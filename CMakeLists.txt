cmake_minimum_required(VERSION 3.0.2)
project(grd_tracking)


add_compile_options(-std=c++14)

find_package(catkin REQUIRED COMPONENTS cv_bridge roscpp sensor_msgs std_msgs darknet_ros_msgs)

find_package(OpenCV REQUIRED)


include_directories( include ${catkin_INCLUDE_DIRS} ${OpenCV_INCLUDE_DIRS} )

add_executable(${PROJECT_NAME} src/tracking.cpp src/tracking_node.cpp include/grd_tracking/tracking.h ${OpenCV_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${catkin_LIBRARIES} ${OpenCV_LIBS})

add_dependencies(${PROJECT_NAME} ${${PROJECT_NAME}_EXPORTED_TARGETS} ${catkin_EXPORTED_TARGETS})