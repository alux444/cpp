#pragma once

enum class VehicleType
{
  CAR,
  MOTORBIKE,
  TRUCK
};

std::ostream &operator<<(std::ostream &os, VehicleType type)
{
  switch (type)
  {
  case VehicleType::CAR:
    return os << "CAR";
  case VehicleType::MOTORBIKE:
    return os << "MOTORBIKE";
  case VehicleType::TRUCK:
    return os << "TRUCK";
  default:
    return os << "Unknown";
  }
}