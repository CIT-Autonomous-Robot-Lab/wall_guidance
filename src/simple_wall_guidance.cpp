#include <ros/ros.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

#include <tf2/utils.h>

constexpr float kp = 0.01;
constexpr float ki = 0;
constexpr float kd = 0;

constexpr float cmd_vel_linear = 0.2;

float target_angle;
float current_angle;

void scanCb(const sensor_msgs::LaserScanConstPtr& msg)
{
    float range_min = *min_element(msg->ranges.begin(), msg->ranges.end());
    for(float i=0; i < 360; i++){
        // std::cout << i;
        if(range_min == msg->ranges[i]){
            target_angle = i;
            // std::cout << i << ", " << target_angle << ", " << range_min << "\n";
            break;
        }
    }
}

void odomCb(const nav_msgs::Odometry::ConstPtr &msg)
{
    current_angle = (tf2::getYaw(msg->pose.pose.orientation)*180) / M_PI;
    if(current_angle >= -180 && current_angle < 0)
        current_angle += 360;
}

geometry_msgs::Twist pidCmdVelPub()
{
    geometry_msgs::Twist cmd_vel;
    static float prev_err = 0, cmd_vel_pid = 0;
    float err, P;
    err = target_angle - current_angle;
    // err = prev_err - target_value;
    
    P = kp * err;
    // prev_err = err;

    cmd_vel_pid = P;

    cmd_vel.linear.x = cmd_vel_linear;
    cmd_vel.angular.z = cmd_vel_pid;
    std::cout << current_angle << ", " 
              << target_angle << ", " 
              << cmd_vel_pid << ", " 
              << "\n";
    // std::cout << "linear_x: " << cmd_vel_linear 
    //           << " angular_z: " << cmd_vel_pid 
    //           << " range_min: " << range_min
    //           << "\n";

    return cmd_vel;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "wall_guidance");

    ros::NodeHandle nh;
    ros::Publisher pub_twist; 
    ros::Subscriber sub_scan, sub_odom;

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
