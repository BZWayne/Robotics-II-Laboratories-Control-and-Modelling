#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <vector>
#include <math.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <iostream>
#include <moveit_visual_tools/moveit_visual_tools.h>


// Main moveit libraries are included
int main(int argc, char **argv)
{
    ros::init(argc, argv, "move_group_interface_tutorial");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(0);
    spinner.start(); // For moveit implementation we need AsyncSpinner, we cant use ros::spinOnce()

    static const std::string PLANNING_GROUP = "robot_arm"; 
    moveit::planning_interface::MoveGroupInterface

    move_group(PLANNING_GROUP); // loading move_group
    const robot_state::JointModelGroup *joint_model_group = move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP); 

    geometry_msgs::PoseStamped current_pose;
    geometry_msgs::PoseStamped target_pose; // Pose in ROS is implemented using geometry_msgs::PoseStamped, google what is the type of this msg
    current_pose = move_group.getCurrentPose(); /* Retrieving the information about the current position and orientation of the end effector*/
    target_pose = current_pose;
    ros::Rate loop_rate(50); //Frequency
    std::vector<geometry_msgs::PoseStamped> arr_points;
    
    float x_c, y_c, rad, rad_squared, val, x_val;
    rad = 0.4;
    rad_squared = rad*rad;
    x_c = target_pose.pose.position.x - rad; //centers
    y_c = target_pose.pose.position.y;  
    
    for (x_val = target_pose.pose.position.x; x_val >= x_c - rad; x_val -= 0.1) 
        { 
            target_pose.pose.position.x = x_val;
	    val = sqrt((rad_squared - (x_val-x_c)*(x_val-x_c)));
            target_pose.pose.position.y = y_c - val;
	    arr_points.push_back(target_pose);
        }
    
    for (x_val = target_pose.pose.position.x; x_val <= x_c + rad; x_val += 0.1) 
        { 
            target_pose.pose.position.x = x_val;
	    val = sqrt((rad_squared - (x_val-x_c)*(x_val-x_c)));
            target_pose.pose.position.y = y_c + val;
	    arr_points.push_back(target_pose);
        }
    
    while (ros::ok())
    {
        for (std::size_t i = 0; i < arr_points.size(); i++) 
        { 
            move_group.setApproximateJointValueTarget(arr_points[i]); 
            move_group.move(); 
        }
           
        loop_rate.sleep();            
    }
    
    ROS_INFO("Done");
    ros::shutdown();
    return 0;
}
