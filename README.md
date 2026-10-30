# ParkSmart - Smart Parking Management System

A console-based parking management system built in C++ that demonstrates Object-Oriented Programming (OOP) concepts and all five SOLID design principles.

## About

ParkSmart simulates a campus parking lot where users can park and remove vehicles, calculate fees based on different pricing policies, choose payment methods, and receive notifications. The system supports bikes, cars, and electric vehicles (EVs) with optional charging.

This project was built as a case study to show how SOLID principles can be applied in a real-world scenario to create maintainable and extensible software.

## Features

- **Vehicle Management** — Park and remove Bikes, Cars, and Electric Vehicles
- **Slot Allocation** — Multiple strategies (First Available, Near Exit)
- **Flexible Pricing** — Standard, Weekend, Festival Discount, EV Charging policies
- **Multiple Payments** — Cash, UPI, and Card payment methods
- **Notifications** — Console, SMS, and Email notification channels
- **Revenue Tracking** — Track total vehicles served and revenue
- **EV Charging** — Special support for electric vehicle charging fees

## OOP Concepts Used

| Concept | Where |
|---------|-------|
| **Classes & Objects** | Vehicle, ParkingSlot, ParkingLot, ParkingService |
| **Encapsulation** | Private data in ParkingSlot with getter/setter methods |
| **Inheritance** | Bike, Car, ElectricVehicle inherit from Vehicle |
| **Polymorphism** | Virtual functions in Vehicle, IPricingPolicy, ISlotAllocator |
| **Abstraction** | Abstract interfaces like IPayment, INotification |

## SOLID Principles Demonstrated

### S — Single Responsibility Principle (SRP)
Each class has one clear job:
- `ParkingLot` — manages slots only
- `ParkingService` — coordinates parking operations only
- `IPricingPolicy` implementations — calculate fees only

### O — Open/Closed Principle (OCP)
New pricing policies (like `FestivalDiscount` or `EVChargingPricing`) were added as new classes without modifying existing pricing code or the checkout flow.

### L — Liskov Substitution Principle (LSP)
`FirstAvailableAllocator` and `NearExitAllocator` can be swapped wherever `ISlotAllocator` is expected. Both return a valid slot index or -1, so the calling code works correctly with either.

### I — Interface Segregation Principle (ISP)
Instead of one big interface, we have small focused ones:
- `IPayment` — only payment processing
- `INotification` — only sending notifications
- `IPricingPolicy` — only fee calculation
- `ISlotAllocator` — only slot finding

No class is forced to implement methods it doesn't need.

### D — Dependency Inversion Principle (DIP)
`ParkingService` depends on abstract interfaces (`IPricingPolicy*`, `ISlotAllocator*`, `IPayment*`, `INotification*`) rather than concrete classes like `CashPayment` or `StandardPricing`. Implementations are injected from outside.

## Extension Demonstrated

After building the core system, we added:
1. **FestivalDiscount** pricing policy — added without changing any existing pricing class
2. **EVChargingPricing** policy — another extension with no modification to existing code
3. **EV Charging support** — ElectricVehicle class with optional charging fee

This shows that the system is open for extension but closed for modification (OCP).

## Project Structure

```
ParkSmart/
├── include/
│   ├── Vehicle.h           # Vehicle base class + Bike, Car, EV
│   ├── ParkingSlot.h       # Parking slot with occupancy tracking
│   ├── ParkingLot.h        # Manages all slots (SRP)
│   ├── PricingPolicy.h     # Pricing interface + implementations (OCP)
│   ├── SlotAllocator.h     # Allocation strategies (LSP)
│   ├── PaymentMethod.h     # Payment interface + implementations (DIP)
│   ├── Notification.h      # Notification interface (ISP)
│   └── ParkingService.h    # Main service coordinating everything (DIP)
├── src/
│   └── main.cpp            # Console menu and user interaction
├── README.md
└── .gitignore
```

## How to Build and Run

### Using g++ (MinGW / Linux / Mac)
```bash
g++ -std=c++17 -I include src/main.cpp -o parksmart
./parksmart
```

### Using Code::Blocks
1. Create a new Console Application project
2. Add all `.h` files from `include/` to the project
3. Add `src/main.cpp` as the main source file
4. Make sure the include path has the `include/` folder
5. Build and Run

### Using Visual Studio
1. Create a new Empty C++ Project
2. Add header files to Header Files filter
3. Add `main.cpp` to Source Files filter
4. Set include directories to include the `include/` folder
5. Build (Ctrl+F5)

## Sample Usage

```
======= ParkSmart =======
1. Park a Vehicle
2. Remove a Vehicle
3. View Parking Status
4. View Revenue
5. Change Pricing Policy
6. Change Allocation Strategy
7. Change Notification Type
8. Exit
=========================
Enter your choice: 1

Vehicle type:
1. Bike
2. Car
3. Electric Vehicle
Choice: 2
Enter number plate: KA-01-1234
Enter owner name: Rahul
Vehicle KA-01-1234 parked in slot 6
  [NOTIFICATION] Vehicle KA-01-1234 parked in slot 6
```

## Pricing Rates

| Policy | Bike | Car | EV |
|--------|------|-----|-----|
| Standard | Rs. 10/hr | Rs. 20/hr | Rs. 25/hr |
| Weekend | Rs. 15/hr | Rs. 30/hr | Rs. 35/hr |
| Festival Discount | Rs. 5/hr | Rs. 12/hr | Rs. 15/hr |
| EV Charging | Rs. 10/hr | Rs. 20/hr | Rs. 40/hr |

## Technologies

- **Language:** C++17
- **Build:** g++ / Code::Blocks / Visual Studio
- **No external libraries required**

## Author

Smart Parking Management System - SOLID Case Study Project
