#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "math.h"

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
	int loopRate = 10;
    	ros::Rate loop_rate(loopRate);
    	ros::Time startTime = ros::Time::now();
    	int count = 0;

    	while (ros::ok()){
        	std_msgs::Float64 msg;
        	count++;
        	msg.data = sin(count/loopRate/1.7);
        	pub.publish(msg);
        	ros::spinOnce();
        	loop_rate.sleep();
    	}
}
