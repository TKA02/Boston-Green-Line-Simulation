/*
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "MetroSim.h"
#include "PassengerQueue.h"
#include <assert.h>
#include <sstream>

using namespace std;

void file_check(ifstream &input, string f);
void argument_check(unsigned int count);
void metro_terminal_start(MetroSim * init, std::string f);

int main(int argc, char *argv[])
{
   ifstream comfile;
   string stations, outputFileName, commandFile;
   string user_input;
   argument_check(argc);

   stations = argv[1];
   outputFileName = argv[2];
   comfile.open(stations);
   file_check(comfile, stations);
   MetroSim inst(comfile, outputFileName);
   comfile.close();
   
   if(argc == 4) {
    metro_terminal_start(&inst, argv[3]);
   } else {

    inst.sim_print(std::cout);
    cout << "Command? ";
    while(getline(cin, user_input, '\n'))
        {
            inst.start(user_input);
            cout << "Command? ";
        }
   }
   if(cin.fail()) {// means that there was no "m f" command inputed
    
    inst.start("m f");
   }
   return 0;
}
/*
file_check()
 *    Purpose: check if the ifstrem is able to open the file from the terminal
 * Parameters: an inputed ifstream, and the name of the file
 *    Returns: N/A
 *
 *       Note: prints an error message to the terminal if the file is not able
            to be opened
*/
void  file_check(ifstream &input, std::string f)
{
    if(not input.is_open())
    {
        cerr << "Error: could not open file " << f << endl;
        exit(EXIT_FAILURE);
    }
}
/*
argument_check()
 *    Purpose: checks that the correct number of arguemnts is being inputed to
            the terminal 
 * Parameters: an inputed argc
 *    Returns: N/A
 *
 *       Note: prints out an error message if the wrong amount of 
            command line arguments
*/
void argument_check(unsigned int count)
{
     if(count <= 2 or count > 4) {
        cerr << "Usage: ./MetroSim stationsFile outputFile [commandsFile]";
        exit(EXIT_FAILURE);
   }
}
/*
metro_terminal_start()
 *    Purpose: if the correct number of argc is reached, then the function 
        opens and inputes the commands within the file to the metrosim
 * Parameters: ptr to the metrosim instance, and name of the commands file
 *    Returns: N/A
*/
void metro_terminal_start(MetroSim * init, std::string f)
{
    ifstream comfile;
    comfile.open(f);
    file_check(comfile,f);
    init -> sim_print(std::cout);
    std::string com;

    cout << "Command? ";
    while(getline(comfile, com, '\n'))
    {
        init -> start(com);
        cout << "Command? ";
    }
    
    if(com != "m f")
    {
        init -> start("m f");
    }

    comfile.close(); 
}