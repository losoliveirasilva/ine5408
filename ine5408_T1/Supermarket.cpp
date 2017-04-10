#include "Supermarket.h"

namespace supermarket {

    Supermarket::Supermarket(std::string name,
                             int simulationTime,
                             int averageClientArrival):
        simulationTime_{simulationTime*3600},
        averageClientArrival_{averageClientArrival}
    {
        name_ = name;
    }

    void Supermarket::addCashier(Cashier c){
        cashiers_.push_front(c);
    }

    void Supermarket::printCashiers(){
        printf("Caixas:\n");
        for(int i = 0; i < cashiers_.size(); ++i){
            cashiers_.at(i).print();
        }
    }

    int Supermarket::currentClock(){
        return clock_;
    }

    void Supermarket::currentClock(int value){
        clock_ = value;
    }

    int Supermarket::totalClock(){
        return simulationTime_;
    }

} /* namespace supermarket */
