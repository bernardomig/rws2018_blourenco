#ifndef PLAYER_MANAGER_HPP
#define PLAYER_MANAGER_HPP

#include <tf/transform_broadcaster.h>
#include <tf/transform_listener.h>

#include "player_blourenco/player.hpp"

class PlayerUpdater
{
public:
  void pullPosition(Player&);
  void pushPosition(Player&);

private:
  tf::TransformListener _listener;
  tf::TransformBroadcaster _broadcaster;
};

#endif