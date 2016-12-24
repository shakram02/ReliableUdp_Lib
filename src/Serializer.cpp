//
// Created by ahmed on 12/24/16.
//

#include <DataPacket.h>
#include "Serializer.h"

void Serializer::SerializeDataPacket(DataPacket data_pack, void *ptr)
{

}

void Serializer::SerializeAckPacket(AckPacket data_pack, void *ptr)
{

}

AckPacket Serializer::DeserializeAckPacket(void *packetBytes)
{
    return AckPacket::Create(0);
}

DataPacket Serializer::DeserializeDataPacket(void *packetBytes, unsigned int packet_len)
{
    return DataPacket::Create(nullptr, 0, 0);
}