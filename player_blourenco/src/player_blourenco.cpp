#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include <ros/ros.h>

#include <tf/transform_broadcaster.h>

#include "player_blourenco/player_node.hpp"

#include "rws2018_libs/team.h"

#include "rws2018_msgs/MakeAPlay.h"

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "blourenco");

  auto player = PlayerNode{ "blourenco" };

  player.start();

  ros::spin();

  return 0;
}
