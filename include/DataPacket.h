//
// Created by ahmed on 12/24/16.
//

#ifndef ENHANCEDUDPCLIENT_DATAPACKET_H
#define ENHANCEDUDPCLIENT_DATAPACKET_H


class DataPacket
{
    DataPacket();

public:
    /* Header */
    unsigned short cksum;
    unsigned short len;
    unsigned int seqno;

    /* Data */
    char data[248] = {0}; // Struct total size is 256 bytes
    static DataPacket Create(void *data, unsigned int data_length, unsigned int seq_no);
};


#endif //ENHANCEDUDPCLIENT_DATAPACKET_H
