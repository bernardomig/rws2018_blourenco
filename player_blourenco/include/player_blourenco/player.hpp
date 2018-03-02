#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <string>

namespace rws
{
class Player
{
public:
  Player(std::string name, std::string team);

  std::string& name();

  std::string& team_name();

private:
  std::string _name;
  std::string _team_name;
};
}

std::ostream& operator<<(std::ostream& s, rws::Player& player);

#endif