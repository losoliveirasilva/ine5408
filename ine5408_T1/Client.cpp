#include "Client.h"

namespace supermarket {

    Client::Client(int atime):
        //smart_{rand()%2 != 0},
        //items_{rand()%99 + 2},
        arrivalTime_{atime}
    {
        struct timeval time; 
        gettimeofday(&time,NULL);
        
        srand((time.tv_sec * 1) + (time.tv_usec / 1));
        //srand(time(NULL));

        smart_ = rand()%2 != 0;
        items_ = rand()%99 + 2;
        money_ = (rand()%101 > 80)?true:false;

        value_ = 0;
        for (int i = 0; i < items_; ++i) {
            value_ += rand()%90 + 1;
        }
    }
    
    int Client::arrivalTime(){
        return arrivalTime_;
    }

    void Client::exitTime(int value){
        exitTime_ = arrivalTime_ + value;
    }

    int Client::exitTime(){
        return exitTime_;
    }

    int Client::totalSpentMoney(){
        return value_;
    }

    void Client::computeCashierTime(int eff){
        particularCashierTime = 0;
        switch(eff){
            case 1:
                particularCashierTime += items_;
                if(!money_)
                    particularCashierTime += 10;
                break;
            case 2:
                particularCashierTime += 2*items_;
                if(!money_)
                    particularCashierTime += 25;
                break;
            case 3:
                particularCashierTime += 4*items_;
                if(!money_)
                    particularCashierTime += 60;
                break;
        }
        return;
    }
    
    int Client::myTimeInCashier(){
        return particularCashierTime;
    }

    bool Client::smart(){
        return smart_;
    }

    int Client::items(){
        return items_;
    }

    int Client::value(){
        return value_;
    }

} /* namespace supermarket */
