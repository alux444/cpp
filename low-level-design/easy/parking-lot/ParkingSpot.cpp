#include "../src/ParkingSpotType.h"
#include "../src/Vehicle.h"
#include "../src/ParkingSpot.h"

#include <iostream>

ParkingSpot::ParkingSpot(int spotNumber, ParkingSpotType type)
    : spotNumber(spotNumber), type(type), vehicle(nullptr), isAvailable(true) {}

int ParkingSpot::getSpotNumber() const { return this->spotNumber; }
ParkingSpotType ParkingSpot::getParkingSpotType() const { return this->type; }
Vehicle *ParkingSpot::getVehicle() const { return this->vehicle; }
bool ParkingSpot::getIsAvailable() const { return this->isAvailable; }

bool ParkingSpot::canFitVehicle(const Vehicle *vehicle) const
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
}

bool ParkingSpot::parkVehicle(Vehicle *vehicle)
{
  if (!isAvailable || !canFitVehicle(vehicle))
    return false;
  this->vehicle = vehicle;
  isAvailable = false;
  return true;
}

Vehicle *ParkingSpot::removeVehicle()
{
  if (!vehicle)
    return nullptr;
  Vehicle *v = this->vehicle;
  this->vehicle = nullptr;
  isAvailable = true;
  return v;
}

void ParkingSpot::displayInfo() const
{
  std::cout << "Parking spot number " << spotNumber << " ";
  std::cout << "Available: " << std::boolalpha << isAvailable << " ";
  std::cout << "Current vehicle: ";
  if (vehicle)
    vehicle->displayInfo();
  else
    std::cout << " None\n";
}