#pragma once

#include <vector>
#include <map>
#include <memory>
#include "ParkingSpot.h"
#include "Vehicle.h"
#include "ParkingLotObserver.h"

class ParkingLot
{
public:
  static ParkingLot &getInstance(int compactCount, int regularCount, int largeCount);
  static class ParkingLot &getInstance();

  ParkingLot(const ParkingLot &) = delete;
  ParkingLot operator=(const ParkingLot &) = delete;
  ParkingLot(ParkingLot &&) = delete;
  ParkingLot &operator=(ParkingLot &&) = delete;

  int getCapacity() const;
  int getAvailable() const;

  bool parkVehicle(Vehicle *vehicle);
  Vehicle *removeVehicle(const std::string license);
  ParkingSpot *findVehicle(const std::string license) const;
  ParkingSpot *findAvailableSpot(const Vehicle *vehicle) const;

  void displayInfo() const;
  void displayOccupied() const;

  void addObserver(ParkingLotObserver *observer);
  void removeObserver(ParkingLotObserver *observer);

private:
  ParkingLot();
  ParkingLot(int compactCount, int regularCount, int largeCount);
  ~ParkingLot();
  std::vector<std::unique_ptr<ParkingSpot>> spots;
  std::map<std::string, ParkingSpot *> occupiedSpots; // license plate : spot
  int capacity;
  int available;
  std::vector<ParkingLotObserver *> observers;
  void notifyObservers(int spotNumber);
};