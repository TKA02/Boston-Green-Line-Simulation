/*
 *  PassengerQueue.cpp
 *  Timi Kola-Abiola
 *  6/19/2022
 *
 *  CS 15 Project 1
 *
 *  To implemenent all the public and private functions decleared in
 *  PassengerQueue.cpp
 *
 */
#include "PassengerQueue.h"
#include <list>

//constructor: intializes all the private memeber variables
PassengerQueue::PassengerQueue ()
{
    m_station_id = 0;
}

// destructor: deletes all the allocated memory on the heap
PassengerQueue::~PassengerQueue()
{
 // None requried for vectors
}
/*
front()
 *    Purpose: returns the passenger at the front of the queue
 * Parameters: N/A
 *    Returns: returns a passenger instance
 *
*/
Passenger PassengerQueue:: front()
{
   return m_queue.front();
}

/*
dequene()
 *    Purpose: removes the passenger at the front of the queue
 * Parameters: N/A
 *    Returns: N/A
*/
void PassengerQueue:: dequeue()
{
    m_queue.pop_front();
}

/*
enqueue
 *    Purpose:to insert passenger at the back of the queue
 * Parameters: an & of a passenger instance
 *    Returns: N/A, void function
*/
void PassengerQueue::enqueue(const Passenger &passenger)
{
    m_queue.push_back(passenger);
    m_station_id = passenger.from;
}
/*
size()
 *    Purpose: returns the current size of the PassengerWueue vector
 * Parameters: N/A
 *    Returns: returns the interger current size 
*/
int PassengerQueue:: size ()
{
    return m_queue.size();
}

/*
print()
 *    Purpose: Prints each Passenger in the queue to the given output stream
 * Parameters: an ouput stream
 *    Returns: N/A
*/
void PassengerQueue:: print(std::ostream &output)
{
    std::list <Passenger>::iterator i = m_queue.begin();
    while (i != m_queue.end())
    {
        (*i).print(output);
        ++i;
    }
    
}

