/*
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include "Passenger.h"
/*
print()
 *    Purpose: to print out the passengers arrival and departure info to the 
                terminal 
 * Parameters: output stream  
 *    Returns: N/A, void function
*/
void Passenger::print(std::ostream &output)
{
        output << "[" << id << ", " << from << "->" << to << "]";
}
