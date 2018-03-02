#ifndef _PLAYER_NODE_HPP
#define _PLAYER_NODE_HPP

#include <algorithm>
#include <map>
#include <string>

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include "rws2018_msgs/MakeAPlay.h"

enum class Team : int
{
  Red,
  Green,
  Blue,
};

class PlayerNode
{
public:
  PlayerNode(std::string name);

  void start();

protected:
private:
  std::string _name;

  std::string _team;

  struct Player
  {
    std::string name;
    Team team;
  };

  std::vector<Player> _players;

  ros::NodeHandle _nh;

  tf::TransformBroadcaster _tf_bf;
  tf::TransformListener _tf_lt;

  ros::Subscriber _make_a_move_sub;
  tf::Transform _transform;
};

#endif