#ifndef IMAGE_UNDISTORT_H_
#define IMAGE_UNDISTORT_H_

#include <stdio.h>
#include <Eigen/Eigen>

#include <ros/ros.h>
#include <ros/callback_queue.h>

#include "image_undistort/undistort.h"

#include <cv_bridge/cv_bridge.h>
#include <sensor_msgs/Image.h>
#include <sensor_msgs/CameraInfo.h>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
using namespace Eigen;

class ImageUndistort{
public:
    ImageUndistort(const ros::NodeHandle& nh, const ros::NodeHandle& private_nh);
private:
    void imageMsgtoCvMat(const sensor_msgs::ImageConstPtr& image_msg, cv::Mat* image);
    
    void newFrameCallback(const sensor_msgs::ImageConstPtr& image_msg);
    
    void camInfoCallback(const sensor_msgs::CameraInfoConstPtr& camera_msg);
    
    ros::NodeHandle nh_;
    ros::NodeHandle private_nh_;
    
    ros::Subscriber image_sub_;
    ros::Subscriber cam_info_sub_;
    
    ros::Publisher image_pub_;
    
    shared_ptr<Undistort> undistort_ptr_;
};


//constexpr = static const 
constexpr size_t kQueueSize = 100;
constexpr double kDefaultZoom = 1.0; 



#endif
