#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h> //standard input or output

#include <ros/ros.h>
#include <image_transport/image_transport.h>
#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/image_encodings.h>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class Settings
{
public:
    enum Pattern{NOT_EXISTING, CHESSBOARD, CIRCLES_GRID,ASYMMETRIC_CIRCLES_GRID};
    //标定板大小，
    Size boardSize; //number of items by width and heidght
    //棋盘格模式
    Pattern calibrationPattern;
    int squareSize; //size of a square (point, millimeter, etc)
    int nrFrames; //the number of frames to use from the input for calibration
    bool aspectRatio; //宽高比
    int  dalay; // in case of a video input
    bool bwritePoints; //detected feature bwritePoints
    bool bwriteExtrinsics; //extrinsic parameters
    //0切向畸变
    bool calibZeroTangentDist;
    bool calibFixPrincipalPoint; //Fix the principal point at the center
    bool flipVertical; //
    string outputFileName;//name of file where to write
    bool showUndistorsed; // Show undistorted images after calibration
    vector<string> imageList;
    int atImageList;
    bool goodInput;
    int flag;
private:
    string patternToUse;
     
public:
    Settings():goodInput(false){}
    //Write serialization for this class
    void write(FileStorage& fs)
    {
	fs << "{" << "BoardSize_Width" << boardSize.width
		  << "boardSize_Height"<< boardSize.height
		  << "Square_Size" << squareSize
		  << "Calibrate_Pattern" <<patternToUse
		  << "Calibrate_NrOfFrameToUse" <<nrFrames
		  << "Calibrate_FixAspectRatio" <<aspectRatio
		  << "Calibrate_AssumeZeroTangentialDistortion"<<calibZeroTangentDist		<<"Calibrate_FixPrincipalPointAtTheCenter"<<calibFixPrincipalPoint
		  <<"Write_DetectedFeatures" << bwritePoints
		  <<"Write_extrinsicParameters"<<bwriteExtrinsics
		  <<"Write_outputFileName"<<outputFileName
		  <<"Show_UndistortedImage"<<showUndistorsed
		  <<"Input_FileAroundHorizontalAxis"<<flipVertical
		  <<"Input_Delay"<< delay << "}";
    }
    
    void read(ros::NodeHandle& nh)
    {
	nh.param("BoardSize_Width", boardSize.width, 8);
	nh.param("BoardSize_Height", boardSize.height, 6);
	nh.param("Calibrate_Pattern", patternToUse, string("CHESSBOARD"));
        nh.param("Square_Size", squareSize, 28);
        nh.param("Calibrate_NrOfFrameToUse", nrFrames, 20);
        nh.param("Calibrate_FixAspectRatio", aspectRatio, false);
        nh.param("Write_DetectedFeaturePoints", bwritePoints, true);
        nh.param("Write_ExtrinsicParameters", bwriteExtrinsics, true);
        nh.param("Write_OutputFileName", outputFileName, string("default.xml"));
        nh.param("Calibrate_AssumeZeroTangentialDistortion", calibZeroTangentDist, false);
        nh.param("Calibrate_FixPrincipalPointAtTheCenter", calibFixPrincipalPoint, false);
        nh.param("Input_FlipAroundHorizontalAxis", flipVertical, true);
        nh.param("Show_UndistortedImage", showUndistorsed, true);
        nh.param("Input_Delay", delay, 2000);
        interprate();
    }
    
    void interprate()
    {
	goodInput = true;
	
	if(boardSize.width <=0 || boardSize.height <= 0)
	{
	    cerr << "Invalid Board size:" << boardSize.width << " "<< boardSize.height << endl;
	    goodInput = false;
	}
	
	if (squareSize <= 10e-6)
        {
            cerr << "Invalid square size " << squareSize << endl;
            goodInput = false;
        }
        
        if (nrFrames <= 0)
        {
            cerr << "Invalid number of frames " << nrFrames << endl;
            goodInput = false;
        }
        
        flag = 0;
	
	if(calibFixPrincipalPoint) 
	    flag |= CV_CALIB_FIX_PRINCIPAL_POINT; //位或操作,4
	if(calibZeroTangentDist)
	    flag |=CV_CALIB_ZERO_TANGENT_DIST;//0切向畸变，8
	if(aspectRatio)
	    flag |=CV_CALIB_FIX_ASPECT_RATIO;//宽高比，2
	    
	calibrationPattern = NOT_EXISTING;
	if(!patternToUse.compare("CHESSBOARD")) //compare returns 0 if equivalent
	    calibrationPattern = CHESSBOARD;
	if (!patternToUse.compare("CIRCLES_GRID")) 		
	    calibrationPattern = CIRCLES_GRID;
        if (!patternToUse.compare("ASYMMETRIC_CIRCLES_GRID")) 
	    calibrationPattern = ASYMMETRIC_CIRCLES_GRID;
	
	if (calibrationPattern == NOT_EXISTING)
        {
            cerr << " Inexistent camera calibration mode: " << patternToUse << endl;
            goodInput = false;
        }
        
        atImageList = 0; //??
    }
    
  
};

