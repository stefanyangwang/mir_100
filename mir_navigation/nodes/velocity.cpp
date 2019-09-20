#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <nav_msgs/Odometry.h>
#include <geometry_msgs/Twist.h>
ros::Publisher pub;
ros::Publisher pub1;
const double PI=3.1415926;

class ga { //parameter gamma
  
    
  public:
    double g1;// gamma 1 for robot 2
    double g2;// gamma 2 for robot 3
    ga(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("gamma",1000,&ga::poseCallback,this);
    }
    void poseCallback(const geometry_msgs::Twist::ConstPtr& msg) 
    {   
   
    g1 = msg->linear.x;
    g2 = msg->linear.y;
    
    
    }
    ros::Subscriber pose_subscriber;
};
class piddistance {// the result of the PID-controller for the distance between robots
  
    
  public:
    double l1;// the result of the PID-controller for the variable of distance between robot 1 and robot 2
    double l2;// the result of the PID-controller for the variable of distance between robot 1 and robot 3
    piddistance(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("piddistance",1000,&piddistance::poseCallback,this);
    }
    void poseCallback(const geometry_msgs::Twist::ConstPtr& msg) 
    {   
   
    l1 = msg->linear.x;
    l2 = msg->linear.y;
    
    
    }
    ros::Subscriber pose_subscriber;
};
class piddegree {// the result of the PID-controller for the relative angle between robots
  
    
  public:
    double w1;// the result of the PID-controller for the variable of relative angle between robot 1 and robot 2
    double w2;// the result of the PID-controller for the variable of relative angle between robot 1 and robot 3
    piddegree(ros::NodeHandle *n){
     
      pose_subscriber=n->subscribe("piddegree",1000,&piddegree::poseCallback,this);
    }
    void poseCallback(const geometry_msgs::Twist::ConstPtr& msg) 
    {   
   
    w1 = msg->linear.x;
    w2 = msg->linear.y;
    
    
    }
    ros::Subscriber pose_subscriber;
};
class distance {
  
    
  public:
    double l1;//distance between robot 1 and robot 2
    double l2;//distance between robot 1 and robot 3
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
    double phi1;//relative angle between robot 1 and robot 2 in degree
    double phi2;//relative angle between robot 1 and robot 3 in degree
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
class velocity1 {
  
    
  public:
    double v1;//linear velocity of robot 1
    double w1;//angular velocity of robot 1
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
    ros::init(argc,argv,"velocity");
    ros::NodeHandle n;
    pub=n.advertise<geometry_msgs::Twist>("/robot2/cmd_vel",10);
    pub1=n.advertise<geometry_msgs::Twist>("/robot3/cmd_vel",10);
    
    ros::Rate rate(50);
    ga gamma(&n);
    distance distance(&n);
    piddistance piddistance(&n);
    piddegree piddegree(&n);
    phi phi(&n);
    velocity1 velocity1(&n);
    while(ros::ok()){
      
      std_msgs::Float64 a;
      std_msgs::Float64 b;
      std_msgs::Float64 c;
      std_msgs::Float64 d;
      std_msgs::Float64 e;
      std_msgs::Float64 f;
      geometry_msgs::Twist velocity2;// liear and angular velocity for robot 2
      geometry_msgs::Twist velocity3;// liear and angular velocity for robot 3
      a.data=gamma.g1*PI/180.0;
      b.data=gamma.g2*PI/180.0;
      c.data=phi.phi1*PI/180.0;// realtive angle between robot 1 and robot 2 in radiance
      d.data=phi.phi2*PI/180.0;// realtive angle between robot 1 and robot 3 in radiance
      e.data=(piddistance.l1+velocity1.v1*cos(c.data))/cos(a.data);
      f.data=(piddistance.l2+velocity1.v1*cos(d.data))/cos(b.data);
      velocity2.angular.z=(cos(a.data)/0.45)*(distance.l1*piddegree.w1-velocity1.v1*sin(c.data)+distance.l1*velocity1.w1+e.data*sin(a.data));
      velocity2.linear.x=e.data-0.45*velocity2.angular.z*tan(a.data);
      velocity3.angular.z=(cos(b.data)/0.45)*(distance.l2*piddegree.w2-velocity1.v1*sin(d.data)+distance.l2*velocity1.w1+f.data*sin(b.data));
      velocity3.linear.x=f.data-0.45*velocity3.angular.z*tan(b.data);
      
      pub.publish(velocity2);
      pub1.publish(velocity3);
      
      ros::spinOnce();
      rate.sleep();
    }
    
    
   
    
   
    
    

}