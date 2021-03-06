#include <iostream>
#include <stdexcept>
#include "RailSystem.h"

int main(int argc, char* argv[])
{
    try
    {
        std::cout << "Press enter to stop simulation" << std::endl;

        // hardcoded for now, some initialization can be implemented
        int numStations = 8;
        int numTrains = 4;
        std::vector<unsigned int> trackLengths = { 100, 200, 300, 250, 400, 150, 300, 200 };
        std::vector<unsigned int> trainSpeed = { 70, 100, 90, 80};
        std::vector<unsigned int> trainCapacity = { 1000, 1500, 2000, 1200 };
        std::vector<unsigned int> trainStartPosition = { 0, 3, 6, 7 };
	
		imc::RailSystem railSystem(
			numStations,
			numTrains,
			trackLengths,
			trainSpeed,
			trainCapacity,
			trainStartPosition);

		railSystem.Start();	
	
		std::cin.get();
		railSystem.Stop();
	}
	catch (std::runtime_error& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (...)
	{
		std::cout << "Unknown exception happened" << std::endl;
	}
}