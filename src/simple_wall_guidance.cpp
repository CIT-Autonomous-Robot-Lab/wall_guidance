#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

#include <tf/transform_datatypes.h>

constexpr float kp = 0.01;
constexpr float ki = 0;
constexpr float kd = 0;

constexpr float cmd_vel_linear = 0.2;

float range_min;

void scanCb(const sensor_msgs::LaserScanConstPtr& msg)
{
    range_min = *min_element(msg->ranges.begin(), msg->ranges.end());
}

geometry_msgs::Twist pidCmdVelPub(float target_value)
{
    geometry_msgs::Twist cmd_vel;
    static float prev_err = 0, cmd_vel_pid = 0;
    float err, P;
    err = prev_err - target_value;
    
    P = kp * err;
    prev_err = err;

    cmd_vel_pid += P;

    cmd_vel.linear.x = cmd_vel_linear;
    cmd_vel.angular.z = cmd_vel_pid;
    std::cout << "linear_x: " << cmd_vel_linear 
              << " angular_z: " << cmd_vel_pid 
              << " range_min: " << range_min
              << "\n";

    return cmd_vel;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "wall_guidance");

    ros::NodeHandle nh;
    ros::Publisher pub_twist; 
    ros::Subscriber sub_scan;

    pub_twist = nh.advertise<geometry_msgs::Twist>("cmd_vel", 1);
    sub_scan = nh.subscribe("scan", 1, scanCb);

    ros::Rate loop_rate(5);
    while (ros::ok){
        pub_twist.publish(pidCmdVelPub(range_min));

        ros::spinOnce();
        loop_rate.sleep();
    }
    
    return 0;
}
