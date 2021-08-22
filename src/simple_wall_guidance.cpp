#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

#include <tf2/utils.h>

constexpr float kp = 1.2;
constexpr float ki = 0.0;
constexpr float kd = 0.0;

constexpr float cmd_vel_linear = 0.1;

float range_min;
float target_angle;
float current_angle;

void scanCb(const sensor_msgs::LaserScanConstPtr& msg)
{
    range_min = *min_element(msg->ranges.begin(), msg->ranges.end());
    for(float i=0; i < 360; i++){
        if(range_min == msg->ranges[i]){
            target_angle = (i/180)*M_PI;
            if(target_angle > M_PI && target_angle <= 2*M_PI)
                target_angle += -2*M_PI;
            break;
        }
    }
}

void odomCb(const nav_msgs::Odometry::ConstPtr &msg)
{
    current_angle = tf2::getYaw(msg->pose.pose.orientation);
}

geometry_msgs::Twist pidCmdVelPub()
{
    geometry_msgs::Twist cmd_vel;
    static float prev_err = 0, cmd_vel_pid = 0;
    float err, P;
    target_angle = target_angle + current_angle;
    err = target_angle - current_angle;
    
    P = kp * err;
    cmd_vel_pid = P;

    cmd_vel.linear.x = cmd_vel_linear;
    cmd_vel.angular.z = cmd_vel_pid;
    std::cout << "current_angle: " << current_angle 
              << " target_angle: " <<  target_angle
              << " angular_z_pid: " <<  cmd_vel_pid
              << " range_min: " << range_min
              << "\n";
    return cmd_vel;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "wall_guidance");

    ros::NodeHandle nh;
    ros::Publisher pub_twist; 
    ros::Subscriber sub_scan, sub_odom;

    std::string test;
    std::string test1;
    std::string test2;
    std::string test3;
    std::string test4;
    std::string test5;
    std::string test6;
    std::string test7;
    std::string test8;
    std::string test9;
    std::string test10;

    pub_twist = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    sub_scan = nh.subscribe("scan", 1, scanCb);
    sub_odom = nh.subscribe("odom", 1, odomCb);

    ros::Rate loop_rate(5);
    while (ros::ok){
        pub_twist.publish(pidCmdVelPub());
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}
