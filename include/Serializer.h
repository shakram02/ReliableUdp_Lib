//
// Created by ahmed on 12/24/16.
//

#ifndef UDPSOCKETLIB_SERIALIZER_H
#define UDPSOCKETLIB_SERIALIZER_H


#include "AckPacket.h"

class Serializer
{
public:
    /**
     * Takes a data packet and converts it to raw binary data
     * @param data_pack Input data packet
     * @param ptr Pointer to the output raw binary data
     */
    static void SerializeDataPacket(DataPacket data_pack, void *ptr);

    /**
     * Takes an ACK packet and converts it to raw binary data
     * @param ack_pack Input ACK packet
     * @param ptr Pointer to the output raw binary data
     */
    static void SerializeAckPacket(AckPacket ack_pack, void *ptr);

    /**
     * Takes an array of raw binary data and returns its equivalent Data Packet
     * @param packetBytes Raw binary data
     * @param packet_len Length of the binary data array
     * @return A reconstructed DataPacket from the provided binary data
     */
    static DataPacket DeserializeDataPacket(void *packetBytes, unsigned int packet_len);

    /**
     * Takes an array of raw binary data and returns its equivalent ACK Packet
     * the length of the ack packet is constant
     * @param packetBytes Raw binary data
     * @return A reconstructed ACK Packet from the provided binary data
     */
    static AckPacket DeserializeAckPacket(void *packetBytes);
};


#endif //UDPSOCKETLIB_SERIALIZER_H