enum {DETECTION = 0, CAPTURING = 1, CALIBRATED =2};

bool runCalibrationAndSave(Settings& s, Size imageSize, Mat&cameraMatrix, Mat& disCoeffs, vector<vector<Point2f>> imagePoints);

Mat nextImage;

void imageCallback(const sensor_msgs::ImageConstPtr& msg)
{
    cv_bridge::CvImagePtr cv_ptr;
    try{
	cv_ptr = cv_bridge::toCvCopy(msg,sensor_msgs::image_encodings::BGR8);
    }
    catch(cv_bridge::Exception& e)
    {
	ROS_ERROR("cv_bridge exception: %s",e.what());
	return;
    }
    nextImage = Mat(cv_ptr->image);
}

//TODO:计算得到平均的重投影误差
//input: objectPoints, rvecs, tvecs, cameraMatrix, disCoeffs, imagePoints
//output: totalErr/totalPoints
static double computerReprojectionErrors(const vector<vector<Point3f> >& objectPoints, const vector<vector<Point2f>> &imagePoints, const vector<Mat>&rvecs, const vector<Mat>& tvecs, const Mat& cameraMatrix, const Mat& distCoeffs, vector<float>& perViewErrors)
{
    vector<Point2f> imagePoints2;
    int i, totalPoints = 0; //棋盘格总点数
    double totalErr = 0, err;
    perViewErrors.resize(objectPoints.size());
    
    for(i=0; i<(int)objectPoints.size(); ++i)
    {
	//TODO:Projects 3D points to an image plane
	//void projectPoints(InputArray objectPoints, InputArray rvec, InputArray tvec, InputArray cameraMatrix, InputArray distCoeffs, OutputArray imagePoints, OutputArray jacobian=noArray(), double aspectRatio=0 )
	
       /*** 1.将实际点重投影到图像平面 ***/		
    
       projectPoints(Mat(objectPoints[i]),rvecs[i],tvecs[i],cameraMatrix,distCoeffs,imagePoints2);
       /*** 2.计算重投影的图像点与实际图像点的总的误差 ***/
	// an absolute difference norm
	err = norm(Mat(imagePoints[i],Mat(imagePoints2),CV_L2);
	
	int n = (int)objectPoints[i].size();
	/*** 3.计算单点的平均重投影误差  ***/
	perViewErrors[i] = (float) std::sqrt(err*err/n);
	/*** 4.计算总误差的平方 ***/
	totalErr += err*err;
	totalPoints += n;
    }
    
    return std::sqrt(totalErr/totalPoints);
}
//TODO:计算棋盘格交点位置
//input: boardSize, squareSize, patternType
//output: corners
static void calcBoardCornerPositions(Size boardSize, float squareSize, vector<Point3f>& corners, Settings::Pattern patternType ) //patternType default: CHESSBOARD
{
    corners.clear();
    
    switch(patternType)
    {
	case Settings::CHESSBOARD:
	case Settings::CIRCLES_GRID:
	    for(int i=0; i<boardSize.height; ++i)
		for(int j=0; j<boardSize.width; ++j)
		{
		    corners.push_back(Point3f(float(j*squareSize), float(i*squareSize),0));
		}
	    break;
	case Settings::ASYMMETRIC_CIRCLES_GRID:
	    for( int i = 0; i < boardSize.height; i++ )
		for( int j = 0; j < boardSize.width; j++ )
		{
		    corners.push_back(Point3f(float((2*j + i % 2)*squareSize), float(i*squareSize), 0));
		}   
	    break;
	default:
	    break;
    }
}
//TODO:计算相机内外参，以及畸变参数; 计算平均重投影误差
//input: Settings& s(flag,boardSize,sqaureSize,CalibrationPattern), imageSize, imagePoints, 
//output: cameraMatrix, distCoeffs,rvecs,tvecs, reprojErrs, totalAvgErr
static bool runCalibration(Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs, vector<vector<Point2f> > imagePoints, vector<Mat>& rvecs, vector<Mat>& tvecs, vector<float>& reprojErrs, double& totalAvgErr)
{
    cameraMatrix = Mat::eye(3,3,CV_64F);
    if(s.flag & CV_CALIB_FIX_ASPECT_RATIO)//宽高比
	cameraMatrix.at<double>(0,0) = 1.0; //???
    distCoeffs = Mat::zeros(8,1,CV_64F);//(K1,K2,P1,P2[,K3[,K4,K5,K6]])
    
    vector<vector<Point3f> > objectPoints(1);
    
    /*** 1.得到棋盘格交点位置 ***/
    calcBoardCornerPositions(s.boardSize,(float)s.squareSize,objectPoints[0],s.calibrationPattern);
    
    // resize(size_type __new_size, const value_type& __x),定义数组大小，并塞入数据
    objectPoints.resize(imagePoints.size(),objectPoints[0]);
    
    //ouble calibrateCamera(InputArrayOfArrays objectPoints, InputArrayOfArrays imagePoints, Size imageSize, InputOutputArray cameraMatrix, InputOutputArray distCoeffs, OutputArrayOfArrays rvecs, OutputArrayOfArrays tvecs, int flags=0 )
    
    /*** 2.计算内参，外餐，畸变参数 ***/
    double rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs, s.flag|CV_CALIB_FIX_K4|CV_CALIB_FIX_K5);
    
    cout << "Re-projection error reported by calibrateCamera: "<< rms << endl;//?????
    
    /*** 3.检查内参与畸变参数 ***/
    bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs); //内参3*3, 畸变参数8*1
    
    /*** 4.计算平均重投影误差（多张图） ***/
    totalAvgErr = computerReprojectionErrors(objectPoints, imagePoints, rvecs, tvecs, cameraMatrix, reprojErrs);
    
    return ok;
}


