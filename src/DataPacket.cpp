//
// Created by ahmed on 12/24/16.
//

#include <iostream>
#include <cstring>
#include "DataPacket.h"

DataPacket::DataPacket()
{}

DataPacket::DataPacket(void *data, unsigned short data_len, unsigned int seq_no)
{
    if (data_len > DATA_FRAGMENT_SIZE) {
        // TODO throw an exception
        throw std::invalid_argument("Data length is bigger than the packet data field");
    }

    this->chksum = 0;
    this->seqno = seq_no;
    this->len = data_len;

    // Copy the data into the packet
    for (int i = 0; i < data_len; ++i) {
        this->data[i] = ((char *) data)[i];
    }
}

void DataPacket::Clone(DataPacket *source)
{
    this->chksum = source->chksum;
    this->seqno = source->seqno;
    this->len = source->len;

    memcpy(this->data, source->data, source->len);
}