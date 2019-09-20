#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
const double PI=3.1415926;
class distance {
  
    
  public:
    double l1; //distance between robot 1 and robot 2
    double l2; //distance between robot 1 and robot 3
    distance(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("distance",1000,&distance::poseCallback,this);
    }
    void poseCallback(const geometry_msgs::Twist::ConstPtr& msg) 
    {   
   
    l1 = msg->linear.x;
    l2 = msg->linear.y;
    
    
    }
    ros::Subscriber pose_subscriber;
};
class phi {
  
    
  public:
    double phi1; //relative direction between robot 1 and robot 2 in degree
    double phi2; //relative direction between robot 1 and robot 3 in degree
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
    ros::init(argc,argv,"statepublish");
    ros::NodeHandle n;
    ros::Publisher servo_state_pub = n.advertise<std_msgs::Float64>("l1/state", 1);//distance between robot 1 and robot 2 in real time
    ros::Publisher servo_state_pub1 = n.advertise<std_msgs::Float64>("l2/state", 1);//distance between robot 1 and robot 3 in real time
    ros::Publisher servo_state_pub2 = n.advertise<std_msgs::Float64>("w1/state", 1);//relative direction between robot 1 and robot 2 in real time
    ros::Publisher servo_state_pub3 = n.advertise<std_msgs::Float64>("w2/state", 1);//relative direction between robot 1 and robot 3 in real time
    ros::Rate rate(50);
    distance distance(&n);
    phi phi(&n);
    while(ros::ok()){
      std_msgs::Float64 plant_state; //distance between robot 1 and robot 2
      std_msgs::Float64 plant_state1; //distance between robot 1 and robot 3
      std_msgs::Float64 a;
      std_msgs::Float64 b;
      a.data=phi.phi1*PI/180.0; //relative direction between robot 1 and robot 2 in radiance
      b.data=phi.phi2*PI/180.0; //relative direction between robot 1 and robot 3 in radiance
      plant_state.data=distance.l1;
      plant_state1.data=distance.l2;
      servo_state_pub.publish(plant_state);
      servo_state_pub1.publish(plant_state1);
      servo_state_pub2.publish(a);
      servo_state_pub3.publish(b);
      
      ros::spinOnce();
      rate.sleep();
    }
    
    
   
    
   
    
    

}