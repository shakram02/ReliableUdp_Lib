//
// Created by ahmed on 12/25/16.
//


#include <malloc.h>
#include "PacketStore.h"

DataPacket PacketStore::CreateDataPacket(void *data, unsigned int data_length, unsigned int seq_no)
{
    DataPacket packet;
    // Create check sum
    Checksum::Create(packet);
    // Create packet number
    packet.seqno = seq_no;

    // Pack data
    return packet;
}

AckPacket PacketStore::CreateAckPacket(unsigned int ackno)
{
    return AckPacket();
}

void PacketStore::DeleteDataPacket(DataPacket *pckt_ptr)
{
    free(pckt_ptr->data);
    free(pckt_ptr);
}