#ifndef PARKINGSLOT_H
#define PARKINGSLOT_H

#include <string>
#include "Vehicle.h"

using namespace std;

class ParkingSlot {
    int slotNumber;
    string slotType;  // "Bike", "Car", "EV"
    bool occupied;
    Vehicle* parkedVehicle;

public:
    ParkingSlot(int num, string type) {
        slotNumber = num;
        slotType = type;
        occupied = false;
        parkedVehicle = nullptr;
    }

    int getNumber() { return slotNumber; }
    string getType() { return slotType; }
    bool isOccupied() { return occupied; }
    Vehicle* getVehicle() { return parkedVehicle; }

    bool isCompatible(string vehicleType) {
        return slotType == vehicleType;
    }

    void parkVehicle(Vehicle* v) {
        parkedVehicle = v;
        occupied = true;
    }

    Vehicle* removeVehicle() {
        Vehicle* v = parkedVehicle;
        parkedVehicle = nullptr;
        occupied = false;
        return v;
    }
};

#endif
