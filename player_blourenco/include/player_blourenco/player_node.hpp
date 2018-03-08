#ifndef _PLAYER_NODE_HPP
#define _PLAYER_NODE_HPP

#include <algorithm>

#include <ros/ros.h>

#include "player_blourenco/player_manager.hpp"
#include "player_blourenco/player_updater.hpp"

#include "rws2018_msgs/MakeAPlay.h"
#include "rws2018_msgs/GameQuery.h"

class PlayerNode
{
public:
  PlayerNode(std::string name, std::vector<std::pair<TeamColor, std::string>> teams);

protected:
  bool respondToGameQuery(rws2018_msgs::GameQuery::Request &req, rws2018_msgs::GameQuery::Response &res);

  void step(const rws2018_msgs::MakeAPlay::ConstPtr &);
  void step();

  void move();
  void moveTo(Player &);
  void moveForward();

  void updatePlayers();
  void updateMyself();

private:
  ros::NodeHandle _nh;
  PlayerManager _manager;
  PlayerUpdater _updater;
  ros::Subscriber _sub;

  ros::ServiceServer _game_srv;

  std::string _name;
  Player &_me;

  float _speed;
  float _rotation = 0.2;

  Team _players;
  Team _team;
  Team _enemies;
  Team _preys;
};

#endif