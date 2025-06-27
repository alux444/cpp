#include "../src/VehicleType.h"
#include "../src/Vehicle.h"
#include <iostream>
#include <string>

Vehicle::Vehicle(std::string licensePlate, VehicleType vehicleType)
    : licensePlate(licensePlate), vehicleType(vehicleType) {}

std::string Vehicle::getLicensePlate() const
{
  return this->licensePlate;
}

VehicleType Vehicle::getVehicleType() const
{
  return this->vehicleType;
}

void Vehicle::displayInfo() const
{
  std::cout << "License plate: " << licensePlate << '\n';
  std::cout << "Vehicle type: " << vehicleType << '\n';
}