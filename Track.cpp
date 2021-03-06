#include "Track.h"

namespace imc {

int Track::Enter(unsigned int trainId)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	
	while (!(m_isFree))
		m_condEnterTrack.wait(lock);

	m_isFree = false;
	return m_length;
}

void Track::Leave(unsigned int trainId)
{
	std::unique_lock<std::mutex> lock(m_mutex);
	m_isFree = true;
	m_condEnterTrack.notify_one();
}

} // namespaces
