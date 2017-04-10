#ifndef CLIENT_H
#define CLIENT_H

#include <ctime>
#include <cstdlib>
#include <cstdio>
#include <sys/time.h>

namespace supermarket {

class Client
{

 public:
    Client() = default;
    Client(int atime);
    int arrivalTime();
    void exitTime(int value);
    int exitTime();
    int totalSpentMoney();
    void computeCashierTime(int eff);
    int myTimeInCashier();
    bool smart();
    int items();
    int value();

 private:
    bool smart_;
    bool money_;
    int items_ {};
    int value_ {};
    int arrivalTime_ {};
    int exitTime_;
    int particularCashierTime;
};

}  /* namespace supermarket */

#endif
