#include "src/ParkingLot.h"
#include <iostream>

// Singleton with custom size
ParkingLot &ParkingLot::getInstance(int compactCount, int regularCount, int largeCount)
{
  static ParkingLot instance(compactCount, regularCount, largeCount);
  return instance;
}

// Singleton with default size
ParkingLot &ParkingLot::getInstance()
{
  static ParkingLot instance(10, 10, 10);
  return instance;
}

// Private default constructor (not used)
ParkingLot::ParkingLot() : capacity(0), available(0) {}

// Main constructor
ParkingLot::ParkingLot(int compactCount, int regularCount, int largeCount)
    : capacity(compactCount + regularCount + largeCount),
      available(compactCount + regularCount + largeCount)
{
  int spotNumber = 1;
  for (int i = 0; i < compactCount; ++i)
    spots.push_back(std::make_unique<ParkingSpot>(spotNumber++, ParkingSpotType::COMPACT));
  for (int i = 0; i < regularCount; ++i)
    spots.push_back(std::make_unique<ParkingSpot>(spotNumber++, ParkingSpotType::REGULAR));
  for (int i = 0; i < largeCount; ++i)
    spots.push_back(std::make_unique<ParkingSpot>(spotNumber++, ParkingSpotType::LARGE));
}

ParkingLot::~ParkingLot() = default;

int ParkingLot::getCapacity() const
{
  return capacity;
}

int ParkingLot::getAvailable() const
{
  return available;
}

bool ParkingLot::parkVehicle(Vehicle *vehicle)
{
  if (!vehicle)
    return false;

  // Already parked?
  if (occupiedSpots.find(vehicle->getLicensePlate()) != occupiedSpots.end())
    return false;

  ParkingSpot *spot = findAvailableSpot(vehicle);
  if (!spot)
    return false;

  if (spot->parkVehicle(vehicle))
  {
    occupiedSpots[vehicle->getLicensePlate()] = spot;
    --available;
    return true;
  }
  return false;
}

Vehicle *ParkingLot::removeVehicle(const std::string license)
{
  auto it = occupiedSpots.find(license);
  if (it == occupiedSpots.end())
    return nullptr;

  ParkingSpot *spot = it->second;
  Vehicle *vehicle = spot->removeVehicle();
  if (vehicle)
  {
    occupiedSpots.erase(it);
    ++available;
    notifyObservers(spot->getSpotNumber());
  }
  return vehicle;
}

ParkingSpot *ParkingLot::findVehicle(const std::string license) const
{
  auto it = occupiedSpots.find(license);
  return (it != occupiedSpots.end()) ? it->second : nullptr;
}

void ParkingLot::displayInfo() const
{
  std::cout << "\nParking Lot Status:" << std::endl;
  std::cout << "Total Capacity: " << capacity << std::endl;
  std::cout << "Available Spots: " << available << std::endl;
  std::cout << "Occupied Spots: " << (capacity - available) << std::endl;
}

void ParkingLot::displayOccupied() const
{
  std::cout << "\nDetailed Occupancy:" << std::endl;
  for (const auto &spot : spots)
    spot->displayInfo();
}

ParkingSpot *ParkingLot::findAvailableSpot(const Vehicle *vehicle) const
{
  for (const auto &spot : spots)
  {
    if (spot->getIsAvailable() && spot->canFitVehicle(vehicle))
      return spot.get();
  }
  return nullptr;
}

void ParkingLot::addObserver(ParkingLotObserver *observer)
{
  observers.push_back(observer);
}

void ParkingLot::removeObserver(ParkingLotObserver *observer)
{
  observers.erase(std::remove(observers.begin(), observers.end(), observer), observers.end());
}

void ParkingLot::notifyObservers(int spotNumber)
{
  for (auto observer : observers)
  {
    if (observer)
      observer->notifyAvailableSpot(spotNumber);
  }
}