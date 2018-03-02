#include <ros/ros.h>

#include "player_blourenco/player_node.hpp"

#include <tf/transform_listener.h>

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "blourenco");

  PlayerNode player("blourenco");
  // this does not work, why?
  // auto player = PlayerNode("blourenco");

  // player.start();

  ros::spin();

  return 0;
}
