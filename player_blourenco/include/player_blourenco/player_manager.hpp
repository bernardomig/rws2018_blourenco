#ifndef PLAYER_MANAGER_HPP_
#define PLAYER_MANAGER_HPP_

#include <algorithm>

#include <ros/ros.h>

#include "player_blourenco/player.hpp"

typedef std::vector<std::reference_wrapper<Player>> Team;

class PlayerManager
{
public:
  PlayerManager(ros::NodeHandle& nh);

  const std::vector<Player> players() const;
  Player& findPlayerWithName(std::string) throw(std::exception);
  const Team& teamOf(TeamColor) const;
  const Team& teamOf(Player&) const;
  const Team& enemiesOf(TeamColor) const;
  const Team& enemiesOf(Player&) const;
  const Team& preysOf(TeamColor) const;
  const Team& preysOf(Player&) const;

  void loadPlayers(std::vector<std::pair<TeamColor, std::string>>&);

protected:
  void loadPlayersFromTeam(TeamColor team, std::string team_str);
  void assignPlayersToTeam();

private:
  ros::NodeHandle& _nh;
  std::vector<Player> _players;

  std::map<TeamColor, Team> _teams;
};

#endif