//
// Created by ahmed on 12/24/16.
//

#include <DataPacket.h>
#include <iostream>
#include "BinarySerializer.h"

void BinarySerializer::SerializeDataPacket(DataPacket *data_pack, void **ptr)
{
    (*ptr) = reinterpret_cast<void *>(data_pack);
}

void BinarySerializer::DeserializeDataPacket(void *packetBytes, unsigned int packet_len,
        DataPacket **recovered)
{
    (*recovered) = reinterpret_cast<DataPacket *>(packetBytes);
    //std::cout << "Unpacked:" << (*recovered)->data << std::endl;
}

void BinarySerializer::SerializeAckPacket(AckPacket *ack_pack, void **ptr)
{
    (*ptr) = reinterpret_cast<void *>(ack_pack);
}

void BinarySerializer::DeserializeAckPacket(void *packetBytes,
        AckPacket **recovered)
{
    (*recovered) = reinterpret_cast<AckPacket *>(packetBytes);
//    std::cout << "Deserializer Len:" << (*recovered)->len << std::endl;
//    std::cout << "Deserializer Checksum:" << (*recovered)->chksum << std::endl;
//    std::cout << "Deserializer ACK NUM:" << (*recovered)->ack_num << std::endl;
}

