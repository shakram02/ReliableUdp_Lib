//
// Created by ahmed on 12/24/16.
//

#include <DataPacket.h>
#include "BinarySerializer.h"

void BinarySerializer::SerializeDataPacket(DataPacket *data_pack, void **ptr)
{

    (*ptr) = reinterpret_cast<void *>(data_pack);
}

DataPacket BinarySerializer::DeserializeDataPacket(void *packetBytes, unsigned int packet_len)
{
    DataPacket *pRec = reinterpret_cast<DataPacket *>(packetBytes);
    //cout << "Unpacked:" << pRec->data << endl;
    return (*pRec);
}

void BinarySerializer::SerializeAckPacket(AckPacket data_pack, void **ptr)
{

}

AckPacket BinarySerializer::DeserializeAckPacket(void *packetBytes)
{
    return AckPacket();
}

