#ifndef CASHIER_H
#define CASHIER_H

#include <iostream>
#include <string>
#include <cstring>
#include "Queue.h"
#include "Client.h"

namespace supermarket {

    using std::string;

    class Cashier{

        public:
            Cashier(std::string name, int efficiency, int salary);
            Cashier();
            LinkedQueue<Client> clients;
            int efficiency_;
            int salary_;
            int totalClients_ {0};
            int clientsInQueue_ {0};
            int totalTimeInQueue_ {0};
            int averageTimeInQueue {0};
            double totalIncome_ {0};
            std::string name_;
            int queueTime();
            void checkClientExit(int time);
            void print();
            void addClient(Client c);
            int qtdProdutos();
    };

}

#endif
