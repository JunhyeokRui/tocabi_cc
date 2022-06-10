#include "tocabi_lib/robot_data.h"
#include "wholebody_functions.h"
#include <random>

class CustomController
{
public:
    CustomController(RobotData &rd);
    Eigen::VectorQd getControl();

    //void taskCommandToCC(TaskCommand tc_);
    
    void computeSlow();
    void computeFast();
    void computePlanner();
    void copyRobotData(RobotData &rd_l);

    RobotData &rd_;
    RobotData rd_cc_;

    //////////////////////////////////////////// Donghyeon RL /////////////////////////////////////////
    void loadNetwork();
    void processObservation();
    void feedforwardPolicy();
    void initVariable();

    static const int num_state = 70;
    static const int num_hidden = 256;
    static const int num_action = 33;

    Eigen::MatrixXd policy_net_w0_;
    Eigen::MatrixXd policy_net_b0_;
    Eigen::MatrixXd policy_net_w2_;
    Eigen::MatrixXd policy_net_b2_;
    Eigen::MatrixXd action_net_w_;
    Eigen::MatrixXd action_net_b_;
    Eigen::MatrixXd hidden_layer1_;
    Eigen::MatrixXd hidden_layer2_;
    Eigen::MatrixXd rl_action_;
    
    Eigen::MatrixXd state_;
    Eigen::MatrixXd state_mean_;
    Eigen::MatrixXd state_var_;

    std::ofstream writeFile;

    bool is_on_robot_ = false;
    bool is_write_file_ = true;
    Eigen::Matrix<double, MODEL_DOF, 1> q_lpf_;
    Eigen::Matrix<double, MODEL_DOF, 1> q_dot_lpf_;
    Eigen::Matrix<double, MODEL_DOF, 1> rl_action_lpf_;
    Eigen::Matrix<double, 3, 1> euler_angle_lpf_;

    Eigen::Matrix<double, MODEL_DOF, 1> q_noise_;
    Eigen::Matrix<double, MODEL_DOF, 1> q_noise_pre_;
    Eigen::Matrix<double, MODEL_DOF, 1> q_vel_noise_;

    Eigen::Matrix<double, MODEL_DOF, 1> torque_init_;
    Eigen::Matrix<double, MODEL_DOF, 1> torque_spline_;
    Eigen::Matrix<double, MODEL_DOF, 1> torque_bound_;

    float start_time_;
    float time_inference_pre_;

    Eigen::Vector3d euler_angle_;

private:
    Eigen::VectorQd ControlVal_;
};
