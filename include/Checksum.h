//
// Created by ahmed on 12/24/16.
//

#ifndef ENHANCEDUDPCLIENT_CHECKSUM_H
#define ENHANCEDUDPCLIENT_CHECKSUM_H

#include "DataPacket.h"
#include <cstdint>


class Checksum
{
    Checksum();

public:
    /**
      * Creates a checksum for a provided packet
      * @param packet input packet
      * @return 32-bit checksum
      */
    static uint32_t Create(DataPacket packet);
};


#endif //ENHANCEDUDPCLIENT_CHECKSUM_H
