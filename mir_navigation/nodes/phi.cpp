#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
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






int main(int argc,char **argv)
{
    ros::init(argc,argv,"phi");
    ros::NodeHandle n;
    pub=n.advertise<std_msgs::Float64>("phi1",10);
    pose1 pose1(&n);
    while(ros::ok()){
      std_msgs::Float64 b;
      b.data=pose1.x1;
      pub.publish(b);
      ros::spinOnce();
    }
    
    
   
    
   
    
    

}