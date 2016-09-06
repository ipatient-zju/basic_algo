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
    int dalay; // in case of a video input
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
};