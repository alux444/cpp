#pragma once
#include "./ParkingLotObserver.h"
#include <iostream>
#include <string>

class Customer : public ParkingLotObserver
{
  std::string name;

public:
  Customer(const std::string &name) : name(name) {}
  void notifyAvailableSpot(int spotNumber) override
  {
    std::cout << "Customer " << name << ": Spot " << spotNumber << " is now available!\n";
  }
};