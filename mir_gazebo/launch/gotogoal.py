#!/usr/bin/env python
import rospy
from nav_msgs.msg import Odometry
from geometry_msgs.msg import Twist
#from geometry_msgs.msg import Pose
from math import pow, atan2, sqrt


class TurtleBot:

    def __init__(self):
        # Creates a node with name 'turtlebot_controller' and make sure it is a
        # unique node (using anonymous=True).
        rospy.init_node('speed_controller', anonymous=True)

        # Publisher which will publish to the topic '/turtle1/cmd_vel'.
        self.velocity_publisher = rospy.Publisher('/robot1/cmd_vel',
                                                  Twist, queue_size=10)
        self.velocity_publisher1 = rospy.Publisher('/robot2/cmd_vel',
                                                  Twist, queue_size=10)
        self.velocity_publisher2 = rospy.Publisher('/robot3/cmd_vel',
                                                  Twist, queue_size=10)
        

        # A subscriber to the topic '/turtle1/pose'. self.update_pose is called
        # when a message of type Pose is received.
        self.pose_subscriber = rospy.Subscriber('/robot1/base_pose_ground_truth',
                                                Odometry, self.update_pose)
        

        self.pose = Odometry()
       
        self.rate = rospy.Rate(100)

    def update_pose(self, data):
        """Callback function which is called when a new message of type Pose is
        received by the subscriber."""
        self.pose = data
        self.pose.pose.pose.position.x = round(self.pose.pose.pose.position.x, 4)
        self.pose.pose.pose.position.y = round(self.pose.pose.pose.position.y, 4)
    
    def euclidean_distance(self, goal_pose):
        """Euclidean distance between current pose and the goal."""
        return sqrt(pow((goal_pose.pose.pose.position.x - self.pose.pose.pose.position.x), 2) +
                    pow((goal_pose.pose.pose.position.y - self.pose.pose.pose.position.y), 2))
    
    def linear_vel(self, goal_pose, constant=1.5):
        """See video: https://www.youtube.com/watch?v=Qh15Nol5htM."""
        return constant * self.euclidean_distance(goal_pose)
    
    def steering_angle(self, goal_pose):
        """See video: https://www.youtube.com/watch?v=Qh15Nol5htM."""
        return atan2(goal_pose.pose.pose.position.y - self.pose.pose.pose.position.y, goal_pose.pose.pose.position.x - self.pose.pose.pose.position.x)
    
    def angular_vel(self, goal_pose, constant=6):
        """See video: https://www.youtube.com/watch?v=Qh15Nol5htM."""
        return constant * (self.steering_angle(goal_pose) - self.pose.pose.pose.orientation.z)

    def move2goal(self):
        """Moves the turtle to the goal."""
        goal_pose = Odometry()
        

        # Get the input from the user.
        goal_pose.pose.pose.position.x = input("Set your x goal: ")
        goal_pose.pose.pose.position.y = input("Set your y goal: ")
        

        # Please, insert a number slightly greater than 0 (e.g. 0.01).
        distance_tolerance = input("Set your tolerance: ")

        vel_msg = Twist()
        

        while self.euclidean_distance(goal_pose) >= distance_tolerance  :

            # Porportional controller.
            # https://en.wikipedia.org/wiki/Proportional_control

            # Linear velocity in the x-axis.
            vel_msg.linear.x = self.linear_vel(goal_pose)
            vel_msg.linear.y = 0
            vel_msg.linear.z = 0

            # Angular velocity in the z-axis.
            vel_msg.angular.x = 0
            vel_msg.angular.y = 0
            vel_msg.angular.z = self.angular_vel(goal_pose)

            # Publishing our vel_msg
            self.velocity_publisher.publish(vel_msg)
            self.velocity_publisher1.publish(vel_msg)
            self.velocity_publisher2.publish(vel_msg)
            

            # Publish at the desired rate.
            self.rate.sleep()

        # Stopping our robot after the movement is over.
        vel_msg.linear.x = 0
        vel_msg.angular.z = 0
        self.velocity_publisher.publish(vel_msg)
        self.velocity_publisher1.publish(vel_msg)
        self.velocity_publisher2.publish(vel_msg)
        

        # If we press control + C, the node will stop.
        

if __name__ == '__main__':
    try:
        x = TurtleBot()
        x.move2goal()
        
    except rospy.ROSInterruptException:
        pass