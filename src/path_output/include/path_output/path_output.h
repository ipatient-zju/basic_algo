#include <ros/ros.h>
#include <geometry_msgs/PointStamped.h>
#include <nav_msgs/Path.h>
class PathOutput{
public:
    PathOutput();
    ros::NodeHandle nh_;
    ros::Subscriber point_sub;
    ros::Publisher pose_pub;
    ros::Publisher path_pub;
    
    
    void pointCallback(const geometry_msgs::PointStampedConstPtr &msg);
    
};