//TODO: Print camera parameters to the output file

static void saveCameraParams(Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs, const vector<Mat>& rvecs, const vector<Mat>& tvecs, const vector<float>& reprojErrs, const vector<vector<Point2f> >& imagePoints, double totalAvgErr)
{
    FileStorage fs( s.outputFileName, FileStorage::WRITE);
    
    time_t tm;
    time( &tm ); //return current time
    struct tm *t2 = localtime( &tm);
    char buf[1024];
    strftime(buf, sizeof(buf)-1, "%c", t2); //将t2保存的标准日期的时间串放在buf指向的字符串中
    
    fs << "calibration_time" << buf;
    
    if( !rvecs.empty() || !reprojErrs.empty() )
    {
	fs << "nrOfFrames" << (int)std::max(rvecs.size(), reprojErrs.size());
    }
    fs << "image_Width" << imageSize.width;
    fs << "image_Height" << imageSize.height;
    fs << "board_Width" << s.boardSize.width;
    fs << "board_Height" << s.boardSize.height;
    fs << "square_Size" << s.squareSize;
    
    if( s.flag & CV_CALIB_FIX_ASPECT_RATIO)
	fs << "FixAspectRatio" << s.aspectRatio;
    
    if(s.flag)
    {
	sprintf(buf, "flags: %s%s%s%s", 
	    s.flag &CV_CALIB_USE_INTRINSIC_GUESS ? "+use_intrinsic_guess" : "",
	    s.flag & CV_CALIB_FIX_ASPECT_RATIO ?
	    "+fix_aspectRatio" : "",
            s.flag & CV_CALIB_FIX_PRINCIPAL_POINT ? 
            "+fix_principal_point" : "",
            s.flag & CV_CALIB_ZERO_TANGENT_DIST ? 
            "+zero_tangent_dist" : "" );
	cvWriteComment( *fs, buf, 0); // writes a comment into file storage
	
    }
    
    fs << "flagValue" << s.flag;

    fs << "Camera_Matrix" << cameraMatrix;
    fs << "Distortion_Coefficients" << distCoeffs;

    fs << "Avg_Reprojection_Error" << totalAvgErr; //sqrt(totalErr/totalPoints)
    if( !reprojErrs.empty() )
        fs << "Per_View_Reprojection_Errors" << Mat(reprojErrs);//每一帧的重投影误差
    if( !rvecs.empty() && !tvecs.empty() )
    {
	CV_Assert(rvecs[0].type() == tvecs[0].type()); //Checks a condition at runtime and throws exception if it fails
	
	Mat bigmat( (int)rvecs.size(), 6, rvecs[0].type() );
	//将每一帧得到的r,t写在一个bigmat中
	for( int i=0; i<(int)rvecs.size(); i++)
	{
	    Mat r = bigmat(Range(i,i+1), Range(0,3));
	    Mat t = bigmat(Range(i,i+1), Range(3,6));
	    CV_Assert(rvecs[i].rows == 3 && rvecs[i].cols == 1); //源r 3行1列
	    CV_Assert(tvecs[i].rows == 3 && tvecs[i].cols == 1);// 源t 3行1列
	    
	    r = rvecs[i].t(); //1行3列
	    t = tvecs[i].t();
	}
	cvWriteComment( *fs, "a set of 6-tuples (rotation vector + translation vector) for each view", 0 );
        fs << "Extrinsic_Parameters" << bigmat;
	
    }
    
    if( !imagePoints.empty() )
    {
	Mat imagePtMat( (int)imagePoints.size(), (int)imagePoints[0].size(), CV_32FC2);
	
	for( int i=0; i<(int)imagePoints.size(); i++)
	{
	    Mat r = imagePtMat.row(i).reshape(2, imagePtMat.cols);
	    imgpti.copyTo(r);
	}
	fs << "Image_points" << imagePtMat;
    }
}


