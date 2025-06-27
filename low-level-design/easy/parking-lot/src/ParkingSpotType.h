#pragma once
#include <ostream>

enum class ParkingSpotType
{
  COMPACT,
  REGULAR,
  LARGE
};

inline std::ostream &operator<<(std::ostream &os, ParkingSpotType type)
{
  switch (type)
  {
  case ParkingSpotType::COMPACT:
    return os << "COMPACT";
  case ParkingSpotType::REGULAR:
    return os << "REGULAR";
  case ParkingSpotType::LARGE:
    return os << "LARGE";
  default:
    return os << "UNKNOWN";
  }
}