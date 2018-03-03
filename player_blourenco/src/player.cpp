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

bool Player::alive() const
{
  return _alive;
}

void Player::alive(bool v)
{
  _alive = v;
}

tf::Transform& Player::transform()
{
  return _transform;
}

void Player::spawn()
{
  _transform.setRotation(tf::Quaternion{ 0, 0, 0, 1 });
}

float Player::distanceTo(Player& p)
{
  auto& pos1 = transform().getOrigin();
  auto& pos2 = p.transform().getOrigin();

  return (pos1 - pos2).length();
}
