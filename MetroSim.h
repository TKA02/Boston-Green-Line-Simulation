/*
* MetroSim.h
* Timi Kola-Abiola
* 6/21/2022
*
* CS 15 Project 1
To implement the main functions of the MetroSim 

*/

#ifndef _METROSIM_H_
#define _METROSIM_H_

#include "Passenger.h"
#include "PassengerQueue.h"
#include <vector>
#include <fstream>
#include <assert.h>

// Put any other necessary includes here


// Put any other structs you need 
struct Train {
        std::vector<PassengerQueue> m_wagons;
        int current_station;
};

class MetroSim
{
public:
    MetroSim(std::ifstream &input, std::string output_file);
    ~MetroSim();
    void start(std::string command);
    void sim_print(std::ostream &output);

private:
    Train m_t1;
    std::vector <std::string> m_station_list;
    std::vector <PassengerQueue> m_stations_queue;
    int passenger_id;
    std::string log_file;
    std::ofstream out;
    void add_passenger(int from, int to);
    void next_station(PassengerQueue * q);
    void disembarking(PassengerQueue * exit);
    void exit_message();
    void split_string(std::string com, int * f, int * t);
    void print_helper(std::ostream &output);
    void train_pos();

};

#endif
