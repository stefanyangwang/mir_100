

/***************************************************************************/ /**
 * \file setpoint_node.cpp
 *
 * \brief Node that publishes time-varying setpoint values
 * \author Paul Bouchier
 * \date January 9, 2016
 *
 * \section license License (BSD-3)
 * Copyright (c) 2016, Paul Bouchier
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 * - Neither the name of Willow Garage, Inc. nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 ******************************************************************************/

#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include <geometry_msgs/Twist.h>

int main(int argc, char** argv)
{ 
  
  ros::init(argc, argv, "setpoint_node");
  ROS_INFO("Starting setpoint publisher");
  ros::NodeHandle setpoint_node;
  
  while (ros::ok() && ros::Time(0) == ros::Time::now())
  {
    ROS_INFO("Setpoint_node spinning, waiting for time to become non-zero");
    sleep(1);
  }
  
  
  ros::Publisher setpoint_pub = setpoint_node.advertise<std_msgs::Float64>("l1/setpoint", 10);
  ros::Publisher setpoint_pub1 = setpoint_node.advertise<std_msgs::Float64>("l2/setpoint", 10);
  ros::Publisher setpoint_pub2 = setpoint_node.advertise<std_msgs::Float64>("w1/setpoint", 10);
  ros::Publisher setpoint_pub3 = setpoint_node.advertise<std_msgs::Float64>("w2/setpoint", 10);

  ros::Rate loop_rate(50);  
  
  while (ros::ok())
  {
    
    std_msgs::Float64 setpointl1;
    std_msgs::Float64 setpointl2;
    std_msgs::Float64 setpointw1;
    std_msgs::Float64 setpointw2;
    setpointl1.data=3;
    setpointl2.data=3;
    setpointw1.data=1.5;
    setpointw2.data=4.7;
    setpoint_pub.publish(setpointl1);  
    setpoint_pub1.publish(setpointl2);
    setpoint_pub2.publish(setpointw1);
    setpoint_pub3.publish(setpointw2);
    ros::spinOnce();
    loop_rate.sleep();
  }
}
