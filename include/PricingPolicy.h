#ifndef PRICINGPOLICY_H
#define PRICINGPOLICY_H

#include <iostream>
#include <string>

using namespace std;


class IPricingPolicy {
public:
    virtual double calculateFee(int hours, string vehicleType) = 0;
    virtual string getPolicyName() = 0;
    virtual ~IPricingPolicy() {}
};

// regular pricing
class StandardPricing : public IPricingPolicy {
public:
    double calculateFee(int hours, string vehicleType) override {
        if (hours <= 0) hours = 1;

        double rate = 0;
        if (vehicleType == "Bike") rate = 10;
        else if (vehicleType == "Car") rate = 20;
        else if (vehicleType == "EV") rate = 25;

        return hours * rate;
    }
    string getPolicyName() override { return "Standard Pricing"; }
};

// weekend rates are higher
class WeekendPricing : public IPricingPolicy {
public:
    double calculateFee(int hours, string vehicleType) override {
        if (hours <= 0) hours = 1;

        double rate = 0;
        if (vehicleType == "Bike") rate = 15;
        else if (vehicleType == "Car") rate = 30;
        else if (vehicleType == "EV") rate = 35;

        return hours * rate;
    }
    string getPolicyName() override { return "Weekend Pricing"; }
};

// EXTENSION: added later without touching existing classes
class FestivalDiscount : public IPricingPolicy {
public:
    double calculateFee(int hours, string vehicleType) override {
        if (hours <= 0) hours = 1;

        double rate = 0;
        if (vehicleType == "Bike") rate = 5;
        else if (vehicleType == "Car") rate = 12;
        else if (vehicleType == "EV") rate = 15;

        return hours * rate;
    }
    string getPolicyName() override { return "Festival Discount"; }
};

// another extension: EV charging pricing
class EVChargingPricing : public IPricingPolicy {
public:
    double calculateFee(int hours, string vehicleType) override {
        if (hours <= 0) hours = 1;

        double rate = 0;
        if (vehicleType == "Bike") rate = 10;
        else if (vehicleType == "Car") rate = 20;
        else if (vehicleType == "EV") rate = 40; // includes charging

        return hours * rate;
    }
    string getPolicyName() override { return "EV Charging Pricing"; }
};

#endif
