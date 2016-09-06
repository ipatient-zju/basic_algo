#include "image_undistort/image_undistort.h"
#include "image_undistort/undistort.h"
/********* sensor_msgs/CameraInfo*******/

// std_msgs/Header header
// uint32 height
// uint32 width
// string distortion_model
// float64[] D
// float64[9] K
// float64[9] R
// float64[12] P
// uint32 binning_x
// uint32 binning_y
// sensor_msgs/RegionOfInterest roi

 /***************************************/

ImageUndistort::ImageUndistort(const ros::NodeHandle& nh, const ros::NodeHandle& private_nh):nh_(nh),private_nh_(private_nh),undistort_ptr_(nullptr)
{
    image_sub_ = nh_.subscribe("image",kQueueSize,&ImageUndistort::newFrameCallback,this);
    
    cam_info_sub_ = nh_.subscribe("cam_info",kQueueSize,&ImageUndistort::camInfoCallback,this);
    
    image_pub_ = nh_.advertise<sensor_msgs::Image>("undistorted_image",0);
}

void ImageUndistort::newFrameCallback(const sensor_msgs::ImageConstPtr& image_msg)
{
    cv::Mat image_distorted, image_undistorted;
    
    image_distorted = cv_bridge::toCvCopy(image_msg,"")->image;
    
    if(undistort_ptr_)
    {
	undistort_ptr_-> undistortImage(image_distorted,&image_undistorted);
    }
    else
    {
	ROS_WARN("Attempted to undistort image before setting valid camera info");
	return;
    }
    
    cv_bridge::CvImage out_msg;
    out_msg.header = image_msg->header;
    out_msg.encoding = image_msg->encoding;
    out_msg.image = image_undistorted;
    
    image_pub_.publish(out_msg);
}

void ImageUndistort::camInfoCallback(const sensor_msgs::CameraInfoConstPtr& camera_msg)
{
    //将camera_info.K中的9个元素传入eigen矩阵
    Matrix3d K = Eigen::Map<const Matrix<double, 3,3, Eigen::RowMajor>>(camera_msg->K.elems);
    
    const cv::Size resolution(camera_msg->width, camera_msg->height);
   
    bool using_radtan;
    if (camera_msg->distortion_model == std::string("radtan")) {
	using_radtan = true;
	
    }
    else if(camera_msg->distortion_model == string("equidistant"))
    {
	using_radtan = false;
    }
    else
    {
	ROS_ERROR_STREAM("Unrecognized distortion model" << camera_msg->distortion_model << ". Valid options are radtan and equidistant");
	undistort_ptr_ = nullptr;
	return;
    }
    
    double zoom;
    private_nh_.param("zoom",zoom,kDefaultZoom);
    
    undistort_ptr_ = make_shared<Undistort>(K,camera_msg->D, resolution,using_radtan,zoom);
}
// void ImageUndistort::imageMsgtoCvMat(const sensor_msgs::ImageConstPtr& image_msg, Mat* image)
// {
// 
// }
