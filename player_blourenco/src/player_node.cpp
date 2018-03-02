#include "player_blourenco/player_node.hpp"

PlayerNode::PlayerNode(std::string name) : _name(name)
{
  // get team members
  _nh.getParam("/team_blue", _teams.blue);
  _nh.getParam("/team_red", _teams.red);
  _nh.getParam("/team_green", _teams.green);
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

  _marker_pub = _nh.advertise<visualization_msgs::Marker>("/bocas", 1);
}

void PlayerNode::makeAPlay(const rws2018_msgs::MakeAPlayConstPtr& msg)
{
  auto max_speed = msg->cheetah;

  auto delta = tf::Transform{};

  delta.setOrigin(tf::Vector3{ max_speed, 0, 0 });
  auto q = tf::Quaternion{};
  q.setRPY(0, 0, 0.1);
  delta.setRotation(q);

  _position *= delta;

  publishPosition();
  publishMarker();
}

void PlayerNode::publishPosition()
{
  _br.sendTransform(tf::StampedTransform{ _position, ros::Time::now(), "world", _name });
}

void PlayerNode::publishMarker()
{
  auto marker = visualization_msgs::Marker{};

  marker.header.frame_id = _name;
  marker.header.stamp = ros::Time();
  marker.type = visualization_msgs::Marker::TEXT_VIEW_FACING;
  marker.action = visualization_msgs::Marker::ADD;

  marker.scale.z = 0.4;
  marker.color.a = 1.0;
  marker.color.r = 1.0;
  marker.color.g = 0.0;
  marker.color.b = 1.0;

  marker.text = piadas_secas[(piada_id++ / 50) % piadas_secas.size()];

  _marker_pub.publish(marker);
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