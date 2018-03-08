#include "player_blourenco/player_node.hpp"

PlayerNode::PlayerNode(std::string name, std::vector<std::pair<TeamColor, std::string>> teams)
  : _name(name)
  , _manager(_nh, teams)
  , _me(_manager.findPlayerWithName(name))
  , _players(_manager.players())
  , _team(_manager.teamOf(_me))
  , _enemies(_manager.enemiesOf(_me))
  , _preys(_manager.preysOf(_me))

{
  _sub = _nh.subscribe<rws2018_msgs::MakeAPlay>("/make_a_play", 2, &PlayerNode::step, this);

  _me.spawn();
  updateMyself();
}

void PlayerNode::step(const rws2018_msgs::MakeAPlay::ConstPtr& msg)
{
  _speed = msg->cheetah;
  step();
}

void PlayerNode::step()
{
  updatePlayers();

  move();

  updateMyself();
}

#include <cmath>

void PlayerNode::move()
{
  Player& target = _manager.findPlayerWithName("lsarmento");

  Team::iterator closest_enemy;
  auto best_distance = 100.0f;
  for (auto it = _enemies.begin(); it != _enemies.end(); ++it)
  {
    if (it->get().alive())
    {
      if (auto dist = _me.distanceTo(*it); dist < best_distance)
      {
        closest_enemy = it;
        best_distance = dist;
      }
    }
  }

  moveTo(target);
}

void PlayerNode::moveTo(Player& target)
{
  float f = _me.angleTo(target);
  float d = _me.sightTo(target) + 0.01;

  auto speed = d > _speed ? _speed : d;
  auto rotation = f * f > _rotation * _rotation ? _rotation * f / fabs(f) : f;

  auto t = tf::Transform{};
  t.setOrigin(tf::Vector3{ speed, 0, 0 });

  auto q = tf::Quaternion{};
  q.setRPY(0, 0, rotation);
  t.setRotation(q);

  _me.transform() *= t;
}

void PlayerNode::updatePlayers()
{
  for (Player& player : _players)
  {
    _updater.pullPosition(player);
  }
}

void PlayerNode::updateMyself()
{
  _updater.pushPosition(_me);
}