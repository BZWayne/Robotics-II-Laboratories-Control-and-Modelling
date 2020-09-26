#include "ros/ros.h"
#include "std_msgs/Float64.h"

float x;

void jointCallback(const std_msgs::Float64 msg)
{
  x = msg.data;
}

int main(int argc, char **argv){

	ros::init(argc, argv, "rotate");
    	ros::NodeHandle nh;
    	ros::Publisher pub = nh.advertise<std_msgs::Float64>("/robot/joint1_position_controller/command", 100); 
	ros::Subscriber sub = nh.subscribe("/robot/result", 1000, jointCallback);
    	ros::Rate loop_rate(0.5);
    	ros::Time startTime = ros::Time::now();
    	bool P = false;

    	while (ros::ok()){
        	std_msgs::Float64 msg;
       
        	if (P){
            		msg.data = 0.0;
        	} else {
            		msg.data = 1.0;
        	}

        	P=!P;
        	pub.publish(msg);
        	ROS_INFO("isMoving");

        	ros::spinOnce();
        	loop_rate.sleep();
   	 }
}
