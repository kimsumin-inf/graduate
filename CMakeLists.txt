cmake_minimum_required(VERSION 3.0.2)
project(grd_tracking)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  sensor_msgs
  std_msgs
  darknet_ros
  cv_bridge
)

find_package(OpenCV REQUIRED)

catkin_package()


include_directories(
# include
  ${catkin_INCLUDE_DIRS}
  ${OpenCV_INCLUDE_DIRS}
)


add_executable(${PROJECT_NAME} src/tracking_node.cpp src/tracking.cpp include/grd_tracking/tracking.h)

target_link_libraries(${PROJECT_NAME}
  ${catkin_LIBRARIES}
  ${OpenCV_LIBS}
)

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})
