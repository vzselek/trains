#ifndef TRAINS_STATION_H
#define TRAINS_STATION_H

#include <list>
#include <mutex>
#include <boost/optional.hpp>
#include "Cargo.h"

namespace imc {

class Station
{
	friend class StationThread;
public:

	Station() : m_id(0)
	{}

	void SetId(unsigned int id) { m_id = id; }

	boost::optional<Cargo> GetOneCargo(unsigned int maxSize);
	void AddCargo(const Cargo& cargo);

private:
	unsigned int m_id;
	std::mutex m_mutex;
	std::list<Cargo> m_cargos;
};

} // namespaces

#endif  //TRAINS_STATION_H
