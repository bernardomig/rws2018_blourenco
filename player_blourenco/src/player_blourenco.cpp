#include <ros/ros.h>

#include "player_blourenco/player.hpp"
#include "player_blourenco/player_manager.hpp"

#include <tf/transform_listener.h>

// clang-format off
auto teams =
  std::vector<std::pair<TeamColor, std::string>>{
    std::make_pair(TeamColor::Red, "/team_red"),
    std::make_pair(TeamColor::Green, "/team_green"),
    std::make_pair(TeamColor::Blue, "/team_blue"),
};
// clang-format on

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "blourenco");

  auto nh = ros::NodeHandle{};

  auto player_manager = PlayerManager{ nh };

  player_manager.loadPlayers(teams);

  auto& player = player_manager.findPlayerWithName("blourenco");

  ROS_INFO("I'm %s and my team is %i", player.name().c_str(), (int)player.team());

  auto& team = player_manager.teamOf(player);
  auto& enemies = player_manager.enemiesOf(player);
  auto& preys = player_manager.preysOf(player);

  auto joiner = [](std::string s, Player& p) { return s + " " + p.name(); };
  auto team_str = std::accumulate(team.begin(), team.end(), std::string(""), joiner);
  auto enemies_str = std::accumulate(enemies.begin(), enemies.end(), std::string(""), joiner);
  auto preys_str = std::accumulate(preys.begin(), preys.end(), std::string(""), joiner);

  ROS_INFO("Team { %s }", team_str.c_str());
  ROS_INFO("Enemies { %s }", enemies_str.c_str());
  ROS_INFO("Preys { %s }", preys_str.c_str());

  return 0;
}
