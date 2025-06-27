#pragma once

#include <../src/ParkingSpotType.h>
#include <../src/Vehicle.h>

class ParkingSpot
{
public:
  ParkingSpot(int spotNumber, ParkingSpotType type) : spotNumber(spotNumber), type(type), vehicle(nullptr), isAvailable(true) {};

  int getSpotNumber() const { return this->spotNumber; };
  ParkingSpotType getParkingSpotType() const { return this->type; };
  Vehicle *getVehicle() const { return this->vehicle; };
  bool getIsAvailable() const { return this->isAvailable; };

  bool canFitVehicle(const Vehicle *vehicle) const
  {
    if (!vehicle)
      return false;

    switch (vehicle->getVehicleType())
    {
    case VehicleType::MOTORBIKE:
      return true; // any spot
    case VehicleType::CAR:
      return type != ParkingSpotType::COMPACT;
    case VehicleType::TRUCK:
      return type == ParkingSpotType::LARGE;
    }

    return false;
  };

  bool parkVehicle(Vehicle *vehicle)
  {
    if (!isAvailable || !canFitVehicle(vehicle))
      return false;
    this->vehicle = vehicle;
    isAvailable = false;
    return true;
  };

  Vehicle *removeVehicle()
  {
    if (!vehicle)
      return nullptr;

    Vehicle *vehicle = this->vehicle;
    this->vehicle = nullptr;
    isAvailable = true;
    return vehicle;
  };

  void displayInfo() const {
    // TODO
  };

private:
  int spotNumber;
  ParkingSpotType type;
  Vehicle *vehicle;
  bool isAvailable;
};