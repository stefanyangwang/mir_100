#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
ros::Publisher pub;
class angle1 {
  
    
  public:
    double z1;
    angle1(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/degree",1000,&angle1::poseCallback,this);
    }
    void poseCallback(const std_msgs::Float64::ConstPtr& msg) 
    {   
   
    z1 = msg->data;
    
    
    }
    ros::Subscriber pose_subscriber;
};
class angle2 {
  
    
  public:
    double z2;
    angle2(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/degree1",1000,&angle2::poseCallback,this);
    }
    void poseCallback(const std_msgs::Float64::ConstPtr& msg) 
    {   
   
    z2 = msg->data;
    
    
    }
    ros::Subscriber pose_subscriber;
};
class angle3 {
  
    
  public:
    double z3;
    angle3(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/degree2",1000,&angle3::poseCallback,this);
    }
    void poseCallback(const std_msgs::Float64::ConstPtr& msg) 
    {   
   
    z3 = msg->data;
    
    
    }
    ros::Subscriber pose_subscriber;
};
class phi {
  
    
  public:
    double phi1;
    double phi2;
    phi(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("phi",1000,&phi::poseCallback,this);
    }
    void poseCallback(const geometry_msgs::Twist::ConstPtr& msg) 
    {   
   
    phi1 = msg->linear.x;
    phi2 = msg->linear.y;
    
    
    }
    ros::Subscriber pose_subscriber;
};
int main(int argc,char **argv)
{
    ros::init(argc,argv,"gamma");
    ros::NodeHandle n;
    pub=n.advertise<geometry_msgs::Twist>("gamma",10);
    ros::Rate rate(50);
    angle1 angle1(&n);
    angle2 angle2(&n);
    angle3 angle3(&n);
    phi phi(&n);
    while(ros::ok()){
      geometry_msgs::Twist gamma;
      gamma.linear.x=angle1.z1+phi.phi1-angle2.z2;
      gamma.linear.y=angle1.z1+phi.phi2-angle3.z3;
      pub.publish(gamma);
      
      ros::spinOnce();
      rate.sleep();
    }
    
    
   
    
   
    
    

}