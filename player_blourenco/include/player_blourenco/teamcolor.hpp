#ifndef TEAMCOLOR_HPP
#define TEAMCOLOR_HPP

#include <iostream>

namespace rws
{
enum class TeamColor : int
{
  RED,
  GREEN,
  BLUE,
};
}
std::ostream& operator<<(std::ostream& s, const rws::TeamColor& team);

#endif