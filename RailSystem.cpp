#include "RailSystem.h"
#include <cassert>
#include <iostream>
#include <stdexcept>
#include "Station.h"
#include "StationThread.h"
#include "Track.h"
#include "TrainThread.h"
#include "TrainData.h"

namespace imc {

RailSystem::RailSystem(
    unsigned int numStations,
    unsigned int numTrains,
    const std::vector<unsigned int>& trackLengths,
    const std::vector<unsigned int>& trainSpeeds,
    const std::vector<unsigned int>& trainCapacities,
    const std::vector<unsigned int>& trainStartPositions)
:
    m_numStations(numStations),
    m_numTrains(numTrains)
{
    if (numStations != trackLengths.size() ||
        numTrains != trainSpeeds.size() ||
        numTrains != trainCapacities.size() ||
        numTrains != trainStartPositions.size())
        throw std::runtime_error("Invalid initialization parameters");

    m_stopped = false;
    
    m_tracks.reset(new Track[m_numStations]);
    m_stations.reset(new Station[m_numStations]);
    for (unsigned int i = 0; i < m_numStations; ++i)
    {
        m_tracks[i].Initialize(i, trackLengths[i]);
        m_stations[i].SetId(i);
    }

    m_initTrainData.reserve(m_numTrains);
    for (unsigned int i = 0; i < m_numTrains; ++i)
    {
        TrainData tmpInitTrainData(
            i,
            trainSpeeds[i],
            trainCapacities[i],
            trainStartPositions[i]);
        m_initTrainData.push_back(tmpInitTrainData);
    }
    
    m_stationThreads.reserve(m_numStations);
    m_trainThreads.reserve(m_numTrains);
}

bool RailSystem::IsStopped() const
{
    return m_stopped;
}

void RailSystem::Start()
{
    for (unsigned int i = 0; i < m_numStations; ++i)
    {
        StationThread tmpStationThread(*this, m_stations[i]);
        m_stationThreads.push_back(std::thread(tmpStationThread));
    }

    for (unsigned int i = 0; i < m_numTrains; ++i)
    {
        TrainThread tmpTrainThread(*this, m_initTrainData[i]);
        m_trainThreads.push_back(std::thread(tmpTrainThread));
    }

    m_initTrainData.clear(); // this was used for initialization only. The train threads will own their data
}

void RailSystem::Stop()
{
    m_stopped = true;

    std::cout << "Stopping threads... " << std::endl;

    for (unsigned int i = 0; i < m_numTrains; ++i)
        m_trainThreads[i].join();

    for (unsigned int i = 0; i < m_numStations; ++i)
        m_stationThreads[i].join();
}

} // namespaces
