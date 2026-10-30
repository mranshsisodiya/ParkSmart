#ifndef PARKINGLOT_H
#define PARKINGLOT_H

#include <vector>
#include <iostream>
#include "ParkingSlot.h"

using namespace std;

class ParkingLot {
    vector<ParkingSlot> slots;
    string lotName;

public:
    ParkingLot(string name) : lotName(name) {}

    void addSlot(int number, string type) {
        slots.push_back(ParkingSlot(number, type));
    }

    // set up the parking lot with given slot counts
    void initializeSlots(int bikeSlots, int carSlots, int evSlots) {
        int slotNum = 1;
        for (int i = 0; i < bikeSlots; i++)
            addSlot(slotNum++, "Bike");
        for (int i = 0; i < carSlots; i++)
            addSlot(slotNum++, "Car");
        for (int i = 0; i < evSlots; i++)
            addSlot(slotNum++, "EV");
    }

    vector<ParkingSlot>& getSlots() { return slots; }
    string getName() { return lotName; }

    // search for a vehicle by its plate number
    int findVehicleSlot(string plate) {
        for (int i = 0; i < (int)slots.size(); i++) {
            if (slots[i].isOccupied() && slots[i].getVehicle()->getPlate() == plate)
                return i;
        }
        return -1;
    }

    int countAvailable(string type) {
        int count = 0;
        for (int i = 0; i < (int)slots.size(); i++) {
            if (!slots[i].isOccupied() && slots[i].getType() == type)
                count++;
        }
        return count;
    }

    int countOccupied() {
        int count = 0;
        for (int i = 0; i < (int)slots.size(); i++) {
            if (slots[i].isOccupied()) count++;
        }
        return count;
    }

    int totalSlots() { return (int)slots.size(); }

    void displayStatus() {
        cout << "\n===== " << lotName << " - Parking Status =====" << endl;
        cout << "Total Slots: " << totalSlots()
             << " | Occupied: " << countOccupied()
             << " | Available: " << (totalSlots() - countOccupied()) << endl;
        cout << "  Bike slots free: " << countAvailable("Bike") << endl;
        cout << "  Car slots free:  " << countAvailable("Car") << endl;
        cout << "  EV slots free:   " << countAvailable("EV") << endl;

        cout << "\nOccupied Slots:" << endl;
        bool anyFound = false;
        for (int i = 0; i < (int)slots.size(); i++) {
            if (slots[i].isOccupied()) {
                cout << "  Slot " << slots[i].getNumber()
                     << " [" << slots[i].getType() << "] -> ";
                slots[i].getVehicle()->display();
                anyFound = true;
            }
        }
        if (!anyFound)
            cout << "  (no vehicles parked)" << endl;
        cout << "==========================================\n" << endl;
    }
};

#endif
