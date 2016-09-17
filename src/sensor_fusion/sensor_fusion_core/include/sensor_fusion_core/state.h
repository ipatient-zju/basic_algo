#ifndef STATE_H_
#define STATE_H_

#include <Eigen/Eigen>

#include <vector>
#include <sensor_fusion_core/eigen_conversion.h>

#include <sensor_fusion_common/ExtState.h>
#include <sensor_fusion_common/DoubleArrayStamped.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>

#define N_STATE 25 //error state size

namespace sensor_fusion_core{
//TODO: define the state, its associated error state covariance and the system inputs
class State
{
  //state varying during propagation
  Eigen::Matrix<double,3,1> p_; /// 0-2, position, IMU-centered
  Eigen::Matrix<double,3,1> v_; /// 3-5, velocity
  Eigen::Quaternion<double> q_; /// 6-9/6-8, attitude
  Eigen::Matrix<double,3,1> b_w_; /// 10-12/9-11, gyro bias
  Eigen::Matrix<double,3,1> b_a_; /// 13-15/12-14, acceleration bias
  
  //state not varying during propagation
  double L_; /// 16/15,visual scale 
  Eigen::Quaternion<double> q_wv_; /// 17-20/16-18, vision-world attitude drift
  Eigen::Quaternion<double> q_ci_; /// 21-24/19-21, camera-imu attitude calibration
  Eigen::Matrix<double,3,1> p_ci_; /// 25-27/22-24, camera-imu position calibration
  
  //system inputs
  Eigen::Matrix<double,3,1> w_m_; /// angular velocity from IMU
  Eigen::Matrix<double,3,1> a_m_; /// acceleration from IMU
  
  Eigen::Quaternion<double> q_int_; ///TODO: [没理解！]this is the integrated ang. vel. no corrections applied, to use for delta rot in external algos...
  
  Eigen::Matrix<double, N_STATE, N_STATE> P_; /// error state covariance
 
  double time_; /// time of this state estimate
  
  /***状态重置***
   * 
   * 3D vector:  0
   * quaternion: unit
   * scale:      1
   * time:       0
   * Error covariance: zeros
   * 
   **************/
  void reset();
  
  ///拿到位置与姿态的协方差
  void getPoseCovariance(geometry_msgs::PoseWithCovariance::_covariance_type & cov);
  
  ///from state get PoseWithCovarianceStamped message
  void toPoseMsg(geometry_msgs::PoseWithCovarianceStamped &pose);
  
  ///from state get DoubleArrayStamped message
  void toStateMsg(sensor_fusion_common::DoubleArrayStamped& state);
  
    
};
}


#endif