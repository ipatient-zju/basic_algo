#ifndef CAMERA_INFO_READ_H_
#define CAMERA_INFO_READ_H_

#include <Eigen/Eigen>

#include <ros/ros.h>
#include <sensor_msgs/CameraInfo.h>

using namespace std;
class CameraInfoRead{
public:
    CameraInfoRead(const ros::NodeHandle& nh, const ros::NodeHandle& private_nh);
private:
    bool loadCamParam();
    
    ros::NodeHandle nh_;
    ros::NodeHandle private_nh_;
    
    sensor_msgs::CameraInfo cam_info_;
    
    ros::Publisher cam_info_pub_;
    
};



#endif
