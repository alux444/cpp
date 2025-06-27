#pragma once

#include <string>
#include <./VehicleType.h>

class Vehicle
{
public:
  Vehicle(std::string licensePlate, VehicleType vehicleType);

  std::string getLicensePlate() const;
  VehicleType getVehicleType() const;

  void displayInfo() const;

private:
  std::string licensePlate;
  VehicleType vehicleType;
};