# mir_100

This programm can make three mobile robots moving in a formation.I make them right now moving in a line to each other.
To start it must make three files launch:


1.roslaunch pid roboterpid.launch
2.roslaunch mir_gazebo mir_empty_world.launch
3.roslaunch mir_gazebo nodes.launch



Mir_empty_world is used to start the robot models(which is three robots staying in a line ,2 meter and 90 degree to each other).


nodes.launch is used to start the relevant nodes that generate the parameter which are used in the algorithm. 


Roboterpid is used for pid control in the programm to make sure that the relativ distance and degree to each other are not changing during the moving.


In roboterpid we can change the PID parameter as we want,in this case I use the PD controller. Also for the node(setpoint_node) in pid package we can change the relativ formation of the robots to each other.Parameter setpointl1,setpointl2 are distance of the slave robots to the master. Setpointw1,setpointw2 are the relativ degree which written in radian in absolute coordinate. 
