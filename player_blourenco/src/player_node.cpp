#include "player_blourenco/player_node.hpp"

PlayerNode::PlayerNode(std::string name) : _name(name)
{
}

void PlayerNode::start()
{
  float x = randomPosition();
  float y = randomPosition();
  _position.setOrigin(tf::Vector3{ x, y, 0 });
  auto q = tf::Quaternion{};
  q.setRPY(0, 0, 0);
  _position.setRotation(q);

  publishPosition();
  _make_a_move_sub = _nh.subscribe<rws2018_msgs::MakeAPlay>("/make_a_play", 10, &PlayerNode::makeAPlay, this);
}

void PlayerNode::makeAPlay(const rws2018_msgs::MakeAPlayConstPtr& msg)
{
  auto max_speed = msg->cheetah;

  auto delta = tf::Transform{};

  delta.setOrigin(tf::Vector3{ 0.1, 0, 0 });
  auto q = tf::Quaternion{};
  q.setRPY(0, 0, 0.1);
  delta.setRotation(q);

  _position *= delta;

  publishPosition();
}

void PlayerNode::publishPosition()
{
  _br.sendTransform(tf::StampedTransform{ _position, ros::Time::now(), "world", _name });
}

float PlayerNode::randomPosition()
{
  using namespace std::chrono_literals;

  auto now = std::chrono::system_clock::now();
  auto seed = now.time_since_epoch() / 1us;

  auto generator = std::default_random_engine{ seed };
  auto distribution = std::uniform_real_distribution<float>{ -5.0f, 5.0f };

  return distribution(generator);
}