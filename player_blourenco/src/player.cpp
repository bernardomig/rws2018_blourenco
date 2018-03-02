#include "player_blourenco/player.hpp"

Player::Player(std::string name, TeamColor team) : _name(name), _team(team)
{
}

const std::string& Player::name() const
{
  return _name;
}

const TeamColor& Player::team() const
{
  return _team;
}

bool Player::sameTeamAs(const Player& other)
{
  return other.team() == team();
}
