#pragma once

#include "ParkingSpotType.h"
#include "Vehicle.h"

class ParkingSpot
{
public:
  ParkingSpot(int spotNumber, ParkingSpotType type);

  int getSpotNumber() const;
  ParkingSpotType getParkingSpotType() const;
  Vehicle *getVehicle() const;
  bool getIsAvailable() const;

  bool canFitVehicle(const Vehicle *vehicle) const;
  bool parkVehicle(Vehicle *vehicle);
  Vehicle *removeVehicle();
  void displayInfo() const;

private:
  int spotNumber;
  ParkingSpotType type;
  Vehicle *vehicle;
  bool isAvailable;
};