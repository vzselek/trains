#include "Station.h"

namespace imc {

boost::optional<Cargo> Station::GetOneCargo(unsigned int maxSize)
{
	std::unique_lock<std::mutex> lock(m_mutex);

	if (m_cargos.size() == 0)
		return boost::optional<Cargo>();

	for (std::list<Cargo>::iterator it = m_cargos.begin(); it != m_cargos.end(); ++it)
	{
		if (it->m_size <= maxSize)
		{
			Cargo ret(*it);
			m_cargos.erase(it);
			return ret;
		}
	}

	return boost::optional<Cargo>();
}

void Station::AddCargo(const Cargo& cargo)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_cargos.push_back(cargo);
}

} // namespaces

