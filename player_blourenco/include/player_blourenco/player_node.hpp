#ifndef _PLAYER_NODE_HPP
#define _PLAYER_NODE_HPP

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>

#include "rws2018_msgs/MakeAPlay.h"

class PlayerNode
{
public:
  PlayerNode(std::string name);

  void start();

protected:
  void makeAPlay(const rws2018_msgs::MakeAPlayConstPtr& msg);

  void updatePosition(float x, float y, float a);

private:
  std::string _name;
  ros::NodeHandle _nh;
  tf::TransformBroadcaster _br;
  ros::Subscriber _make_a_move_sub;
  float _a = 0.0f;
};

#endif