#pragma once
#include <string>

class ParkingLotObserver
{
public:
  virtual ~ParkingLotObserver() = default;
  virtual void notifyAvailableSpot(int spotNumber) = 0;
};