//
// Created by ahmed on 12/24/16.
//

#include <DataPacket.h>
#include "BinarySerializer.h"

void BinarySerializer::SerializeDataPacket(DataPacket *data_pack, void **projected_data_ptr)
{
    (*projected_data_ptr) = reinterpret_cast<void *>(data_pack);
}

void BinarySerializer::DeserializeDataPacket(void *packetBytes,
        DataPacket **recovered)
{
    (*recovered) = reinterpret_cast<DataPacket *>(packetBytes);
}

void BinarySerializer::SerializeAckPacket(AckPacket *ack_pack, void **projected_ack_ptr)
{
    (*projected_ack_ptr) = reinterpret_cast<void *>(ack_pack);
}

void BinarySerializer::DeserializeAckPacket(void *packetBytes, AckPacket **recovered)
{
    (*recovered) = reinterpret_cast<AckPacket *>(packetBytes);
}
