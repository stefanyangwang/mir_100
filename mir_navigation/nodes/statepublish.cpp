#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
class velocity2 {
  
    
  public:
    double x1;
    double y1;
    velocity2(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("/robot2/cmd_vel",1000,&velocity2::poseCallback,this);
    }
    void poseCallback(const geometry_msgs::Twist::ConstPtr& msg) 
    {   
   
    x1 = msg->linear.x;
    y1 = msg->angular.z;
    
    }
    ros::Subscriber pose_subscriber;
};
int main(int argc,char **argv)
{
    ros::init(argc,argv,"statepublish");
    ros::NodeHandle n;
    ros::Publisher servo_state_pub = n.advertise<std_msgs::Float64>("w/state", 1);
    ros::Publisher servo_state_pub1 = n.advertise<std_msgs::Float64>("v/state", 1);
    ros::Rate rate(50);
    velocity2 velocity2(&n);
    
    while(ros::ok()){
      std_msgs::Float64 plant_state;
      std_msgs::Float64 plant_state1;
      plant_state.data=velocity2.y1;
      plant_state1.data=velocity2.x1;
      servo_state_pub.publish(plant_state);
      servo_state_pub1.publish(plant_state1);
      
      ros::spinOnce();
      rate.sleep();
    }
    
    
   
    
   
    
    

}