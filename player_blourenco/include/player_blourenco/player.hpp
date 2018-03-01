#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "player_blourenco/player.hpp"
#include "player_blourenco/teamcolor.hpp"

namespace rws
{
class Player
{
public:
  Player(std::string name, TeamColor team = TeamColor::BLUE);

  std::string& name();

  TeamColor& team_name();

private:
  std::string _name;
  TeamColor _team_name;
};
}

std::ostream& operator<<(std::ostream& s, rws::Player& player);

#endif