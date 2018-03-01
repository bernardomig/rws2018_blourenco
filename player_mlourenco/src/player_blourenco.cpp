#include <algorithm>
#include <iostream>
#include <vector>

#include <ros/ros.h>

#include <tf/transform_broadcaster.h>

#include "player_blourenco/player.hpp"
#include "player_blourenco/team.hpp"
#include "player_blourenco/teamcolor.hpp"

#include "rws2018_libs/team.h"

tf::TransformBroadcaster br;

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "blourenco");

  auto nh = ros::NodeHandle{};

  auto transform = tf::Transform{};

  auto rate = ros::Rate{ 10 };

  while (ros::ok())
  {
    transform.setOrigin(tf::Vector3{ 7, 7, 0 });
    auto q = tf::Quaternion{};
    q.setRPY(0, 0, M_PI / 2);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform{ transform, ros::Time::now(), "world", "blourenco" });
    rate.sleep();
    ros::spinOnce();
  }

  return 0;
}
