#ifndef _PLAYER_NODE_HPP
#define _PLAYER_NODE_HPP

#include <algorithm>
#include <chrono>
#include <random>

using namespace std::literals;

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

#include <visualization_msgs/Marker.h>

#include "rws2018_msgs/MakeAPlay.h"

class PlayerNode
{
public:
  PlayerNode(std::string name);

  void start();

protected:
  void makeAPlay(const rws2018_msgs::MakeAPlayConstPtr& msg);

  void publishPosition();
  void publishMarker();

  float randomPosition();

private:
  std::string _name;
  ros::NodeHandle _nh;
  ros::Publisher _marker_pub;
  tf::TransformBroadcaster _br;
  ros::Subscriber _make_a_move_sub;
  tf::Transform _position;
  struct
  {
    std::vector<std::string> red, green, blue;
  } _teams;
};

#endif