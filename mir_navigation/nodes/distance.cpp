#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
ros::Publisher pub;
class pose1 {
  
    
  public:
    double x1;
    double y1;
    pose1(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/robot1/base_pose_ground_truth",1000,&pose1::poseCallback,this);
    }
    void poseCallback(const nav_msgs::Odometry::ConstPtr& msg) 
    {   
   
    x1 = msg->pose.pose.position.x;
    y1 = msg->pose.pose.position.y;
    
    }
    ros::Subscriber pose_subscriber;
};
class newpose {
  
    
  public:
    double x2;
    double y2;
    double x3;
    double y3;
    newpose(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("newpose",1000,&newpose::poseCallback,this);
    }
    void poseCallback(const geometry_msgs::Twist::ConstPtr& msg) 
    {   
   
    x2 = msg->linear.x;
    y2 = msg->linear.y;
    x3 = msg->angular.x;
    y3 = msg->angular.y;
    
    }
    ros::Subscriber pose_subscriber;
};
int main(int argc,char **argv)
{
    ros::init(argc,argv,"distance");
    ros::NodeHandle n;
    pub=n.advertise<geometry_msgs::Twist>("distance",10);
    ros::Rate rate(50);
    pose1 pose1(&n);
    newpose newpose(&n);
    while(ros::ok()){
      geometry_msgs::Twist l;
      l.linear.x=sqrt(pow(newpose.x2-pose1.x1,2)+pow(newpose.y2-pose1.y1,2));
      l.linear.y=sqrt(pow(newpose.x3-pose1.x1,2)+pow(newpose.y3-pose1.y1,2));
      pub.publish(l);
      
      ros::spinOnce();
      rate.sleep();
    }
    
    
   
    
   
    
    

}