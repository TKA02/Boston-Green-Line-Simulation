#########################################################
#             PROJECT 1: MetroSim Makefile             #
#########################################################

CXX      = clang++
CXXFLAGS = -g3 -Wall -Wextra -Wpedantic -Wshadow
LDFLAGS  = -g3 


MetroSim: main.o MetroSim.o PassengerQueue.o Passenger.o
	$(CXX) $(CXXFLAGS) -o MetroSim main.o MetroSim.o PassengerQueue.o Passenger.o


# This rule builds PassengerQueue.o
PassengerQueue.o: PassengerQueue.cpp PassengerQueue.h Passenger.h 
	$(CXX) $(CXXFLAGS) -c PassengerQueue.cpp

MetroSim.o:MetroSim.cpp MetroSim.h PassengerQueue.h 
	$(CXX) $(CXXFLAGS) -c MetroSim.cpp

main.o: main.cpp MetroSim.h 
	$(CXX) $(CXXFLAGS) -c main.cpp
 
unit_test: unit_test_driver.o PassengerQueue.o Passenger.o
	$(CXX) $(CXXFLAGS) unit_test_driver.o MetroSim.o PassengerQueue.o Passenger.o


# remove executables, object code, and temporary files from the current folder 
# -- the executable created by unit_test is called a.out
clean: 
	rm *.o *~ a.out
