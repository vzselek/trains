#ifndef TRAINS_TRAINTHREAD_H
#define TRAINS_TRAINTHREAD_H

#include "TrainData.h"

namespace imc {

class RailSystem;

class TrainThread
{
public:

	TrainThread(
		RailSystem& railSystem,		
		TrainData& trainData)
	:
		m_railSystem(railSystem),
		m_trainData(trainData)
	{}

	void operator()();

private:

	void UnloadCargo();
	void LoadCargo();
	void Handling(int handlingTime) const;

	void EnterTrack();
	void Traveling(int travelTime) const;
	void LeaveTrack();

	RailSystem& m_railSystem;
	TrainData m_trainData;
};

} // namespaces

#endif  //TRAINS_TRAINTHREAD_H