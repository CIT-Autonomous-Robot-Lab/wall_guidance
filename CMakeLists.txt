################################################################################
# Set minimum required version of cmake, project name and compile options
################################################################################
cmake_minimum_required(VERSION 2.8.3)
project(wall_guidance)

################################################################################
# Find catkin packages and libraries for catkin and system dependencies
################################################################################
## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
)

catkin_package(
  #INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp std_msgs
)

include_directories(
  include
  ${catkin_INCLUDE_DIRS}
)

################################################################################
# Build
################################################################################
add_executable(simple_wall_guidance
  src/simple_wall_guidance.cpp
)
target_link_libraries(
  simple_wall_guidance
  ${catkin_LIBRARIES}
)
################################################################################
# Install
################################################################################
install(DIRECTORY src
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

################################################################################
# Test
################################################################################
