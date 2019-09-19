#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
ros::Publisher pub;
ros::Publisher pub1;
const double PI=3.1415926;
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
class pose2 {
  
    
  public:
    double x2;
    double y2;
    pose2(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/robot2/base_pose_ground_truth",1000,&pose2::poseCallback,this);
    }
    void poseCallback(const nav_msgs::Odometry::ConstPtr& msg) 
    {   
   
    x2 = msg->pose.pose.position.x;
    y2 = msg->pose.pose.position.y;
    
    }
    ros::Subscriber pose_subscriber;
};
class pose3 {
  
    
  public:
    double x3;
    double y3;
    pose3(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/robot3/base_pose_ground_truth",1000,&pose3::poseCallback,this);
    }
    void poseCallback(const nav_msgs::Odometry::ConstPtr& msg) 
    {   
   
    x3 = msg->pose.pose.position.x;
    y3 = msg->pose.pose.position.y;
    
    }
    ros::Subscriber pose_subscriber;
};
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





int main(int argc,char **argv)
{
    ros::init(argc,argv,"phi");
    ros::NodeHandle n;
    pub=n.advertise<geometry_msgs::Twist>("phi",10);
    pub1=n.advertise<geometry_msgs::Twist>("newpose",10);
    pose1 pose1(&n);
    pose2 pose2(&n);
    pose3 pose3(&n);
    angle1 angle1(&n);
    angle2 angle2(&n);
    angle3 angle3(&n);
    ros::Rate rate(50);
    while(ros::ok()){
      geometry_msgs::Twist newpose1;
      geometry_msgs::Twist newpose2;
      std_msgs::Float64 a;
      std_msgs::Float64 b;
      std_msgs::Float64 c;
      std_msgs::Float64 d;
      std_msgs::Float64 e;
      std_msgs::Float64 f;
      std_msgs::Float64 phi1;
      std_msgs::Float64 phi2;
      
      newpose1.linear.x=0.45*cos(angle2.z2)+pose2.x2;
      newpose1.linear.y=0.45*cos(angle2.z2)+pose2.y2;
      newpose2.linear.x=0.45*cos(angle3.z3)+pose3.x3;
      newpose2.linear.y=0.45*cos(angle3.z3)+pose3.y3;
      a.data=atan2((pose1.y1-newpose1.linear.y),(newpose1.linear.x-pose1.x1));
      d.data=atan2((pose1.y1-newpose2.linear.y),(newpose2.linear.x-pose1.x1));
      b.data=a.data*(180/PI);
      e.data=d.data*(180/PI);
      if(b.data<0){
        c.data=360+b.data;
         
      }
      else{
        c.data=b.data;
      }
      if(e.data<0){
        f.data=360+e.data;
         
      }
      else{
        f.data=e.data;
      }

      c.data=360-c.data;
      f.data=360-f.data;
      if(c.data>angle1.z1){
        phi1.data=c.data-angle1.z1;

      }
      else{
        phi1.data=360-angle1.z1+c.data;
      }
      if(f.data>angle1.z1){
        phi2.data=f.data-angle1.z1;

      }
      else{
        phi2.data=360-angle1.z1+f.data;
      }



      geometry_msgs::Twist g;
      geometry_msgs::Twist h;
      g.linear.x=phi1.data;
      g.linear.y=phi2.data;
      h.linear.x=newpose1.linear.x;
      h.linear.y=newpose1.linear.y;
      h.angular.x=newpose2.linear.x;
      h.angular.y=newpose2.linear.y;
      
      
      
      
      pub.publish(g);
      pub1.publish(h);
      ros::spinOnce();
      rate.sleep();
    }
    
    
   
    
   
    
    

}