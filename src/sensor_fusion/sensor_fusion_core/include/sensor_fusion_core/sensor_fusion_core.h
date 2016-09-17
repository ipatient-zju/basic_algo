#ifndef SENSOR_FUSION_CORE_H_
#define SENSOR_FUSION_CORE_H_

#include <Eigen/Eigen>

#include <ros/ros.h>
#include <dynamic_reconfigure/server.h>
#include <sensor_fusion_core/sensor_fusion_coreConfig.h>

#include <sensor_fusion_common/DoubleArrayStamped.h>
#include <sensor_fusion_common/ExtEkf.h>
#include <sensor_fusion_common/ExtState.h>

#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <sensor_msgs/Imu.h>

#include <vector>

#include "sensor_fusion_core/state.h"

#define N_STATE_BUFFER 256 ///
#define HLI_EKF_STATE_SIZE 16 ///TODO:number of states exchanged with external propagation, {p,v,q,bw} ///

namespace sensor_fusion_core{
typedef dynamic_reconfigure::Server<sensor_fusion_core::sensor_fusion_coreConfig> ReconfigureServer;

class SensorFusionCore{
public:
    typedef Eigen::Matrix<double, N_STATE, 1> ErroeState;
    typedef Eigen::Matrix<double, N_STATE,N_STATE> ErroeStateCov; 
    void initialize(const Eigen::Matrix<double,3,1> &p, //position
		    const Eigen::Matrix<double,3,1> &v, //velocity
		    const Eigen::Quaternion<double> &q, //attitude
		    const Eigen::Matrix<double,3,1> &b_w, //gyro_biases
		    const Eigen::Matrix<double,3,1> &b_a, //acce_bias
		    const double &L,                      //visual scale
		    const Eigen::Quaternion<double> &q_wv, //vision-world attitude drift
		    const Eigen::Matrix<double,N_STATE,N_STATE> &P,//error state covariance 
		    const Eigen::Matrix<double,3,1> &w_m, //angular velocity from IMU
		    const Eigen::Matrix<double,3,1> &a_m, //acce from IMU
		    const Eigen::Matrix<double,3,1> &g, //gravity vector
		    const Eigen::Quaternion<><double> &q_ci, //camera-imu attitude calibration
		    const Eigen::Matrix<double,3,1> &p_ci); //camera-imu position calibration
    ///
    unsigned char getClosestState(State* timestate, ros::Time tstamp, double delay = 0.00);
    
    ///get state info at a given index
    bool getStateAtIdx(State* timestate, unsigned char idx);
    
    SensorFusionCore();
    ~SensorFusionCore();

private:
    const static int nFUllState_ = 28; //全状态
    const static int nBuff_ = 30; //TODO:30个 vision-world attitude driftbuff 取中值
    const static int nMaxCorr_ = 50; //number of IMU measurements buffered for time correction actions
    
    const static int QualityThres_ = 1e3;//TODO:???
    
    Eigen::Matrix<double, N_STATE,N_STATE> Fd_; //discrete state propagation matrix
    Eigen::Matrix<double, N_STATE, N_STATE> Qd_; //discrete propagation noise matrix
    
    ///state variables
    State StateBuffer_[N_STATE_BUFFER]; //EKF buffer contain info at time t
    unsigned char idx_state_; //
    unsigned char idx_p_; // 
    unsigned char idx_time_; //
    
    Eigen::Matrix<double,3,1> g_; //gravity vector
    
    ///TODO: vision-world drift watch dog to determine fuzzy tracking???
    int qvw_inittimer_;
    Eigen::Matrix<double, nBuff_, 4> qbuff_;
    
    ///correction from EKF update
    Eigen::Matrix<double,N_STATE,1> correction_;
    
    ///dynamic reconfigure config
    sensor_fusion_core::sensor_fusion_coreConfig config_;
    
    Eigen::Matrix<double,3,3> R_IW_; // Rot IMU->World
    Eigen::Matrix<double,3,3> R_CI_; // Rot Camera->IMU
    Eigen::Matrix<double,3,3> R_WV_; ///Rot World->Vison
    
    bool initialized_;
    bool predictionMade_;
    
    /// enables internal state predictions for log replay
    /**
    * used to determine if internal states get overwritten by the external
    * state prediction (online) or internal state prediction is performed
    * for log replay, when the external prediction is not available.
    * 
    * 内部状态预测 (log play ) or 外部状态预测 (available)
    */
    
    bool data_playback_;
    
    enum{NO_UP, GOOD_UP, FUZZY_UP};
    
    ros::Publisher pubState_; 
    sensor_fusion_common::DoubleArrayStamped msgState_; //format: point[]
    
    ros:;Publisher pubPose_; //6DoF pose output
    geometry_msgs::PoseWithCovariance msgPose_;
    
    ros::Publisher pubPoseCtrl_; //6DoF pose and velocity
    sensor_fusion_common::ExtState msgPoseCtrl_; //geometry_msgs::Pose and geometry_msgs::vector3
    
    ros::Publisher pubCorrect_; //corrections for external state propagation
    sensor_fusion_common::ExtEkf msgCorrect_; //ang_vel,line_acc,state,flag
    
    ros::Subscriber subState_; //external state propagation
    
    ros::Subscriber subImu_; //IMU readings
    
    sensor_fusion_common::ExtEkf hl_state_buf_; //buffer to store external propagation data
    
    //dynamic reconfigure
    ReconfigureServer *reconfServer_;
    
    
    
    
    

};
}; //end namespace


#endif