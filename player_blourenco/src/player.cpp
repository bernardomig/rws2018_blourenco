#include "player_blourenco/player.hpp"

namespace rws
{
Player::Player(std::string name, std::string team) : _name(name), _team_name(team)
{
}
std::string& Player::name()
{
  return _name;
}
std::string& Player::team_name()
{
  return _team_name;
}
}

std::ostream& operator<<(std::ostream& s, rws::Player& player)
{
  s << "Player{ " << player.name() << " of " << player.team_name() << " }";
  return s;
}
