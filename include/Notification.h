#ifndef NOTIFICATION_H
#define NOTIFICATION_H

#include <iostream>
#include <string>

using namespace std;


class INotification {
public:
    virtual void sendNotification(string message) = 0;
    virtual ~INotification() {}
};

class ConsoleNotification : public INotification {
public:
    void sendNotification(string message) override {
        cout << "  [NOTIFICATION] " << message << endl;
    }
};

class SMSNotification : public INotification {
public:
    void sendNotification(string message) override {
        cout << "  [SMS] " << message << endl;
    }
};

class EmailNotification : public INotification {
public:
    void sendNotification(string message) override {
        cout << "  [EMAIL] " << message << endl;
    }
};

#endif
