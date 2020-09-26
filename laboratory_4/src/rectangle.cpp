#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
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
    const robot_state::JointModelGroup *joint_model_group = move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP); //For joint control

    geometry_msgs::PoseStamped current_pose;
    geometry_msgs::PoseStamped target_pose; 
    current_pose = move_group.getCurrentPose(); 
    target_pose = current_pose;
    ros::Rate loop_rate(50); 

    float directions[5][2] = {{2.0 , -1.0}, {1.0, -1.0}, {1.0, -2.0}, {2.0, -2.0}, {2.0, -1.0}};

    while (ros::ok())
    {
        for (int i = 0; i < sizeof(directions)/sizeof(directions[0]); i++) 
        { 
            target_pose.pose.position.x = directions[i][0];
            target_pose.pose.position.y = directions[i][1];

            std::cout << target_pose.pose.position.x  << "X\n";
            std::cout << target_pose.pose.position.y  << "Y\n";

            move_group.setApproximateJointValueTarget(target_pose); 
            move_group.move(); // Move the robot
        }
        
        current_pose = move_group.getCurrentPose();

        if ((abs(current_pose.pose.position.x - target_pose.pose.position.x) < 0.1) && (abs(current_pose.pose.position.y - target_pose.pose.position.y) < 0.1)) 
        {
            break; // Basically, check if we reached the desired position
        }    
        loop_rate.sleep();            
    }

    ROS_INFO("%f", current_pose.pose.position.x);
    ROS_INFO("%f", current_pose.pose.position.y);
    ROS_INFO("%f", current_pose.pose.position.z);
    
    ROS_INFO("Done");
    ros::shutdown();
    return 0;
}
