#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
class controleffort2w {
  
    
  public:
    double x;
    
    controleffort2w(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/w/control_effort",1000,&controleffort2w::poseCallback,this);
    }
    void poseCallback(const std_msgs::Float64::ConstPtr& msg) 
    {   
   
    x = msg->data;
    
    
    }
    ros::Subscriber pose_subscriber;
};
class controleffort2v {
  
    
  public:
    double x;
    
    controleffort2v(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/v/control_effort",1000,&controleffort2v::poseCallback,this);
    }
    void poseCallback(const std_msgs::Float64::ConstPtr& msg) 
    {   
   
    x = msg->data;
    
    
    }
    ros::Subscriber pose_subscriber;
};
class velocity1 {
  
    
  public:
    double v1;
    double w1;
    velocity1(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/robot1/cmd_vel",1000,&velocity1::poseCallback,this);
    }
    void poseCallback(const geometry_msgs::Twist::ConstPtr& msg) 
    {   
   
    v1 = msg->linear.x;
    w1 = msg->angular.z;
    
    
    }
    ros::Subscriber pose_subscriber;
};
int main(int argc,char **argv)
{
    ros::init(argc,argv,"pidpublish");
    ros::NodeHandle n;
    ros::Publisher pub=n.advertise<geometry_msgs::Twist>("/robot2/cmd_vel",10);
    
    ros::Rate rate(50);
    velocity1 velocity1(&n);
    controleffort2w controleffort2w(&n);
    controleffort2v controleffort2v(&n);
    while(ros::ok()){
      geometry_msgs::Twist velocity2;
      
      velocity2.angular.z=velocity1.w1+controleffort2w.x;
      velocity2.linear.x=velocity1.v1+controleffort2v.x;
      
      pub.publish(velocity2);
      
      
      ros::spinOnce();
      rate.sleep();
    }
    
    
   
    
   
    
    

}