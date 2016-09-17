//#include "path_output/path_output.h"
#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <geometry_msgs/PoseStamped.h>
#include <nav_msgs/Path.h>

ros::Subscriber point_sub;
ros::Publisher pose_pub;
ros::Publisher path_pub;
geometry_msgs::PoseStamped pose;
nav_msgs::Path path;

void pointCallback(const geometry_msgs::PointStampedConstPtr& msg);
int main (int argc, char **argv) 
{

    ros::init(argc, argv, "path_output_node");
    ros::NodeHandle nh_;

    point_sub =nh_.subscribe("/ground_position",100,pointCallback);
    path_pub=nh_.advertise<nav_msgs::Path>("/path",10);
    ros::spin();
    return 0;
}


void pointCallback(const geometry_msgs::PointStampedConstPtr& msg)
{
    
    
    pose.header.frame_id = "world";
    pose.header.stamp = msg->header.stamp;
    pose.pose.position.x = msg->point.x;
    pose.pose.position.y = msg->point.y;
    pose.pose.position.z = msg->point.z;
    pose.pose.orientation.w = 1;
    pose.pose.orientation.x = 0;
    pose.pose.orientation.y = 0;
    pose.pose.orientation.z = 0;
    //pose_pub.publish(pose);
    
    path.poses.push_back(pose);
    path.header.frame_id = "world";
    path.header.stamp = msg->header.stamp;
    path_pub.publish(path);
}
