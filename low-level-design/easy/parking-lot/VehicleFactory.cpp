#include "../src/VehicleFactory.h"

std::unique_ptr<Vehicle> VehicleFactory::createVehicle(const std::string &licensePlate, VehicleType type)
{
  // with inherited classes (e.g., Car, Truck), use a switch case
  return std::make_unique<Vehicle>(licensePlate, type);
}