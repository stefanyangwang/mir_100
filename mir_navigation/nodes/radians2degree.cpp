#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
ros::Subscriber pose_subscriber;
ros::Publisher pub;

const double PI=3.1415926;

void poseCallback(const nav_msgs::Odometry & pose_message){
    
    std_msgs::Float64 new_msg;
    new_msg.data=pose_message.pose.pose.orientation.z*180.0/PI;
    pub.publish(new_msg);

}
int main(int argc,char **argv)
{
    ros::init(argc,argv,"radians2degree");
    ros::NodeHandle n;
    pose_subscriber=n.subscribe("/robot1/base_pose_ground_truth",1000,poseCallback);
    pub=n.advertise<std_msgs::Float64>("/degree",10);
    ros::spin();

}