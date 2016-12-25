//
// Created by ahmed on 12/24/16.
//

#ifndef ENHANCEDUDPCLIENT_DATAPACKET_H
#define ENHANCEDUDPCLIENT_DATAPACKET_H

#include "globaldefs.h"

class DataPacket
{

public:

    DataPacket();

    /**
     * Creates a data packet by copying the data supplied in *data to the
     * local data field of the packet using the given length
     * @param data Data to be copied to the packet
     * @param data_len Length of data
     * @param seq_no Sequence number of the packet
     */
    DataPacket(void *data, unsigned short data_len, unsigned int seq_no);

    /**
     * Checksum for all the other fields in the packet
     */
    unsigned short chksum;
    /**
     * Length of data inside the data field
     * Header + data
     */
    unsigned short len;
    /**
     * Sequence number of the packet
     */
    unsigned int seqno;


    /**
     * The size data in the packet isn't dynamic
     * but will rather be known using the len field
     */
    char data[DATA_FRAGMENT_SIZE] = {0};
};


#endif //ENHANCEDUDPCLIENT_DATAPACKET_H
