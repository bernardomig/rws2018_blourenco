#ifndef TEAM_HPP
#define TEAM_HPP

#include <vector>

#include "player_blourenco/player.hpp"
#include "player_blourenco/teamcolor.hpp"

namespace rws
{
class Team
{
public:
  Team(TeamColor color);

  TeamColor& color();

  std::vector<Player>& players();

  void addPlayer(Player);

private:
  TeamColor _color;
  std::vector<Player> _players;
};
}

std::ostream& operator<<(std::ostream& s, rws::Team& team);

#endif