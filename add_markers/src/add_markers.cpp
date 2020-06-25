#include <ros/ros.h>
#include <geometry_msgs/PoseWithCovarianceStamped.h>
#include <visualization_msgs/Marker.h>


ros::Publisher marker_pub ;
visualization_msgs::Marker marker;

float pickUp[3]={6.0, 1.0, 1.0};
float dropOff[3]={-6.0, 3.0, 1.0};


bool atpickup = false;
bool atdropoff = false;
bool carrying = false;
bool droppingOff();
bool carryingCube();
bool between();

void callback(const geometry_msgs::PoseWithCovarianceStamped::ConstPtr& msg)
{
    //checking the location
    if((std::abs(pickUp[0] - msg->pose.pose.position.x) < 0.2) && (std::abs(pickUp[1] - msg->pose.pose.position.y) < 0.2))
        {
            atpickup = true;
            atdropoff=false;
            carryingCube();

        
        }
    
    if(std::abs(dropOff[0] - msg->pose.pose.position.x) < 0.2 && std::abs(dropOff[1] - msg->pose.pose.position.y) < 0.2)
    {
        atdropoff= true;
        atpickup=false;
        droppingOff();
        
    }

    else{
      atpickup= false;
      atdropoff=false;
    
      between();

    
    }
}





int main( int argc, char** argv )
{
  ros::init(argc, argv, "add_markers");
  ros::NodeHandle n;
  ros::Rate r(5);
  marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 10);

  // Subscribing to AMCL POSE for better accuracy
  ros::Subscriber odom_sub = n.subscribe("/amcl_pose", 1000, callback);

  // Set our initial shape type to be a cube
  uint32_t shape = visualization_msgs::Marker::CUBE;
   
    // Set the frame ID and timestamp.  See the TF tutorials for information on these.
    marker.header.frame_id = "map";
    marker.header.stamp = ros::Time::now();

    // Set the namespace and id for this marker.  This serves to create a unique ID
    // Any marker sent with the same namespace and id will overwrite the old one
    marker.ns = "basic_shapes";
    marker.id = 0;

    // Set the marker type.  Initially this is CUBE, and cycles between that and SPHERE, ARROW, and CYLINDER
    marker.type = visualization_msgs::Marker::CUBE;

    // Set the marker action.  Options are ADD, DELETE, and new in ROS Indigo: 3 (DELETEALL)
   


    // Set the scale of the marker -- 1x1x1 here means 1m on a side
    marker.scale.x = 1.0;
    marker.scale.y = 1.0;
    marker.scale.z = 1.0;

    // Set the color -- be sure to set alpha to something non-zero!
    marker.color.r = 0.0f;
    marker.color.g = 1.0f;
    marker.color.b = 0.0f;
    marker.color.a = 1.0;

    marker.lifetime = ros::Duration();


 
   
   
   ros::spin();
}



    // Publish the marker according to situation
bool between()
{

    if(!atpickup && !carrying)
    {
    marker.pose.position.x = pickUp[0];
    marker.pose.position.y = pickUp[1];
    marker.pose.position.z = pickUp[2];
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    marker.action = visualization_msgs::Marker::ADD;
      if(!atdropoff)
      {
      marker_pub.publish(marker);
      }
    } 

    return true;
}

bool carryingCube()
{
   if(atpickup && !carrying)

    {
        ros::Duration(3.5).sleep();
        marker.action = visualization_msgs::Marker::DELETE;
        marker_pub.publish(marker);
        carrying= true;
     
    }
    return true;
}

bool droppingOff()
{
   if (atdropoff && carrying)
    {
     marker.pose.position.x =dropOff[0];
    marker.pose.position.y = dropOff[1];
    marker.pose.position.z = dropOff[2];
    marker.pose.orientation.x = 0.0;
    marker.pose.orientation.y = 0.0;
    marker.pose.orientation.z = 0.0;
    marker.pose.orientation.w = 1.0;
    ros::Duration(3.5).sleep();
    marker.action = visualization_msgs::Marker::ADD;
    carrying=false;
    marker_pub.publish(marker);

    }

    return true;
   

}