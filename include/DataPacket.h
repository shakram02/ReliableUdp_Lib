//
// Created by ahmed on 12/24/16.
//

#ifndef ENHANCEDUDPCLIENT_DATAPACKET_H
#define ENHANCEDUDPCLIENT_DATAPACKET_H


class DataPacket
{

public:

    DataPacket();
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
    char data[128] = {0};
};


#endif //ENHANCEDUDPCLIENT_DATAPACKET_H
