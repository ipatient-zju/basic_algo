#ifndef UNDISTORT_H_
#define UNDISTORT_H_

#include <Eigen/Eigen>

#include <ros/ros.h>
#include <iostream>

#include <opencv2/opencv.hpp>
using namespace Eigen;
using namespace std;

class Undistort{
public:
    Undistort(const Matrix3d& K, const vector<double>& D, const cv::Size& resolution, const bool using_radtan, const double zoom = 1.0);
    
    void undistortImage(const cv::Mat& image, cv::Mat* undistorted_image);
private:
    void distortPixel(const Matrix3d& K, const vector<double>& D, const double zoom, const double u, const double v, double* ud, double* vd);
    
    cv::Mat map_x_;
    cv::Mat map_y_;
    
    bool using_radtan_;
};





#endif