#ifndef TRAINS_TRAINDATA_H
#define TRAINS_TRAINDATA_H

#include <map>
#include "Cargo.h"

namespace imc {

enum PositionType
{
    PT_Station,
    PT_Track
};

struct TrainData
{
    TrainData(
        unsigned int id,
        int speed,
        unsigned int initialCapacity,
        unsigned int startPosition)
    :
        m_id(id),
        m_speed(speed),
        m_capacity(initialCapacity),
        m_position(startPosition),
        m_positionType(PT_Station)
    {}

    unsigned int m_id;
    int m_speed;
    unsigned int m_capacity;

    std::multimap<unsigned int, Cargo> m_cargos;
    
    unsigned int m_position;
    PositionType m_positionType;
};

} // namespaces

#endif  //TRAINS_TRAINDATA_H