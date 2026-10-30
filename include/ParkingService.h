#ifndef PARKINGSERVICE_H
#define PARKINGSERVICE_H

#include "ParkingLot.h"
#include "PricingPolicy.h"
#include "SlotAllocator.h"
#include "PaymentMethod.h"
#include "Notification.h"

using namespace std;


class ParkingService {
    ParkingLot& lot;
    IPricingPolicy* pricing;
    ISlotAllocator* allocator;
    INotification* notifier;
    double totalRevenue;
    int totalVehiclesServed;

public:
    ParkingService(ParkingLot& parkingLot, IPricingPolicy* p, ISlotAllocator* a, INotification* n)
        : lot(parkingLot), pricing(p), allocator(a), notifier(n) {
        totalRevenue = 0;
        totalVehiclesServed = 0;
    }

    // swap pricing at runtime without changing this class - OCP
    void setPricingPolicy(IPricingPolicy* p) {
        pricing = p;
        cout << "Pricing policy changed to: " << p->getPolicyName() << endl;
    }

    // swap allocator at runtime - LSP
    void setAllocator(ISlotAllocator* a) {
        allocator = a;
        cout << "Allocation strategy changed to: " << a->getName() << endl;
    }

    void setNotifier(INotification* n) {
        notifier = n;
        cout << "Notification method updated." << endl;
    }

    bool parkVehicle(Vehicle* vehicle) {
        string type = vehicle->getType();

        int slotIdx = allocator->findSlot(lot.getSlots(), type);
        if (slotIdx == -1) {
            cout << "Sorry, no " << type << " parking slot available!" << endl;
            delete vehicle;
            return false;
        }

        lot.getSlots()[slotIdx].parkVehicle(vehicle);
        int slotNum = lot.getSlots()[slotIdx].getNumber();

        cout << "Vehicle " << vehicle->getPlate() << " parked in slot " << slotNum << endl;
        notifier->sendNotification("Vehicle " + vehicle->getPlate() +
                                   " parked in slot " + to_string(slotNum));
        return true;
    }

    bool exitVehicle(string plate, int hours, IPayment* paymentMethod) {
        int slotIdx = lot.findVehicleSlot(plate);
        if (slotIdx == -1) {
            cout << "Vehicle " << plate << " not found in parking lot!" << endl;
            return false;
        }

        Vehicle* vehicle = lot.getSlots()[slotIdx].removeVehicle();
        string vType = vehicle->getType();

        // calculate fee using current pricing policy
        double fee = pricing->calculateFee(hours, vType);

        // extra charge if EV needs charging
        if (vType == "EV") {
            ElectricVehicle* ev = dynamic_cast<ElectricVehicle*>(vehicle);
            if (ev != nullptr && ev->wantsCharging()) {
                double chargingFee = hours * 15.0;
                fee += chargingFee;
                cout << "  (EV charging fee of Rs. " << chargingFee << " added)" << endl;
            }
        }

        // print the receipt
        cout << "\n--- Parking Receipt ---" << endl;
        cout << "  Vehicle:  " << plate << " (" << vType << ")" << endl;
        cout << "  Owner:    " << vehicle->getOwner() << endl;
        cout << "  Duration: " << hours << " hour(s)" << endl;
        cout << "  Policy:   " << pricing->getPolicyName() << endl;
        cout << "  Total:    Rs. " << fee << endl;
        cout << "  Payment:  " << paymentMethod->getMethodName() << endl;

        paymentMethod->processPayment(fee);

        totalRevenue += fee;
        totalVehiclesServed++;

        notifier->sendNotification("Vehicle " + plate + " exited. Fee: Rs. " +
                                   to_string((int)fee));

        cout << "--- End Receipt ---\n" << endl;

        delete vehicle;
        return true;
    }

    void showRevenue() {
        cout << "\n--- Revenue Summary ---" << endl;
        cout << "  Vehicles served:  " << totalVehiclesServed << endl;
        cout << "  Total revenue:    Rs. " << totalRevenue << endl;
        cout << "  Current pricing:  " << pricing->getPolicyName() << endl;
        cout << "  Allocator:        " << allocator->getName() << endl;
        cout << "-----------------------\n" << endl;
    }

    ParkingLot& getLot() { return lot; }
};

#endif
