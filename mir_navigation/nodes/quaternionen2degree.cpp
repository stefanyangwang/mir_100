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
    std_msgs::Float64 a;
    
    double siny_cosp=2.0*(pose_message.pose.pose.orientation.w*pose_message.pose.pose.orientation.z+pose_message.pose.pose.orientation.x*pose_message.pose.pose.orientation.y);
    double cosy_cosp=1.0-2.0*(pose_message.pose.pose.orientation.y*pose_message.pose.pose.orientation.y+pose_message.pose.pose.orientation.z*pose_message.pose.pose.orientation.z);
    a.data=atan2(siny_cosp,cosy_cosp);
    a.data=a.data*(180.0/PI);
    if (a.data<0){
        a.data=360+a.data;
    }
    else{
        a.data=a.data;
    }
   
    pub.publish(a);

}
void poseCallback1(const nav_msgs::Odometry & pose_message){
    
    
   std_msgs::Float64 a;
    
    double siny_cosp=2.0*(pose_message.pose.pose.orientation.w*pose_message.pose.pose.orientation.z+pose_message.pose.pose.orientation.x*pose_message.pose.pose.orientation.y);
    double cosy_cosp=1.0-2.0*(pose_message.pose.pose.orientation.y*pose_message.pose.pose.orientation.y+pose_message.pose.pose.orientation.z*pose_message.pose.pose.orientation.z);
    a.data=atan2(siny_cosp,cosy_cosp);
    a.data=a.data*(180.0/PI);
    if (a.data<0){
        a.data=360+a.data;
    }
    else{
        a.data=a.data;
    }
   
    pub1.publish(a);

}
void poseCallback2(const nav_msgs::Odometry & pose_message){
    
    
    std_msgs::Float64 a;
    
    double siny_cosp=2.0*(pose_message.pose.pose.orientation.w*pose_message.pose.pose.orientation.z+pose_message.pose.pose.orientation.x*pose_message.pose.pose.orientation.y);
    double cosy_cosp=1.0-2.0*(pose_message.pose.pose.orientation.y*pose_message.pose.pose.orientation.y+pose_message.pose.pose.orientation.z*pose_message.pose.pose.orientation.z);
    a.data=atan2(siny_cosp,cosy_cosp);
    a.data=a.data*(180.0/PI);
    if (a.data<0){
        a.data=360+a.data;
    }
    else{
        a.data=a.data;
    }
   
    pub2.publish(a);

}
int main(int argc,char **argv)
{
    ros::init(argc,argv,"quaternionen2degree");
    ros::NodeHandle n;
    pose_subscriber=n.subscribe("/robot1/base_pose_ground_truth",1000,poseCallback);
    pose_subscriber1=n.subscribe("/robot2/base_pose_ground_truth",1000,poseCallback1);
    pose_subscriber2=n.subscribe("/robot3/base_pose_ground_truth",1000,poseCallback2);
    pub=n.advertise<std_msgs::Float64>("/degree",10);
    pub1=n.advertise<std_msgs::Float64>("/degree1",10);
    pub2=n.advertise<std_msgs::Float64>("/degree2",10);
    ros::spin();

}