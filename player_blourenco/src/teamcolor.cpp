#include "player_blourenco/teamcolor.hpp"

namespace rws
{
}
std::ostream& operator<<(std::ostream& s, const rws::TeamColor& team)
{
  switch (team)
  {
    case (rws::TeamColor::RED):
      s << "red";
      break;
    case (rws::TeamColor::GREEN):
      s << "green";
      break;
    case (rws::TeamColor::BLUE):
      s << "blue";
      break;
    default:
      s << "UNDEF";
      break;
  }
  return s;
}