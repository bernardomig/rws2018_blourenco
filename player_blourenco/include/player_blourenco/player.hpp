#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>

#include <tf/LinearMath/Transform.h>

#include "player_blourenco/team_color.hpp"

class Player
{
public:
  Player(std::string name, TeamColor team);

  const std::string& name() const;
  const TeamColor& team() const;
  bool alive() const;
  void alive(bool);

  tf::Transform& transform();
  void spawn();
  tf::Transform transformTo(Player&);

  float distanceTo(Player&);
  float sightTo(Player&);
  float angleTo(Player&);

private:
  tf::Transform _transform;
  std::string _name;
  TeamColor _team;
  bool _alive;
};

#endif