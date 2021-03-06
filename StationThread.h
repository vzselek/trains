#ifndef TRAINS_STATIONTHREAD_H
#define TRAINS_STATIONTHREAD_H

namespace imc {

class RailSystem;
class Station;

class StationThread
{
public:

	StationThread(
		RailSystem& railSystem,		
		Station& station)
	:
		m_railSystem(railSystem),
		m_station(station)
	{}

	void operator()();

private:

	RailSystem& m_railSystem;
	Station& m_station;
};

} // namespaces

#endif  //TRAINS_STATIONTHREAD_H