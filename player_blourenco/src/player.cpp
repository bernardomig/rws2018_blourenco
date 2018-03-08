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
  auto now = std::chrono::system_clock::now();

  auto seed = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()).count();

  auto generator = std::default_random_engine{};
  generator.seed(seed);
  auto distribution = std::uniform_real_distribution<float>{ -5, 5 };

  auto x = distribution(generator);
  auto y = distribution(generator);

  auto q = tf::Quaternion{};
  q.setRPY(0, 0, M_PI_2);
  _transform.setOrigin(tf::Vector3(x, y, 0));
  _transform.setRotation(q);
}

tf::Transform Player::transformTo(Player& p)
{
  return transform().inverse() * p.transform();
}

float Player::distanceTo(Player& p)
{
  return transformTo(p).getOrigin().length();
}

float Player::sightTo(Player& p)
{
  return transformTo(p).getOrigin().x();
}

float Player::angleTo(Player& p)
{
  auto T = transformTo(p).getOrigin();
  auto x = T.x();
  auto y = T.y();

  return atan2(y, x);
}