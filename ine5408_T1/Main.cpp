#include <iostream>
#include <cstdint>
#include <stdexcept>
#include <fstream>
#include <cstdlib>
#include <string>
#include <cstring>
#include "Cashier.h"
#include "Supermarket.h"

int main(int argc, char **argv)
{
    std::string readline;
    // Supermarket infos
    std::string smName;
    int smSimulationTime, smClientArrival, smCashiersNum;
    // Cashier infos
    std::string cName;
    int cEffi, cSal;


    std::ifstream file("file.dat");
    if(!file.is_open()){
        printf("DEU RUIM\n");
        return 1;
    }


    std::getline(file, smName);
    std::getline(file, readline);
    smSimulationTime = stoi(readline);
    std::getline(file, readline);
    smClientArrival = stoi(readline);
    std::getline(file, readline);
    smCashiersNum = stoi(readline);

    std::cout << "\nAlunos: Leonardo de Oliveira da Silva e Patrick Machado\n\n";
    std::cout << "Simulacao Tempo: " << smSimulationTime << "h - Clientes a cada: " << smClientArrival << "s \n\n";

    std::cout << "Supermercado: " << smName;
    auto superm = supermarket::Supermarket(smName, smSimulationTime, smClientArrival);

    //supermarket::Cashier *ptrCashier;
    //ptrCashier = new supermarket::Cashier[smCashiersNum];

    for(int i = 0; i < smCashiersNum; ++i){
        std::getline(file, cName);
        std::getline(file, readline);
        cEffi = stoi(readline);
        std::getline(file, readline);
        cSal = stoi(readline);

        supermarket::Cashier c(cName, cEffi, cSal);
        //ptrCashier[i] = c;
        superm.addCashier(c);
    }

    puts("");

    superm.printCashiers();

    puts("");

    int clientArrivalAux = 0;
    int auxcounter = 0;
    int caixaEntrar = 0;
    int qtdClientesNaFila = 0;
    int qtdAuxCaixa = 0;
    int clientesDesistentes = 0;
    int valorCompraDesistentes = 0;
    int valorCompraAtendidos = 0;
    // Simulation start
    while(superm.currentClock() < superm.totalClock()){
        // Client In
        if(clientArrivalAux == smClientArrival-1){
            caixaEntrar = 0;
            // Create Client
            supermarket::Client novo(superm.currentClock());
            if(novo.smart()){
                qtdAuxCaixa = superm.cashiers_.at(0).qtdProdutos();
                for(int i = 1; i < superm.cashiers_.size(); ++i){
                    if(superm.cashiers_.at(i).qtdProdutos() < qtdAuxCaixa){
                        caixaEntrar = i;
                        qtdAuxCaixa = superm.cashiers_.at(i).qtdProdutos();
                        if(superm.cashiers_.at(i).clientsInQueue_ < qtdClientesNaFila)
                            qtdClientesNaFila = superm.cashiers_.at(i).clientsInQueue_;
                    }
                }
            }else{
                qtdClientesNaFila = superm.cashiers_.at(0).clientsInQueue_;
                for(int i = 1; i < superm.cashiers_.size(); ++i){
                    if(superm.cashiers_.at(i).clientsInQueue_ < qtdClientesNaFila){
                        caixaEntrar = i;
                        qtdClientesNaFila = superm.cashiers_.at(i).clientsInQueue_;
                    }
                }
            }
            if(qtdClientesNaFila < 10){
                superm.cashiers_.at(caixaEntrar).addClient(novo);
            }else{
                ++clientesDesistentes;
                valorCompraDesistentes += novo.value();
            }
            ++auxcounter;
            clientArrivalAux = 0;
        }else{
            ++clientArrivalAux;
        }

        // Client Out
        for(int i = 0; i < superm.cashiers_.size(); ++i){
            superm.cashiers_.at(i).checkClientExit(superm.currentClock());
        }


        superm.currentClock(superm.currentClock()+1);
    }

    int totalClientesAtendidosSuperM = 0;
    for(int i = 0; i < superm.cashiers_.size(); ++i){
        totalClientesAtendidosSuperM += superm.cashiers_.at(i).totalClients_;
        valorCompraAtendidos += superm.cashiers_.at(i).totalIncome_;
    }

    std::cout << "Clientes atendidos:\t\t" << totalClientesAtendidosSuperM << "\n";
    std::cout << "Clientes que desistiram:\t" << clientesDesistentes << "\n";
    std::cout << "Faturamento total:\t\t" << valorCompraAtendidos << "\n";
    std::cout << "Faturamento perdido:\t\t" << valorCompraDesistentes << "\n";
    std::cout << "Faturamento médio:\t\t" << valorCompraAtendidos/superm.cashiers_.size() << "\n";
    std::cout << "Clients recebidos:\t\t" << auxcounter << "\n";

    return 0;
}
