/*
* PassengerQueue.h
* Timi Kola-Abiola
* 6/19/2022
*
* CS 15 Project 1
* To create a Quene of Passenger instances

*/
#ifndef PASSENGER_QUEUE_H
#define PASSENGER_QUEUE_H

#include <iostream>
#include <list>
#include "Passenger.h"

class PassengerQueue 
{
    public :
        PassengerQueue();
        ~PassengerQueue();
        Passenger front();//returns the passenger at the front of the queue
        void dequeue();//removes the passenger at the front of the queue
        void enqueue(const Passenger &passenger);//inserts a new passenger at 
        // the back of the queue
        int size();//returns the current size of the queue
        void print(std::ostream &output);
        
    private:
        std::list<Passenger> m_queue;
        int m_station_id;
};

#endif
