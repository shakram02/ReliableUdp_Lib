//
// Created by ahmed on 12/24/16.
//

#include "DataPacket.h"
#include "Checksum.h"

DataPacket::DataPacket()
{

}

DataPacket DataPacket::Create(void *data, unsigned int data_length, unsigned int seq_no)
{
    DataPacket packet;
    // Create check sum
    Checksum::Create(packet);
    // Create packet number
    packet.seqno = seq_no;

    // Pack data
    return packet;
}
