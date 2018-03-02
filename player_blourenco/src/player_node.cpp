#include "player_blourenco/player_node.hpp"

static const std::string team_to_s(Team team)
{
  switch (team)
  {
    case Team::Blue:
      return "blue";
    case Team::Red:
      return "red";
    case Team::Green:
      return "green";
  }
}

PlayerNode::PlayerNode(std::string name) : _name(name)
{
  // clang-format off
  auto team_mapping = {
    std::make_pair("/team_blue", Team::Blue),std::make_pair("/team_red", Team::Red),
    std::make_pair("/team_green", Team::Green),
  };
  // clang-format on

  for (auto& team : team_mapping)
  {
    std::vector<std::string> players_in_team;
    _nh.getParam(std::get<0>(team), players_in_team);
    for (auto& player : players_in_team)
    {
      _players.push_back(Player{ player, std::get<1>(team) });
    }
  }

  std::array<std::vector<std::reference_wrapper<Player>>, 3> teams;

  for (auto team : { Team::Red, Team::Blue, Team::Green })
  {
    std::copy_if(_players.begin(), _players.end(), std::back_inserter(teams[(int)team]),
                 [=](const Player& player) { return player.team == team; });
  }

  auto print_team = [&]() {
    for (auto& els : teams)
    {
      auto team_s = std::accumulate(els.begin(), els.end(), std::string(""),
                                    [](auto& rep, auto& el) { return rep + " " + el.get().name; });

      ROS_INFO("team %s {%s }", team_to_s(els[0].get().team).c_str(), team_s.c_str());
    }
  };

  print_team();

  for (auto& player : _players)
  {
    player.name += "[" + team_to_s(player.team) + "]";
  }

  print_team();
}

void PlayerNode::start()
{
}