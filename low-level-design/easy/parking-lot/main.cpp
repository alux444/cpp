#include "src/ParkingLot.h"
#include "src/VehicleFactory.h"
#include "src/Customer.h"
#include <iostream>
#include <memory>

int main()
{
  // Create a parking lot with 2 compact, 2 regular, 1 large spot
  ParkingLot &lot = ParkingLot::getInstance(2, 2, 1);

  // Create customers (observers)
  Customer alice("Alice");
  Customer bob("Bob");
  lot.addObserver(&alice);
  lot.addObserver(&bob);

  // Create vehicles using the factory
  auto car1 = VehicleFactory::createVehicle("CAR123", VehicleType::CAR);
  auto bike1 = VehicleFactory::createVehicle("BIKE1", VehicleType::MOTORBIKE);
  auto truck1 = VehicleFactory::createVehicle("TRUCK1", VehicleType::TRUCK);

  // Park vehicles
  std::cout << "\nParking vehicles...\n";
  lot.parkVehicle(car1.get());
  lot.parkVehicle(bike1.get());
  lot.parkVehicle(truck1.get());

  // Display lot info
  lot.displayInfo();
  lot.displayOccupied();

  // Remove a vehicle and observe notifications
  std::cout << "\nRemoving CAR123...\n";
  lot.removeVehicle("CAR123");

  // Display lot info again
  lot.displayInfo();
  lot.displayOccupied();

  // Remove observers
  lot.removeObserver(&alice);
  lot.removeObserver(&bob);

  return 0;
}