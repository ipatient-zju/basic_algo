cmake_minimum_required(VERSION 2.8.3)
project(sensor_fusion_common)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  geometry_msgs
  message_generation
  roscpp
  std_msgs
)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

add_message_files(
  FILES
  DoubleArrayStamped.msg
  ExtEkf.msg
  ExtState.msg
)

generate_messages(
  DEPENDENCIES geometry_msgs std_msgs
)

catkin_package(
    DEPENDS
    CATKIN_DEPENDS  geometry_msgs
    INCLUDE_DIRS # TODO include
    LIBRARIES # TODO
)

include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)
