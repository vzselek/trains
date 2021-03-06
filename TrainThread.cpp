#include "TrainThread.h"
#include <cassert>
#include <chrono>
#include <iostream>
#include "RailSystem.h"
#include "TrainData.h"

namespace imc {

void TrainThread::operator()()
{
	std::cout << "Train" << m_trainData.m_id << " started. Speed: " << m_trainData.m_speed <<
		", Capacity: " << m_trainData.m_capacity <<
		", Position: " << (m_trainData.m_positionType == PT_Station ? "S" : "Tr") << m_trainData.m_position << std::endl;
	
	while (!(m_railSystem.IsStopped()))
	{
		UnloadCargo();
		LoadCargo();
		EnterTrack();
		LeaveTrack();		
	}
}

void TrainThread::UnloadCargo()
{
	assert(m_trainData.m_positionType == PT_Station);

	typedef std::pair<std::multimap<unsigned int, Cargo>::iterator, std::multimap<unsigned int, Cargo>::iterator> FindCargosType;
	FindCargosType findCargos = m_trainData.m_cargos.equal_range(m_trainData.m_position);
	
	std::multimap<unsigned int, Cargo>::iterator current = findCargos.first;
	while (current != findCargos.second)
	{
		unsigned int handlingTime = current->second.m_handlingTime;
		unsigned int cargoSize = current->second.m_size;

		std::cout << "Train" << m_trainData.m_id << " Unloading cargo. Size: " << cargoSize << " Destination: "
			<< current->second.m_destination << " Handling time: " << handlingTime << std::endl;

		std::multimap<unsigned int, Cargo>::iterator toDelete = current;
		++current;
		m_trainData.m_cargos.erase(toDelete);
		m_trainData.m_capacity += cargoSize;
		Handling(handlingTime);
	}
}

void TrainThread::LoadCargo()
{
	assert(m_trainData.m_positionType == PT_Station);

	Station& station = m_railSystem.GetStation(m_trainData.m_position);

	boost::optional<Cargo> cargo;
	while (m_trainData.m_capacity > 0 && (cargo = station.GetOneCargo(m_trainData.m_capacity)))
	{
		assert(cargo->m_size < m_trainData.m_capacity);
		m_trainData.m_capacity -= cargo->m_size;
		m_trainData.m_cargos.insert(std::multimap<unsigned int, Cargo>::value_type(cargo->m_destination, *cargo));

		std::cout << "Train" << m_trainData.m_id << " Loading cargo. Size: " << cargo->m_size << " Destination: "
			<< cargo->m_destination << " Handling time: " << cargo->m_handlingTime << std::endl;

		Handling(cargo->m_handlingTime);
	}
}

void TrainThread::EnterTrack()
{
	assert(m_trainData.m_positionType == PT_Station);
	Track& track = m_railSystem.GetTrack(m_trainData.m_position);

	int trackLength = track.Enter(m_trainData.m_id);
	m_trainData.m_positionType = PT_Track;

	int travelTime = int(double(trackLength) / m_trainData.m_speed * 1000);

	std::cout << "Train" << m_trainData.m_id << " entered track:" << (m_trainData.m_positionType == PT_Station ? "S" : "Tr")
		<< m_trainData.m_position << " Travel Time: " << travelTime << " Capacity: " << m_trainData.m_capacity << std::endl;
			
	Traveling(travelTime);
}

void TrainThread::LeaveTrack()
{
	assert(m_trainData.m_positionType == PT_Track);
	
	unsigned int numStations = m_railSystem.GetNumStations();
	Track& track = m_railSystem.GetTrack(m_trainData.m_position);
	track.Leave(m_trainData.m_id);

	unsigned int position = m_trainData.m_position;
	++position;
	unsigned int newPosition = (position == numStations ? 0 : position);

	m_trainData.m_position = newPosition;
	m_trainData.m_positionType = PT_Station;

	std::cout << "Train" << m_trainData.m_id << " entered station:" << (m_trainData.m_positionType == PT_Station ? "S" : "Tr")
		<< m_trainData.m_position << " Capacity: " << m_trainData.m_capacity << std::endl;
}

void TrainThread::Traveling(int travelTime) const
{
    std::this_thread::sleep_for(std::chrono::milliseconds(travelTime));
}

void TrainThread::Handling(int handlingTime) const
{
	std::this_thread::sleep_for(std::chrono::milliseconds(handlingTime));
}

} // namespaces
