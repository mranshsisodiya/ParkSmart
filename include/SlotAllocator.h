#ifndef SLOTALLOCATOR_H
#define SLOTALLOCATOR_H

#include <vector>
#include <string>
#include "ParkingSlot.h"

using namespace std;


class ISlotAllocator {
public:
    virtual int findSlot(vector<ParkingSlot>& slots, string vehicleType) = 0;
    virtual string getName() = 0;
    virtual ~ISlotAllocator() {}
};

// picks the first empty slot that matches the vehicle type
class FirstAvailableAllocator : public ISlotAllocator {
public:
    int findSlot(vector<ParkingSlot>& slots, string vehicleType) override {
        for (int i = 0; i < (int)slots.size(); i++) {
            if (!slots[i].isOccupied() && slots[i].isCompatible(vehicleType))
                return i;
        }
        return -1;
    }
    string getName() override { return "First Available"; }
};

// picks the last empty slot (closest to exit)
class NearExitAllocator : public ISlotAllocator {
public:
    int findSlot(vector<ParkingSlot>& slots, string vehicleType) override {
        if (slots.empty()) return -1;
        for (int i = (int)slots.size() - 1; i >= 0; i--) {
            if (!slots[i].isOccupied() && slots[i].isCompatible(vehicleType))
                return i;
        }
        return -1;
    }
    string getName() override { return "Near Exit"; }
};

#endif
