#ifndef _PLAYER_NODE_HPP
#define _PLAYER_NODE_HPP

#include <algorithm>
#include <chrono>
#include <random>

#include <ros/ros.h>
#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include <visualization_msgs/Marker.h>

#include "rws2018_msgs/MakeAPlay.h"

class PlayerNode
{
public:
  PlayerNode(std::string name);

  void start();

protected:
  void updatePosition();
  bool findOtherPlayer(std::string, tf::StampedTransform&);

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

  float max_speed;

  // garbage, plz remove
  struct
  {
    std::vector<std::string> red, green, blue;
  } _teams;

  std::vector<std::string> piadas_secas = { "O que diz o hidrogenio quando vai para a esquadra?\n- Tenho direito a uma "
                                            "ligacao?",
                                            "Os humanos sao seres de habitos,\nespecialmente os monges.",
                                            "O que e que um tubarao diz para o outro?\n- Tubaralhas-me.",
                                            "O que e que a galinha foi fazer na igreja?\n-Assistir a Missa do Galo.",
                                            "Para que servem oculos verdes?\n- Para verde perto." };
  int piada_id = 0;
};

#endif