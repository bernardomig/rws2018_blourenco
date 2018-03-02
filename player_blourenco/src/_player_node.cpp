#include "player_blourenco/player_node.hpp"

PlayerNode::PlayerNode(std::string name) : _name(name)
{
  // get team members
  _nh.getParam("/team_blue", _teams.blue);
  _nh.getParam("/team_red", _teams.red);
  _nh.getParam("/team_green", _teams.green);

  auto _in_team_blue = std::find(_teams.blue.begin(), _teams_blue.end(), _name) != _teams.blue.end();
  auto _in_team_red = std::find(_teams.red.begin(), _teams_blue.end(), _name) != _teams.red.end();
  auto _in_team_green = std::find(_teams.green.begin(), _teams_blue.end(), _name) != _teams.green.end();
}

void PlayerNode::start()
{
  static tf::TransformListener _listener;
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

void PlayerNode::updatePosition()
{
  float angle;
  if (findOtherPlayer("lsarmento", angle))
  {
    auto delta = tf::Transform{};

    delta.setOrigin(tf::Vector3{ 2, 0, 0 });
    auto q = tf::Quaternion{};
    q.setRPY(0, 0, angle / 10);
    delta.setRotation(q);

    _position *= delta;
  }
}

bool PlayerNode::findOtherPlayer(std::string player_name, float& angle)
{
  static tf::TransformListener _listener;
  auto transform = tf::StampedTransform{};
  try
  {
    // _listener.waitForTransform(player_name, _name, ros::Time(0), ros::Duration(10));
    _listener.lookupTransform(player_name, _name, ros::Time(0), transform);
    angle = std::atan2(transform.getOrigin().y(), transform.getOrigin().x());
    ROS_INFO("found %s", player_name.c_str());
    return true;
  }
  catch (tf::LookupException& ex)
  {
    ROS_ERROR("didn't found %s: %s", player_name.c_str(), ex.what());
    return false;
  }
}

void PlayerNode::makeAPlay(const rws2018_msgs::MakeAPlayConstPtr& msg)
{
  max_speed = msg->cheetah;

  updatePosition();

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

  marker.scale.z = 0.3;
  marker.color.a = 1.0;
  marker.color.r = 1.0;
  marker.color.g = 0.0;
  marker.color.b = 1.0;

  //   marker.text = piadas_secas[(piada_id++ / 50) % piadas_secas.size()];
  marker.text = "here I go";

  _marker_pub.publish(marker);
}

float PlayerNode::randomPosition()
{
  auto now = std::chrono::system_clock::now();
  auto seed = now.time_since_epoch() / std::chrono::microseconds(1);

  auto generator = std::default_random_engine{ seed };
  auto distribution = std::uniform_real_distribution<float>{ -5.0f, 5.0f };

  return distribution(generator);
}