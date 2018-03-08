#ifndef _PLAYER_NODE_HPP
#define _PLAYER_NODE_HPP

#include <ros/ros.h>

#include "player_blourenco/player_manager.hpp"
#include "player_blourenco/player_updater.hpp"

#include "rws2018_msgs/MakeAPlay.h"
class PlayerNode
{
public:
  PlayerNode(std::string name, std::vector<std::pair<TeamColor, std::string>> teams);

  void report()
  {
    // ROS_INFO("I'm %s and my team is %i", _me.name().c_str(), (int)_me.team());

    tf::Vector3 pos = _me.transform().getOrigin();

    ROS_INFO("My position is (%f, %f)", pos.x(), pos.y());

    // ROS_INFO("My team is:");
    // for (Player& mate : _team)
    // {
    //   ROS_INFO("- %s [%s] [%f]", mate.name().c_str(), (mate.alive() ? "alive" : "dead"), _me.distanceTo(mate));
    // }

    // ROS_INFO("My enemies are:");
    // for (Player& enemy : _enemies)
    // {
    //   ROS_INFO("- %s [%s] [%f]", enemy.name().c_str(), (enemy.alive() ? "alive" : "dead"), _me.distanceTo(enemy));
    // }

    // ROS_INFO("My prays are:");
    // for (Player& prey : _preys)
    // {
    //   ROS_INFO("- %s [%s] [%f]", prey.name().c_str(), (prey.alive() ? "alive" : "dead"), _me.distanceTo(prey));
    // }
  }

protected:
  void step(const rws2018_msgs::MakeAPlay::ConstPtr&);
  void step();

  void move();
  void moveTo(Player&);

  void updatePlayers();
  void updateMyself();

private:
  ros::NodeHandle _nh;
  PlayerManager _manager;
  PlayerUpdater _updater;
  ros::Subscriber _sub;

  std::string _name;
  Player& _me;

  float _speed;
  float _rotation = 0.2;

  Team _players;
  Team _team;
  Team _enemies;
  Team _preys;
};

#endif