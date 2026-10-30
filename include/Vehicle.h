#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
#include <ctime>

using namespace std;

class Vehicle {
protected:
    string numberPlate;
    string ownerName;
    string vehicleType;
    time_t entryTime;

public:
    Vehicle(string plate, string owner, string type) {
        numberPlate = plate;
        ownerName = owner;
        vehicleType = type;
        entryTime = time(0);
    }

    virtual ~Vehicle() {}

    string getPlate() { return numberPlate; }
    string getOwner() { return ownerName; }
    string getType() { return vehicleType; }
    time_t getEntryTime() { return entryTime; }

    virtual void display() {
        cout << vehicleType << " | " << numberPlate << " | " << ownerName << endl;
    }
};

class Bike : public Vehicle {
public:
    Bike(string plate, string owner) : Vehicle(plate, owner, "Bike") {}
};

class Car : public Vehicle {
public:
    Car(string plate, string owner) : Vehicle(plate, owner, "Car") {}
};

class ElectricVehicle : public Vehicle {
    bool needsCharging;
public:
    ElectricVehicle(string plate, string owner, bool charging = false)
        : Vehicle(plate, owner, "EV"), needsCharging(charging) {}

    bool wantsCharging() { return needsCharging; }

    void display() override {
        cout << "EV | " << numberPlate << " | " << ownerName;
        if (needsCharging) cout << " [Charging]";
        cout << endl;
    }
};

#endif
