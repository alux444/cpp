#pragma once
#include <memory>
#include <string>
#include "./Vehicle.h"
#include "./VehicleType.h"

class VehicleFactory {
public:
    static std::unique_ptr<Vehicle> createVehicle(const std::string& licensePlate, VehicleType type);
};