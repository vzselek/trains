#include "StationThread.h"
#include <cassert>
#include <cstdlib>
#include <chrono>
#include <ctime>
#include <iostream>
#include "Cargo.h"
#include "RailSystem.h"

namespace imc {

void StationThread::operator()()
{
	std::cout << "Station" << m_station.m_id << " started" << std::endl;

	srand(static_cast<unsigned int>(time(0)));

	unsigned int numStations = m_railSystem.GetNumStations();
	
	while (!(m_railSystem.IsStopped()))
	{
		// Some smartness can be implemented related to the randomness of cargo creation
		// Just hardcoded some magic numbers for now

		int randomCargoTime = rand() % 10000 + 500;
		std::this_thread::sleep_for(std::chrono::milliseconds(randomCargoTime));

		int randomCargoSize = rand() % 300 + 1;
		int randomCargoHandlingTime = rand() % 300 + 1;

		int randomCargoDestination = rand() % numStations;
		if (randomCargoDestination == m_station.m_id)
		{
			if (randomCargoDestination == 0)
				randomCargoDestination = numStations - 1;
			else
				--randomCargoDestination;
		}

		Cargo cargo;
		cargo.m_size = randomCargoSize;
		cargo.m_handlingTime = randomCargoHandlingTime;
		cargo.m_destination = randomCargoDestination;
		m_station.AddCargo(cargo);

		std::cout << "Station" << m_station.m_id << " New cargo. Size: " << cargo.m_size
			<< " Destination: " << cargo.m_destination << " Handling time: " << cargo.m_handlingTime << std::endl;		
	}
}

} // namespaces
