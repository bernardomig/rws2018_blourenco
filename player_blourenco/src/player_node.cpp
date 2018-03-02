#include "player_blourenco/player_node.hpp"

PlayerNode::PlayerNode(std::string name) : _name(name)
{
}

void PlayerNode::start()
{
  _make_a_move_sub = _nh.subscribe<rws2018_msgs::MakeAPlay>("/make_a_play", 10, &PlayerNode::makeAPlay, this);
}

void PlayerNode::makeAPlay(const rws2018_msgs::MakeAPlayConstPtr& msg)
{
  updatePosition(4 * std::cos(_a), 2 * std::sin(_a), _a);

  _a += 0.1;

  ROS_INFO("I'm %s and I am a moon (~_~;)", _name.c_str());
}

void PlayerNode::updatePosition(float x, float y, float a)
{
  auto transform = tf::Transform{};
  transform.setOrigin(tf::Vector3{ 4 * std::cos(a), 2 * std::sin(a), 0 });
  auto q = tf::Quaternion{};
  q.setRPY(0, 0, a);
  transform.setRotation(q);
  _br.sendTransform(tf::StampedTransform{ transform, ros::Time::now(), "world", _name });
}