#include "image_undistort/undistort.h"

//TODO: 对图像去畸变，from destination image to source image
Undistort::Undistort(const Matrix3d& K, const vector< double >& D, const cv::Size& resolution, const bool using_radtan, const double zoom):using_radtan_(using_radtan)
{
    //TODO:initialize maps
    map_x_.create(resolution,CV_32FC1);
    map_y_.create(resolution,CV_32FC1);
    
    //Computer the remap maps
    for(size_t v = 0; v< resolution.height; ++v)
    {
	for(size_t u = 0; v<resolution.width; ++u)
	{
	    double ud, vd;
	    distortPixel(K,D,zoom,u,v,&ud,&vd);
	    
	    //insert in map
	    map_x_.at<float>(v,u) = ud;
	    map_y_.at<float>(v,u) = vd;
	}
    }
}

//TODO:对每个像素进行去畸变操作,从destination image to source image,详见http://docs.opencv.org/2.4/modules/imgproc/doc/geometric_transformations.html?highlight=undistort
void Undistort::distortPixel(const Matrix3d& K, const vector< double >& D, const double zoom, const double u, const double v, double* ud, double* vd)
{
    /*******
     *  |u|   |fx        0      cx | |x/z|
     *  |v| = | 0       fy      cy | |y/z|
     *  |1|   |	0	 0      1  | |1  |
     *  
     ********/
    double x = (u-K(0,2)) / K(0,0);
    double y = (v-K(1,2)) / K(1,1);
    
    x = x*1.0/zoom;
    y = y*1.0/zoom;
    
    double xd, yd;
    //TODO: D – Input vector of distortion coefficients  (k_1, k_2, p_1, p_2[, k_3[, k_4, k_5, k_6]]) of 4, 5, or 8 elements.
    //TODO:radian径向 tangential切向 模型：plumb_bob
    if (using_radtan_) 
    {
	double k1 = D[0];
	double k2 = D[1];
	double k3 = D[4];
	double p1 = D[2];
	double p2 = D[3];
	
	//undistort
	double r2 = x * x + y * y;
	double r4 = r2 * r2;
	double r6 = r4 * r2;
	double kr = (1.0 + k1 * r2 + k2 * r4 + k3 * r6);
	xd = x * kr + 2.0 * p1 * x * y + p2 * (r2 + 2.0 * x * x);
	yd = y * kr + 2.0 * p2 * x * y + p1 * (r2 + 2.0 * y * y);
    }
    else{
	double k1 = D[0];
	double k2 = D[1];
	double k3 = D[2];
	double k4 = D[3];
	
	 // Undistort
	double r = std::sqrt(x * x + y * y);
	if (r < 1e-10) {
	*ud = u;
	*vd = v;
	return;
	}
	const double theta = atan(r);
	const double theta2 = theta * theta;
	const double theta4 = theta2 * theta2;
	const double theta6 = theta2 * theta4;
	const double theta8 = theta4 * theta4;
	const double thetad =
	    theta * (1 + k1*theta2 + k2*theta4 + k3*theta6 + k4*theta8);

	const double scaling = (r > 1e-8) ? thetad / r : 1.0;
	xd = x * scaling;
	yd = y * scaling;
    }
    
    *ud = K(0, 0) * xd + K(0, 2);
    *vd = K(1, 1) * yd + K(1, 2);
}
//TODO:计算非整数坐标的像素值
void Undistort::undistortImage(const cv::Mat& image, cv::Mat* undistorted_image)
{
    cv::remap(image, *undistorted_image, map_x_, map_y_, CV_INTER_LINEAR,cv::BORDER_CONSTANT, cv::Scalar(0,0,0));
}
