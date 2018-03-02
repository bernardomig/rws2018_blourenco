#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

#include <ros/ros.h>

#include <tf/transform_broadcaster.h>

#include "player_blourenco/player.hpp"

#include "rws2018_libs/team.h"

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "blourenco");

  auto nh = ros::NodeHandle{};

  auto rate = ros::Rate{ 30 };

  tf::TransformBroadcaster br;

  auto a = 0.0f;

  while (ros::ok())
  {
    auto transform = tf::Transform{};
    transform.setOrigin(tf::Vector3{ 4 * std::cos(a), 2 * std::sin(a), 0 });
    auto q = tf::Quaternion{};
    q.setRPY(0, 0, a);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform{ transform, ros::Time::now(), "world", "blourenco" });
    rate.sleep();
    ros::spinOnce();

    ROS_INFO("I'm blourenco and I am a moon (~_~;)");

    a += 0.1;
  }

  return 0;
}
