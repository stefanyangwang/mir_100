cmake_minimum_required(VERSION 2.8.3)
project(mir_gazebo)

find_package(catkin REQUIRED COMPONENTS
  roslaunch
  
)
include_directories(include ${catkin_INCLUDE_DIRS})
###################################
## catkin specific configuration ##
###################################
catkin_package(
    
)

#############
## Install ##
#############

# Mark other files for installation (e.g. launch and bag files, etc.)
install(DIRECTORY
  config
  launch
  maps
  sdf
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

#############
## Testing ##
#############


roslaunch_add_file_check(launch)
