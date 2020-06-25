The Home Service Robot was build up using following ROS packages:
1. turtlebot
2. turtlebot_gazebo
3. turtlebot_teleop
4. gmapping

The map of the custom made world was created with spawned into the gazebo world and visualized in rviz. The Robot
is manually moved through the environment using turtlebot_teleop package for mapping. The gmapping package was used 
for performing the SLAM and map was saved. 
The map generated was used by map_server for Localization and Navigation. This was done using ROS Navigation stack . The navigation package uses
AMCL to perform navigation and localisation. Using the move_base package , we are able to send navigation goals to the robot via rviz.
The robot was successfuly able to navigate towards the given goals. ROS navigation stack creates a path for your robot based on 
Dijkstra's algorithm. 
Next, navigation goal node named pick_objects was created which will send navigation goal commands to the robot. It utilizes move_base_msgs
 and actionlib . This node was able to navigate the robot from pickup goal to dropoff goal.


 A virtual object was created in rviz to represent the object being transported. This was done by creating add_markers node which utilizes
visualization_msgs. (Another seperate/duplicate node is created which just displays the marker 5 seconds  to satisfy project rubric - marker_initial_test)
Later, the pick_objects node and add_markers node are made to communicate with each other to make the marker get appear and dissappear at appropriate times.
add_markers node also used amcl_pose topic inorder to identify the position and when to the display the marker. (This can also be done using other methods)
Also, a seperate rviz config file was created to accomodate the marker. 

Finally, the robot was able to pick 'marker' from pickup location and transport it to the dropoff location!
(The marker is displayed some seconds after reaching the dropoff location to get the feel of dropping off)

Note: Inorder to ace the launch of different launch files and nodes home_service.sh shell script was written and executed using xterm.
Please note to SET the environment variables if world, map files are giving errors. 

