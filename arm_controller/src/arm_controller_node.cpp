#include "ros/ros.h"
#include <sensor_msgs/JointState.h>
#include "std_msgs/Float64.h"

void JointStateCallback(const sensor_msgs::JointState::ConstPtr& msg_js)
{
 ROS_INFO("Received JointState message");
  for (size_t i = 0; i < msg_js->position.size(); ++i) {
        ROS_INFO("Position of %s: %f",msg_js->name[i].c_str() , msg_js->position[i]);
    }
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "arm_controller_node");
  
	ros::NodeHandle n;

	ros::Publisher Joint0_Publisher = n.advertise<std_msgs::Float64>("arm/PositionJointInterface_J0_controller/command", 1);
	ros::Publisher Joint1_Publisher = n.advertise<std_msgs::Float64>("arm/PositionJointInterface_J1_controller/command", 1);
	ros::Publisher Joint2_Publisher = n.advertise<std_msgs::Float64>("arm/PositionJointInterface_J2_controller/command", 1);
	ros::Publisher Joint3_Publisher = n.advertise<std_msgs::Float64>("arm/PositionJointInterface_J3_controller/command", 1);

	ros::Rate loop_rate(10);
	ros::Subscriber JS_sub = n.subscribe("arm/joint_states", 10,JointStateCallback); 
	// the arm/joint_states is updated with a frequency of 100hz, meanwhile here the info is collected every 10Hz, so there are are 10 messages saved. 


	std_msgs::Float64 Joint0_Command,Joint1_Command,Joint2_Command,Joint3_Command;

// Here, we are assuming that the joints commands are given by terminal
	if (argc != 5) {
      ROS_INFO("Insert the correct number of desired joints positions");
      return 0;
  }
 	Joint0_Command.data = std::stod(argv[1]);	//stod converts from a string to a double
 	Joint1_Command.data = std::stod(argv[2]);
  Joint2_Command.data = std::stod(argv[3]);
 	Joint3_Command.data = std::stod(argv[4]);
            
  while (ros::ok())
	{

	  ROS_INFO("Sending position command to j0: %.2f", Joint0_Command.data);
	  Joint0_Publisher.publish(Joint0_Command);

	  ROS_INFO("Sending position command to j1: %.2f", Joint1_Command.data);        
		Joint1_Publisher.publish(Joint1_Command);

	  ROS_INFO("Sending position command to j2: %.2f", Joint2_Command.data);     
		Joint2_Publisher.publish(Joint2_Command);

	  ROS_INFO("Sending position command to j3: %.2f", Joint3_Command.data);  
		Joint3_Publisher.publish(Joint3_Command);	

		ros::spinOnce();
		loop_rate.sleep();
	} 

	return 0;
}