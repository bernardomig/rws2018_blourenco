#include "player_blourenco/player_manager.hpp"

PlayerManager::PlayerManager(ros::NodeHandle& nh) : _nh(nh)
{
}

const std::vector<Player> PlayerManager::players() const
{
  return _players;
}

const Team& PlayerManager::playersOf(TeamColor team) const
{
  return _teams.at(team);
}

const Team& PlayerManager::teamOf(Player& player) const
{
  return playersOf(player.team());
}

void PlayerManager::loadPlayers(std::vector<std::pair<TeamColor, std::string>>& teams)
{
  for (auto& team : teams)
  {
    auto color = std::get<0>(team);
    auto topic = std::get<1>(team);
    loadPlayersFromTeam(color, topic);
  }
  assignPlayersToTeam();
}

void PlayerManager::assignPlayersToTeam()
{
  for (auto&& player : _players)
    _teams[player.team()].push_back(player);
}

void PlayerManager::loadPlayersFromTeam(TeamColor team, std::string team_str)
{
  std::vector<std::string> players_str;
  _nh.getParam(team_str, players_str);

  std::transform(players_str.begin(), players_str.end(), std::back_inserter(_players), [=](auto str) {
    return Player{ str, team };
  });
}