/*  
 *
 */

#include "MetroSim.h"
#include <sstream>
#include <iostream>
#include <string>
#include <ostream>
/*
Overloaded Constructor
 *    Purpose: to intialize the vector of stations names
 * Parameters: an string array and the size of the array 
 *    Returns: N/A, constructor 
*/
MetroSim::MetroSim(std::ifstream &input, std::string output_file)
{
    while(not input.fail())
    {
        std::string name;
        getline(input, name);//gets the entire name from the stations file
        m_station_list.push_back(name);//add station name to the vector
    }
    m_t1.current_station = 0;//starts the train at station_0
    m_t1.m_wagons.resize(m_station_list.size(),PassengerQueue());
    //increases the size of the vector to the largests possible amount 
    //and intializes all the index with a Passenger
    m_stations_queue.resize(m_station_list.size(),PassengerQueue());
    passenger_id = 1;
    log_file = output_file;
    out.open(log_file);
}
/*Destructor */
MetroSim:: ~MetroSim()
{
    //lists and vectors do not need destructor
}
/*
start()
 *    Purpose: starts the main query loop for the simulation 
 * Parameters: a string containing the inputed command 
 *    Returns: N/A, void function 
*/
void MetroSim:: start(std::string command)
{
    if(command[0]== 'p') {
        int from, to;
        split_string(command, &from, &to);
        add_passenger(from, to);// adds passenger to the current station queue
        sim_print(std::cout);
   } else if(command == "m m") {
        next_station(&m_stations_queue[m_t1.current_station]);
        // adds passengers from the current station to the train
        train_pos();// moves the train in the sim
        disembarking(&m_t1.m_wagons[m_t1.current_station]);
        //all passengers going to current station leave the sim
        sim_print(std::cout);  
   } else if(command == "m f") {
        out.close();
        exit_message();
   }

}

/*
train_pos()
 *    Purpose:to update the current_station var of the train 
 * Parameters: N/A
 *    Returns: N/A
*/

void MetroSim:: train_pos()
{
    unsigned int past_curr = m_t1.current_station;
    if(past_curr == m_station_list.size() - 2)
    {
        m_t1.current_station = 0;//resets the train current station after 
        //it reaches the last station in the sim
    } else {
        ++m_t1.current_station;
    }
}
/*
sim_print ()
 *    Purpose:prints the outline of the sim after each command  
 * Parameters: ostream var 
 *    Returns: N/A, void function
*/
void MetroSim:: sim_print(std::ostream &output)
{
    unsigned int i = 0;
    output << "Passengers on the train: {";
    while(i < m_t1.m_wagons.size())
    {
        if(m_t1.m_wagons[i].size() != 0)
        {
        m_t1.m_wagons[i].print(output);//prints all the passengers in the train
        }
        ++i;
    }
    output << "}" << std::endl;
    print_helper(output);
}
/*
print_helper()
 *    Purpose: prints where the train is on the simulation
 * Parameters: ostream output
 *    Returns: N/A, void function
*/
void MetroSim::print_helper(std::ostream &output)
{
    unsigned int train_index = m_t1.current_station;
    for(unsigned int k = 0; k < m_station_list.size() - 1; k++)
    {
        if(train_index == k)//if train is at the station in the station's list
        {
            output << "TRAIN: [" << k << "] " << m_station_list[k];
            output <<  " {";
            if(m_stations_queue[k].size() != 0)
            {
                m_stations_queue[k].print(output);
            }
            output << "}" << std::endl;
        }else { 
            output << "       [" << k << "] " << m_station_list[k] << " {";
            if(m_stations_queue[k].size() != 0)
            {
                m_stations_queue[k].print(output);//print all the passengers at
                //the station
            }
            output << "}" << std::endl;
        }
    }
}
/*
add_passenger()
 *    Purpose: adds passenger to either the train or a seperate queue based on 
the passenger's arrival station 
 * Parameters: int representing the stations the passenger is from and 
 an int representing the station the passenger is going to. 
 *    Returns: N/A, void function
*/
void MetroSim:: add_passenger(int from, int to)
{
    Passenger p(passenger_id, from, to);
    m_stations_queue[p.from].enqueue(p);//add passenger to the station queue 
    //based on what station the passenger arrived at 
    passenger_id++;
}
/*
next_station()
 *    Purpose:onboards waiting passengers to the train
 * Parameters: an passenger queue instance 
 *    Returns: N/A
*/
void MetroSim::next_station(PassengerQueue * q)
{
    
    while (q ->size() != 0)
    {
        m_t1.m_wagons[q ->front().to].enqueue(q ->front());//adds passenger at the 
        //front of the queue to the train depending on what station the 
        //passenger is heading to 
        q ->dequeue();// removes the already added passenger to the queue
    }
}

/*
exit_message()
 *    Purpose: formats the exit message when the simulation ends
 * Parameters: N?A
 *    Returns: returns the string containing the string message
*/
void MetroSim::exit_message()
{
    std::cout << "Thanks for playing MetroSim. Have a nice day!" << std::endl;
    exit(EXIT_SUCCESS);
}
/*
split_string()
 *    Purpose:to split the adding passenger command and convert the arrival
              and departure numbers into string
 * Parameters: string adding passenger command, and pointers to two int var
 *    Returns: N/A
*/
void MetroSim:: split_string(std::string com, int * f, int * t)
{
    std::stringstream split(com);
    std::string word;
    split >> word;// gets the "p" part of the command
    split >> word;// gets the first number from the command
    *f = stoi(word);//converts the first # to an int
    split >> word;// gets the last number from the command
    *t = stoi(word);// converts the second # to an int 
}
/*
disembarking()
 *    Purpose:to removes passengers from the train who arrive at their 
            station and print the leaving passenger to separate file
 * Parameters: ptr to a passenger instance
 *    Returns: N/A
*/
void MetroSim:: disembarking(PassengerQueue * e)
{
    while (e ->size() != 0)
    {
        if(out.is_open())
        {
            out << "Passenger " << e ->front().id << " left train at station ";
            out << m_station_list[m_t1.current_station] << std::endl;
            e ->dequeue();  
        }else {
            std::cerr << "Error: could not open file "  << log_file << std::endl;
            exit(EXIT_FAILURE);
        }
    } 
}