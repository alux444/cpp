#pragma once

#include <string>
#include <iostream>

#include <../src/VehicleType.h>
#include <../src/Vehicle.h>

class Vehicle
{
public:
  Vehicle(std::string licensePlate, VehicleType vehicleType) : licensePlate(licensePlate), vehicleType(vehicleType) {};

  std::string getLicensePlate() const { return this->licensePlate; };
  VehicleType getVehicleType() const { return this->vehicleType; };

  void displayInfo() const
  {
    std::cout << "License plate: " << licensePlate << '\n';
    std::cout << "Vehicle type: " << vehicleType << '\n';
  };

private:
  std::string licensePlate;
  VehicleType vehicleType;
};