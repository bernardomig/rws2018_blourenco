#include <ros/ros.h>

#include "player_blourenco/player.hpp"

#include "player_blourenco/player_node.hpp"

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

  PlayerNode node("blourenco", teams);

  ros::spin();

  return 0;
}
