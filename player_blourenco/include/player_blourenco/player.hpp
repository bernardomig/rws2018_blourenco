#ifndef PLAYER_HPP_
#define PLAYER_HPP_

#include <string>

#include "player_blourenco/team_color.hpp"

class Player
{
public:
  Player(std::string name, TeamColor team);

  const std::string& name() const;
  const TeamColor& team() const;

private:
  std::string _name;
  TeamColor _team;
};

#endif