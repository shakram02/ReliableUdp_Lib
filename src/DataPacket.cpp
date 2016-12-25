//
// Created by ahmed on 12/24/16.
//

#include "DataPacket.h"
#include "Checksum.h"

DataPacket::DataPacket()
{}

DataPacket::DataPacket(void *data, unsigned short data_len, unsigned int seq_no)
{
    this->chksum = 0;
    this->seqno = seq_no;
    this->len = data_len;

    // Copy the data into the packet
    for (int i = 0; i < data_len; ++i) {
        this->data[i] = ((char *) data)[i];
    }
}

