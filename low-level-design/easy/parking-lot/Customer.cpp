#include "src/Customer.h"

Customer::Customer(const std::string &name) : name(name) {}

void Customer::notifyAvailableSpot(int spotNumber)
{
  std::cout << "Customer " << name << ": Spot " << spotNumber << " is now available!\n";
}