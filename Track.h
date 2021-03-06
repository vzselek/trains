#ifndef TRAINS_TRACK_H
#define TRAINS_TRACK_H

#include <condition_variable>
#include <mutex>

namespace imc {

class Track
{
public:
	Track() :
		m_isFree(true), m_length(0)
	{}

	void Initialize(unsigned int id, unsigned int length)
	{
		m_id = id;
		m_length = length;
	}

	int Enter(unsigned int trainId);
	void Leave(unsigned int trainId);

private:
	unsigned int m_id;
	bool m_isFree;
	unsigned int m_length;

	mutable std::mutex m_mutex;
	std::condition_variable m_condEnterTrack;
};

} // namespaces

#endif  //TRAINS_TRACK_H