#include <ros/ros.h>

#include "player_blourenco/player.hpp"
#include "player_blourenco/player_manager.hpp"

#include <tf/transform_listener.h>

int main(int argc, char* argv[])
{
  ros::init(argc, argv, "blourenco");

  auto nh = ros::NodeHandle{};

  auto player_manager = PlayerManager{ nh };

  auto teams = std::vector<std::pair<TeamColor, std::string>>{
    std::make_pair(TeamColor::Red, "/team_red"), std::make_pair(TeamColor::Green, "/team_green"),
    std::make_pair(TeamColor::Blue, "/team_blue"),
  };

  player_manager.loadPlayers(teams);

  auto& players = player_manager.playersOf(TeamColor::Red);

  for (Player& player : players)
  {
    ROS_INFO("%s", player.name().c_str());
  }

  return 0;
}
