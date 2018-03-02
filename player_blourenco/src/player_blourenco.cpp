#include <ros/ros.h>

#include "player_blourenco/player.hpp"

#include <tf/transform_listener.h>

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "blourenco");

  auto player = Player{ "blourenco", TeamColor::Blue };

  ROS_INFO("Player %s of team %i", player.name().c_str(), (int)player.team());

  return 0;
}
