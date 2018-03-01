#include "player_blourenco/team.hpp"

namespace rws
{
Team::Team(TeamColor color) : _color(color), _players()
{
}

TeamColor& Team::color()
{
  return _color;
}

std::vector<Player>& Team::players()
{
  return _players;
}

void Team::addPlayer(Player player)
{
  player.team_name() = color();
  _players.push_back(player);
}
}

std::ostream& operator<<(std::ostream& s, rws::Team& team)
{
  s << "Team {\n";
  for (auto& player : team.players())
  {
    s << "  " << player << "," << std::endl;
  }
  s << "}";
}