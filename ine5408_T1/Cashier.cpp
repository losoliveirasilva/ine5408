#include "Cashier.h"

namespace supermarket {

    Cashier::Cashier(std::string name, int efficiency, int salary)
    {
        name_ = name;
        salary_ = salary;
        efficiency_ = efficiency;
    }

    Cashier::Cashier()
    {
        name_ = "Nome";
        salary_ = 0;
        efficiency_ = 1;
    }

    int Cashier::queueTime()
    {
        return totalTimeInQueue_;
    }

    void Cashier::checkClientExit(int time){
        if(clients.empty()){
            return;
        } else if(time == clients.front().exitTime()){
            //printf("Hora: %d - ArrivalTime: %d - SelfTime: %d - Hora de saida: %d\n", time+1, clients.front().arrivalTime(), clients.front().myTimeInCashier(), clients.front().exitTime()+1);
            ++totalClients_;
            totalIncome_ += clients.front().totalSpentMoney();
            averageTimeInQueue = (clients.front().exitTime() - clients.front().arrivalTime() + averageTimeInQueue) / totalClients_; 
            --clientsInQueue_;
            totalTimeInQueue_ -= clients.front().myTimeInCashier();
            clients.dequeue();
            return;
        }
    }

    void Cashier::print(){
	std::cout << "\tName: " << name_ << " - Efficiency: " << efficiency_ << " - Salary: " << salary_ << " \n";
    }

    void Cashier::addClient(Client c){
        ++clientsInQueue_;
        c.computeCashierTime(efficiency_);
        c.exitTime(totalTimeInQueue_ + c.myTimeInCashier());
        totalTimeInQueue_ += c.myTimeInCashier();
        clients.enqueue(c);
        //printf("Hora: %d - QueueTime: %d - SelfTime: %d - Hora de saida: %d - QtdClientes: %d - ClienteSmart: %d\n", c.arrivalTime()+1, (totalTimeInQueue_-c.myTimeInCashier()), c.myTimeInCashier(), c.exitTime()+1, clientsInQueue_, c.smart());
    }

    int Cashier::qtdProdutos(){
        int ret = 0;
        for(int i = 0; i < clients.size(); ++i){
            ret += clients.at(i).items();
        }
        return ret;
    }

} /* namespace supermarket */
