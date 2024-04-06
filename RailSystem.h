#ifndef TRAINS_RAILSYSTEM_H
#define TRAINS_RAILSYSTEM_H

#include <memory>
#include <thread>
#include <vector>
//#include <boost/scoped_array.hpp>
#include "Station.h"
#include "Track.h"
#include "TrainData.h"

namespace imc {

class RailSystem
{
public:
    RailSystem(
        unsigned int numStations,
        unsigned int numTrains,
        const std::vector<unsigned int>& trackLengths,
        const std::vector<unsigned int>& trainSpeeds,
        const std::vector<unsigned int>& trainCapacities,
        const std::vector<unsigned int>& trainStartPositions);

    void Start();
    void Stop();
    bool IsStopped() const;

    unsigned int GetNumStations() const { return m_numStations; }

    Station& GetStation(unsigned int stationId) { return m_stations[stationId]; }
    Track& GetTrack(unsigned int trackId) { return m_tracks[trackId]; }

private:
    volatile bool m_stopped;

    unsigned int m_numStations;
    unsigned int m_numTrains;

    //boost::scoped_array<Track> m_tracks;
    std::unique_ptr<Track[]> m_tracks;
    
    //boost::scoped_array<Station> m_stations;
    std::unique_ptr<Station[]> m_stations;

    std::vector<TrainData> m_initTrainData;
    
    std::vector<std::thread> m_stationThreads;
    std::vector<std::thread> m_trainThreads;
};

} // namespaces

#endif  //TRAINS_RAILSYSTEM_H