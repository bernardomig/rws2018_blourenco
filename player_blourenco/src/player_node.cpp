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
}

void PlayerNode::step(const rws2018_msgs::MakeAPlay::ConstPtr& msg)
{
  _speed = msg->cheetah;
  step();
}

void PlayerNode::step()
{
  updatePlayers();

  report();

  updateMyself();
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