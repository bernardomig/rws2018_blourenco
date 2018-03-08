#include "player_blourenco/player_updater.hpp"

void PlayerUpdater::pullPosition(Player& p)
{
  auto transform = tf::StampedTransform{};

  try
  {
    _listener.lookupTransform("/world", p.name(), ros::Time(0), transform);

    p.alive(true);

    p.transform().setOrigin(transform.getOrigin());
    p.transform().setRotation(transform.getRotation());
  }
  catch (tf::LookupException)
  {
    p.alive(false);
  }
}

void PlayerUpdater::pushPosition(Player& p)
{
  _broadcaster.sendTransform(tf::StampedTransform(p.transform(), ros::Time::now(), "/world", p.name()));
}