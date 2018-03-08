#include "player_blourenco/player_manager.hpp"

PlayerManager::PlayerManager(ros::NodeHandle& nh, std::vector<std::pair<TeamColor, std::string>> teams) : _nh(nh)
{
  loadPlayers(teams);
}

Team PlayerManager::players()
{
  Team team;

  for (Player& player : _players)
  {
    team.push_back(player);
  }
  return team;
}

Player& PlayerManager::findPlayerWithName(std::string name)
{
  auto player = std::find_if(_players.begin(), _players.end(), [&](auto& p) { return p.name() == name; });
  if (player == _players.end())
  {
    throw std::runtime_error("player not found");
  }
  else
  {
    return *player;
  }
}

const Team& PlayerManager::teamOf(TeamColor team) const
{
  return _teams.at(team);
}

const Team& PlayerManager::teamOf(Player& player) const
{
  return teamOf(player.team());
}

const Team& PlayerManager::preysOf(TeamColor team) const
{
  switch (team)
  {
    case TeamColor::Red:
      return teamOf(TeamColor::Green);
    case TeamColor::Green:
      return teamOf(TeamColor::Blue);
    case TeamColor::Blue:
      return teamOf(TeamColor::Red);
  }
}

const Team& PlayerManager::enemiesOf(Player& player) const
{
  return enemiesOf(player.team());
}

const Team& PlayerManager::enemiesOf(TeamColor team) const
{
  switch (team)
  {
    case TeamColor::Red:
      return teamOf(TeamColor::Blue);
    case TeamColor::Green:
      return teamOf(TeamColor::Red);
    case TeamColor::Blue:
      return teamOf(TeamColor::Green);
  }
}

const Team& PlayerManager::preysOf(Player& player) const
{
  return preysOf(player.team());
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