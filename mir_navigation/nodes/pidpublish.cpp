#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
class controleffortl1 {
  
    
  public:
    double x;
    
    controleffortl1(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/l1/control_effort",1000,&controleffortl1::poseCallback,this);
    }
    void poseCallback(const std_msgs::Float64::ConstPtr& msg) 
    {   
   
    x = msg->data;
    
    
    }
    ros::Subscriber pose_subscriber;
};
class controleffortl2 {
  
    
  public:
    double x;
    
    controleffortl2(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/l2/control_effort",1000,&controleffortl2::poseCallback,this);
    }
    void poseCallback(const std_msgs::Float64::ConstPtr& msg) 
    {   
   
    x = msg->data;
    
    
    }
    ros::Subscriber pose_subscriber;
};
class controleffortw1 {
  
    
  public:
    double x;
    
    controleffortw1(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/w1/control_effort",1000,&controleffortw1::poseCallback,this);
    }
    void poseCallback(const std_msgs::Float64::ConstPtr& msg) 
    {   
   
    x = msg->data;
    
    
    }
    ros::Subscriber pose_subscriber;
};
class controleffortw2 {
  
    
  public:
    double x;
    
    controleffortw2(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/w2/control_effort",1000,&controleffortw2::poseCallback,this);
    }
    void poseCallback(const std_msgs::Float64::ConstPtr& msg) 
    {   
   
    x = msg->data;
    
    
    }
    ros::Subscriber pose_subscriber;
};

int main(int argc,char **argv)
{
    ros::init(argc,argv,"pidpublish");
    ros::NodeHandle n;
    ros::Publisher pub=n.advertise<geometry_msgs::Twist>("piddistance",10);
    ros::Publisher pub1=n.advertise<geometry_msgs::Twist>("piddegree",10);
    
    ros::Rate rate(50);
   
    controleffortl1 controleffortl1(&n);
    controleffortl2 controleffortl2(&n);
    controleffortw1 controleffortw1(&n);
    controleffortw2 controleffortw2(&n);
    while(ros::ok()){
      geometry_msgs::Twist distanceeffort;
      geometry_msgs::Twist degreeeffort;
      distanceeffort.linear.x=controleffortl1.x;
      distanceeffort.linear.y=controleffortl2.x;
      degreeeffort.linear.x=controleffortw1.x;
      degreeeffort.linear.y=controleffortw2.x;
      
      
      pub.publish(distanceeffort);
      pub1.publish(degreeeffort);
      
      ros::spinOnce();
      rate.sleep();
    }
    
    
   
    
   
    
    

}