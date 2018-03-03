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
  const Team& playersOf(TeamColor team) const;
  const Team& teamOf(Player&) const;

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