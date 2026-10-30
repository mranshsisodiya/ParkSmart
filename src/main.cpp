
#include <iostream>
#include <string>
#include <limits>
#include "../include/ParkingService.h"

using namespace std;

// helper to clear bad input from cin
void clearInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void showMenu() {
    cout << "\n======= ParkSmart =======" << endl;
    cout << "1. Park a Vehicle" << endl;
    cout << "2. Remove a Vehicle" << endl;
    cout << "3. View Parking Status" << endl;
    cout << "4. View Revenue" << endl;
    cout << "5. Change Pricing Policy" << endl;
    cout << "6. Change Allocation Strategy" << endl;
    cout << "7. Change Notification Type" << endl;
    cout << "8. Exit" << endl;
    cout << "=========================" << endl;
    cout << "Enter your choice: ";
}

int main() {
    // set up the parking lot with slots
    ParkingLot lot("VIT Campus Parking");
    lot.initializeSlots(5, 5, 3);  // 5 bike, 5 car, 3 EV

    StandardPricing standardPricing;
    WeekendPricing weekendPricing;
    FestivalDiscount festivalDiscount;
    EVChargingPricing evChargingPricing;

    FirstAvailableAllocator firstAvailable;
    NearExitAllocator nearExit;

    CashPayment cashPayment;
    UpiPayment upiPayment;
    CardPayment cardPayment;

    ConsoleNotification consoleNotify;
    SMSNotification smsNotify;
    EmailNotification emailNotify;

    ParkingService service(lot, &standardPricing, &firstAvailable, &consoleNotify);

    cout << "==========================================" << endl;
    cout << "  Welcome to ParkSmart" << endl;
    cout << "  Smart Parking Management System" << endl;
    cout << "==========================================" << endl;
    cout << "Parking lot ready: 5 Bike, 5 Car, 3 EV slots" << endl;

    int choice;
    bool running = true;

    while (running) {
        showMenu();
        cin >> choice;

        if (cin.fail()) {
            clearInput();
            cout << "Please enter a valid number." << endl;
            continue;
        }

        switch (choice) {

        case 1: {
            // Park a vehicle
            cout << "\nVehicle type:" << endl;
            cout << "1. Bike" << endl;
            cout << "2. Car" << endl;
            cout << "3. Electric Vehicle" << endl;
            cout << "Choice: ";
            int vtype;
            cin >> vtype;

            if (cin.fail() || vtype < 1 || vtype > 3) {
                clearInput();
                cout << "Invalid vehicle type." << endl;
                break;
            }
            clearInput();

            string plate, owner;
            cout << "Enter number plate: ";
            getline(cin, plate);
            cout << "Enter owner name: ";
            getline(cin, owner);

            if (plate.empty() || owner.empty()) {
                cout << "Plate and owner name cannot be empty." << endl;
                break;
            }

            // check duplicate
            if (lot.findVehicleSlot(plate) != -1) {
                cout << "Vehicle " << plate << " is already parked!" << endl;
                break;
            }

            Vehicle* vehicle = nullptr;
            if (vtype == 1) {
                vehicle = new Bike(plate, owner);
            }
            else if (vtype == 2) {
                vehicle = new Car(plate, owner);
            }
            else {
                int charging;
                cout << "Does the EV need charging? (1 = Yes, 0 = No): ";
                cin >> charging;
                if (cin.fail()) {
                    clearInput();
                    charging = 0;
                }
                vehicle = new ElectricVehicle(plate, owner, charging == 1);
            }

            service.parkVehicle(vehicle);
            break;
        }

        case 2: {
            // Remove a vehicle
            clearInput();
            string plate;
            cout << "Enter number plate to remove: ";
            getline(cin, plate);

            if (plate.empty()) {
                cout << "Plate number cannot be empty." << endl;
                break;
            }

            if (lot.findVehicleSlot(plate) == -1) {
                cout << "Vehicle " << plate << " not found in the lot." << endl;
                break;
            }

            int hours;
            cout << "Enter parking duration (in hours): ";
            cin >> hours;
            if (cin.fail() || hours <= 0) {
                clearInput();
                cout << "Invalid duration. Must be at least 1 hour." << endl;
                break;
            }

            // pick payment method
            cout << "\nPayment method:" << endl;
            cout << "1. Cash" << endl;
            cout << "2. UPI" << endl;
            cout << "3. Card" << endl;
            cout << "Choice: ";
            int pmethod;
            cin >> pmethod;

            IPayment* selectedPayment = &cashPayment;
            if (pmethod == 2) selectedPayment = &upiPayment;
            else if (pmethod == 3) selectedPayment = &cardPayment;

            service.exitVehicle(plate, hours, selectedPayment);
            break;
        }

        case 3:
            lot.displayStatus();
            break;

        case 4:
            service.showRevenue();
            break;

        case 5: {
            // Change pricing policy - shows OCP in action
            cout << "\nSelect pricing policy:" << endl;
            cout << "1. Standard Pricing" << endl;
            cout << "2. Weekend Pricing" << endl;
            cout << "3. Festival Discount (Extension)" << endl;
            cout << "4. EV Charging Pricing (Extension)" << endl;
            cout << "Choice: ";
            int pchoice;
            cin >> pchoice;

            if (pchoice == 1) service.setPricingPolicy(&standardPricing);
            else if (pchoice == 2) service.setPricingPolicy(&weekendPricing);
            else if (pchoice == 3) service.setPricingPolicy(&festivalDiscount);
            else if (pchoice == 4) service.setPricingPolicy(&evChargingPricing);
            else cout << "Invalid choice." << endl;
            break;
        }

        case 6: {
            cout << "\nSelect allocation strategy:" << endl;
            cout << "1. First Available" << endl;
            cout << "2. Near Exit" << endl;
            cout << "Choice: ";
            int achoice;
            cin >> achoice;

            if (achoice == 1) service.setAllocator(&firstAvailable);
            else if (achoice == 2) service.setAllocator(&nearExit);
            else cout << "Invalid choice." << endl;
            break;
        }

        case 7: {
            // Change notification type
            cout << "\nSelect notification type:" << endl;
            cout << "1. Console" << endl;
            cout << "2. SMS (simulated)" << endl;
            cout << "3. Email (simulated)" << endl;
            cout << "Choice: ";
            int nchoice;
            cin >> nchoice;

            if (nchoice == 1) service.setNotifier(&consoleNotify);
            else if (nchoice == 2) service.setNotifier(&smsNotify);
            else if (nchoice == 3) service.setNotifier(&emailNotify);
            else cout << "Invalid choice." << endl;
            break;
        }

        case 8:
            running = false;
            cout << "\nThank you for using ParkSmart. Goodbye!" << endl;
            break;

        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
