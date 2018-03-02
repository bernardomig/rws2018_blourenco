#include <algorithm>
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

  auto rate = ros::Rate{ 10 };

  tf::TransformBroadcaster br;

  while (ros::ok())
  {
    auto transform = tf::Transform{};
    transform.setOrigin(tf::Vector3{ 7, 7, 0 });
    auto q = tf::Quaternion{};
    q.setRPY(0, 0, M_PI / 2);
    transform.setRotation(q);
    br.sendTransform(tf::StampedTransform{ transform, ros::Time::now(), "world", "blourenco" });
    rate.sleep();
    ros::spinOnce();

    ROS_INFO("I'm blourenco and my team is team_read");
  }

  return 0;
}
