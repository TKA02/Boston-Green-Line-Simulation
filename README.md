# Boston-Green-Line-Simulation
/**********************************************************
* Project 1: Metro Simulator 
* README
*
*********************************************************/

Compile/run:
     - Compile using
            make MetroSim
     - run executable with
            ./MetroSim stationsFile passFile [commands]


Program Purpose: to create a simulation that simulates the actions on the 
MBTA Green Line


Acknowledgements: N/A


Files: 

main.cpp:
    * reads in files form the terminal and starts the main query loop for 
    the MetroSim 

MetroSim.cpp:   
     Implementation of MetroSim class.  Main functionality of running the Metro Simulation, moves the train and deals with passengers going 
     on/off the train. The class also splits the adding passenger command to effectively add a passenger, updates the trains current position, prints the current state of the simulation, and displays the exit message when the user 
     inputed "m f"

MetroSim.h:
    Interface of the MetroSim class includes a overloaded constructor that takes
    in a ifstream var, and a string containing the ouputfile name that was 
    retrived from terminal. The interface also contains the start() that takes 
    in a command and executes the commands throught helper functions and a 
    sim_print() that prints all relevant information about the simulation to 
    the user. 

stations.txt:
     an example file containing a list of stations.

test_commands.txt:
     sample list of commands that you could give to the simulator

the_metroSim:
     reference implementation for students to see how 


Note:  the program should handle all cases.

Data Structures:

    I used two main data sturctures for the implementation of the MetroSim. I 
    used the 'list' data structure for the PassengerQueue class and the vector 
    data struture for the MetroSim class. The 'list' data structure was used in
    for PassengerQueue because the time complexity for a linked list to remove 
    an element from the front of the list and inserting an element at the back 
    of the list are both O(1), which is better than executing the same 
    operations with a vector whose time complexity is O(n). 

    For the MetroSim, I decided to use vectors as the primary data structure 
    when modeling the train, keeping track of the stations_queue , and having 
    a list of all the station_names in the queue because the time complexity of
    accessing any element within a vector is O(1) while do the same operation 
    with a list is O(n). This meant that I had easy access to each elements
    within the vector rather than having to tranverse the entire data structure 
    to access a single element. 
    
Testing:

The primary method I used to test each of the public and private function for 
the MetroSim is by cin the commands from the terminal after I implemented the 
main query loop in main. This allowed to solve most of the functionaly errors 
of function before I used the diff command to fix any output errors that my 
code had. 

Since I used the main query loop to test each function, I could not properly 
create specific unit test for each function so I document the bugs and solution
I created for each function.

Through the first method, I noticted that my add_passenger() was correctly adding 
passengers to the correct station queue however the passenger_id for each 
passenger would reset when I added a new passenger to a different station queue.
This bug would result in duplicate ids for the passengers so that there existed 
two passengers who had the same id at different stations. To solve this problem, 
I added a private var named , "passenger_id", that I then set to the value 1 in
the overloaded constructor and incremeneted at the end of the adding_passenger().

For the next_station(), which adds waiting passengers to the train, I first used
the assert() to determine if the station queue had reduced to zero after the 
loop ended however the next_station() argument contained a copy of the revelent 
passenger queue rather than a pointer. This error meant that the passengers were 
being added to the train but the passengers still remained in the station's 
queue as well. To solve this problem, I changed the argument to able to recieve
a pointer to the station_queue. 

The disembarking() function worked in logging the leaving passengers into another 
file but the change was not represented in the train's print of all the 
passengers in the sim. This created several duplicates train and station 
queues.To remove the duplicates that appeared in the simulation print, I 
changed the argument of the disembark() to be able to recieve a pointer to the
passenger queue in the train struct. This allowed for the changes made in the 
disembark() to be reflected in the train's passenger queues. 

split_string(): I passed different p ARRIVAL DEPARTURE and printed out the int
result to the terminal to check if the function worked. I especially focused 
my testing on ARRIVAL and DEPARTURE values that was greater than 9 to make 
sure split_string() could successfully convert larger integer successfully.

sim_print(): I relied heavily on diffing my simulation with the reference sim 
to see if my sim_print() output was correct. The diff results showed that my
simulation print function didn't have a capitalized TRAIN and I had an extra 
space before printing the passengers in the train.

train_pos(): I also used the diff command to test if the train in my 
simulation was updating correctly, since the changing train position would 
reflect in the sim_print(). 

exit_message(): I cin the "m f" command to check if the functions successfully 
ends the program. I then diff my simulation with the reference simulation where
the only command in test_commands.txt was "m f". This was to make sure that 
my exit message didn't have any extra spaces. 

The last two cases I tested involving make sure my code was able to successfully 
read commands from a empty commandFile and a non-empty commandFile that doesn't 
have the "m f"

When testing for these two cases, my code would go into a infinite loop so I 
decided to switch my loop conditonal form using the ifstream fail() function 
to utilizing the getline().  
