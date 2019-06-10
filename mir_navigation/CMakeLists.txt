cmake_minimum_required(VERSION 2.8.3)
project(mir_navigation)

find_package(catkin REQUIRED COMPONENTS
  roslaunch
  roscpp
  std_msgs
  nav_msgs
  geometry_msgs
)
include_directories(include ${catkin_INCLUDE_DIRS})

###################################
## catkin specific configuration ##
###################################
catkin_package(
    INCLUDE_DIRS
    LIBRARIES
    CATKIN_DEPENDS roscpp std_msgs nav_msgs geometry_msgs
    DEPENDS
)
add_executable(radians2degree nodes/radians2degree.cpp)
target_link_libraries(radians2degree ${catkin_LIBRARIES})
add_dependencies(radians2degree ${catkin_EXPORTED_TARGETS})
add_executable(phi nodes/phi.cpp)
target_link_libraries(phi ${catkin_LIBRARIES})
add_dependencies(phi ${catkin_EXPORTED_TARGETS})
add_executable(distance nodes/distance.cpp)
target_link_libraries(distance ${catkin_LIBRARIES})
add_dependencies(distance ${catkin_EXPORTED_TARGETS})
add_executable(gamma nodes/gamma.cpp)
target_link_libraries(gamma ${catkin_LIBRARIES})
add_dependencies(gamma ${catkin_EXPORTED_TARGETS})

#############
## Install ##
#############

# all install targets should use catkin DESTINATION variables
# See http://ros.org/doc/api/catkin/html/adv_user_guide/variables.html

# Mark executable scripts (Python etc.) for installation
# in contrast to setup.py, you can choose the destination
install(PROGRAMS
  nodes/acc_finder.py
  nodes/min_max_finder.py
  scripts/plot_mprim.py
  DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

## Mark executables and/or libraries for installation
 install(TARGETS radians2degree phi distance gamma
   ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
   RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
 )
 
## Mark cpp header files for installation
# install(DIRECTORY include/${PROJECT_NAME}/
#   DESTINATION ${CATKIN_PACKAGE_INCLUDE_DESTINATION}
#   FILES_MATCHING PATTERN "*.h"
#   PATTERN ".svn" EXCLUDE
# )

# Mark other files for installation (e.g. launch and bag files, etc.)
install(DIRECTORY
  config
  launch
  mprim
  rviz
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

#############
## Testing ##
#############

## Add gtest based cpp test target and link libraries
 #catkin_add_gtest(${radians2degree}-test src/mir_robot/mir_navigation/nodes/radians2degree.cpp)
 #if(TARGET ${radians2degree}-test)
  # target_link_libraries(${radians2degree}-test ${catkin_LIBRARIES})
 #endif()

## Add folders to be run by python nosetests
#catkin_add_nosetests(test)

roslaunch_add_file_check(launch)