bool runCalibrationAndSave(Settings& s, Size imageSize, Mat&  cameraMatrix, Mat& distCoeffs,vector<vector<Point2f> > imagePoints )
{
    vector<Mat> rvecs, tvecs;
    vector<float> reprojErrs;
    double totalAvgErr = 0;

    bool ok = runCalibration(s,imageSize, cameraMatrix, distCoeffs, imagePoints, rvecs, tvecs,
                             reprojErrs, totalAvgErr);
    cout << (ok ? "Calibration succeeded" : "Calibration failed")
        << ". avg re projection error = "  << totalAvgErr << endl;

    if( ok )
        saveCameraParams( s, imageSize, cameraMatrix, distCoeffs, rvecs ,tvecs, reprojErrs,
                            imagePoints, totalAvgErr);
    return ok;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "camera_calibration_node");
    
    ros::NodeHandle nh;
    
    string image_topic;
    nh.param("image_topic", image_topic,"/cam/image_raw");
    image_transport::ImageTransport it(nh);
    image_transport::Subscriber sub = it.subscribe(image_topic,1, imageCallback);
    
    Settings s;
    s.read(nh);
    
    if( !s.goodInput)
    {
	cout << "Invalid input detected. Application stopping." << endl;
	return -1;
    }
    
    vector<vector<Point2f>> imagePoints;
    Mat cameraMatrix, distCoeffs;
    Size imageSize;
    int mode = DETECTION;
    clock_t prevTimestamp = 0;
    const Scalar RED(0,0,255), GREEN(0,255,0);
    const char ESC_KEY = 27;
    
    while( ros::ok() )
    {
	Mat view;
	bool blinkOutput = false;
	
	//get the next image here
	while ( view.empty() )
	{
	    ros::spinOnce();
	    view = Mat(nextImage);
	    cout << "Wait for image" << endl;
	}
	// if no more image or get enough, then stop calibration and show result
	if( mode == CAPTURING && imagePoints.size() >= (unsigned )s.nrFrames )
	{
	    if(runCalibrationAndSave(s,imageSize, cameraMatrix, distCoeffs,imagePoints))
		mode = CALIBRATED;
	    else
		mode = DETECTION;
	}
	
	if(view.empty())
	{
	    if(imagePoints.size() > 0)
		runCalibrationAndSave(s, imageSize, cameraMatrix, distCoeffs, imagePoints);
	    break;
	}
	
	imageSize = view.size();
	if(s.flipVertical)
	    flip(view, view, 0);
	vector<Point2f> pointBuf;
    }
}






