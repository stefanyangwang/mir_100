#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
ros::Subscriber pose_subscriber;
ros::Subscriber pose_subscriber1;
ros::Subscriber pose_subscriber2;
ros::Publisher pub;
ros::Publisher pub1;
ros::Publisher pub2;

const double PI=3.1415926;

void poseCallback(const nav_msgs::Odometry & pose_message){
    
    std_msgs::Float64 new_pose;
    std_msgs::Float64 new_pose1;
    std_msgs::Float64 a;
    std_msgs::Float64 b;
    std_msgs::Float64 c;
    new_pose.data=1*cos(pose_message.pose.pose.orientation.z)+pose_message.pose.pose.position.x;
    new_pose1.data=1*sin(pose_message.pose.pose.orientation.z)+pose_message.pose.pose.position.y;
    a.data=atan2((pose_message.pose.pose.position.y-new_pose1.data),(new_pose.data-pose_message.pose.pose.position.x));
    b.data=a.data*(180.0/PI);
    if (b.data<0){
        c.data=360+b.data;
    }
    else{
        c.data=b.data;
    }
    c.data=360-c.data;
    pub.publish(c);

}
void poseCallback1(const nav_msgs::Odometry & pose_message){
    
    std_msgs::Float64 new_pose;
    std_msgs::Float64 new_pose1;
    std_msgs::Float64 a;
    std_msgs::Float64 b;
    std_msgs::Float64 c;
    new_pose.data=1*cos(pose_message.pose.pose.orientation.z)+pose_message.pose.pose.position.x;
    new_pose1.data=1*sin(pose_message.pose.pose.orientation.z)+pose_message.pose.pose.position.y;
    a.data=atan2((pose_message.pose.pose.position.y-new_pose1.data),(new_pose.data-pose_message.pose.pose.position.x));
    b.data=a.data*(180.0/PI);
    if (b.data<0){
        c.data=360+b.data;
    }
    else{
        c.data=b.data;
    }
    c.data=360-c.data;
    pub1.publish(c);

}
void poseCallback2(const nav_msgs::Odometry & pose_message){
    
    std_msgs::Float64 new_pose;
    std_msgs::Float64 new_pose1;
    std_msgs::Float64 a;
    std_msgs::Float64 b;
    std_msgs::Float64 c;
    new_pose.data=1*cos(pose_message.pose.pose.orientation.z)+pose_message.pose.pose.position.x;
    new_pose1.data=1*sin(pose_message.pose.pose.orientation.z)+pose_message.pose.pose.position.y;
    a.data=atan2((pose_message.pose.pose.position.y-new_pose1.data),(new_pose.data-pose_message.pose.pose.position.x));
    b.data=a.data*(180.0/PI);
    if (b.data<0){
        c.data=360+b.data;
    }
    else{
        c.data=b.data;
    }
    c.data=360-c.data;
    pub2.publish(c);

}
int main(int argc,char **argv)
{
    ros::init(argc,argv,"radians2degree");
    ros::NodeHandle n;
    pose_subscriber=n.subscribe("/robot1/base_pose_ground_truth",1000,poseCallback);
    pose_subscriber1=n.subscribe("/robot2/base_pose_ground_truth",1000,poseCallback1);
    pose_subscriber2=n.subscribe("/robot3/base_pose_ground_truth",1000,poseCallback2);
    pub=n.advertise<std_msgs::Float64>("/degree",10);
    pub1=n.advertise<std_msgs::Float64>("/degree1",10);
    pub2=n.advertise<std_msgs::Float64>("/degree2",10);
    ros::spin();

}