#!/bin/sh
xterm  -e  "source /opt/ros/kinetic/setup.bash; source /home/shimon/udacity-robotics/catkin_ws/devel/setup.bash; export TURTLEBOT_GAZEBO_WORLD_FILE='$(rospack find turtlebot_gazebo)/worlds/myworld.world'; roslaunch turtlebot_gazebo turtlebot_world.launch " &
sleep 5
xterm  -e  "source /opt/ros/kinetic/setup.bash; source /home/shimon/udacity-robotics/catkin_ws/devel/setup.bash; roslaunch turtlebot_gazebo gmapping_demo.launch  " & 
sleep 5
xterm  -e  " source /opt/ros/kinetic/setup.bash; source /home/shimon/udacity-robotics/catkin_ws/devel/setup.bash; roslaunch turtlebot_rviz_launchers view_navigation.launch" &
sleep 5
xterm -e   "source /opt/ros/kinetic/setup.bash; source /home/shimon/udacity-robotics/catkin_ws/devel/setup.bash; roslaunch turtlebot_teleop keyboard_teleop.launch "