#ifndef PAYMENTMETHOD_H
#define PAYMENTMETHOD_H

#include <iostream>
#include <string>

using namespace std;

class IPayment {
public:
    virtual void processPayment(double amount) = 0;
    virtual string getMethodName() = 0;
    virtual ~IPayment() {}
};

class CashPayment : public IPayment {
public:
    void processPayment(double amount) override {
        cout << "  Cash payment of Rs. " << amount << " received." << endl;
    }
    string getMethodName() override { return "Cash"; }
};

class UpiPayment : public IPayment {
public:
    void processPayment(double amount) override {
        cout << "  UPI payment of Rs. " << amount << " processed successfully." << endl;
    }
    string getMethodName() override { return "UPI"; }
};

class CardPayment : public IPayment {
public:
    void processPayment(double amount) override {
        cout << "  Card payment of Rs. " << amount << " processed." << endl;
    }
    string getMethodName() override { return "Card"; }
};

#endif
