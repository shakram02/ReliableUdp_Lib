//
// Created by ahmed on 12/24/16.
//

#ifndef UDPSOCKETLIB_SERIALIZER_H
#define UDPSOCKETLIB_SERIALIZER_H


#include "AckPacket.h"

class BinarySerializer
{
public:
    /**
     * Takes a data packet and converts it to raw binary data
     * @param data_pack Input data packet
     * @param ptr Pointer to the output raw binary data
     */
    static void SerializeDataPacket(DataPacket *data_pack, void **ptr);

    /**
     * Takes an ACK packet and converts it to raw binary data
     * @param ack_pack Input ACK packet
     * @param ptr Pointer to the output raw binary data
     */
    static void SerializeAckPacket(AckPacket *ack_pack, void **ptr);

    /**
     * Takes an array of raw binary data and returns its equivalent Data Packet
     * Representing the DataPacket as a simple struct (non-pointer) alawys fails to work
     * so a (DataPacket**) must be passed to the function so a value of (DataPacket*) is set
     * The user can then proceed the re-projected DataPacket only through its pointer
     * That is a lesson that I learned the hard way.
     * @param packetBytes Raw binary data
     * @param packet_len Length of the binary data array
     * @return A reconstructed DataPacket from the provided binary data
     */
    static void DeserializeDataPacket(void *packetBytes,
            unsigned int packet_len, DataPacket **recovered);

    /**
     * Takes an array of raw binary data and returns its equivalent ACK Packet
     * the length of the ack packet is constant
     * A AckPacket** must be passed to the function so the re-projection works correctly
     * @param packetBytes Raw binary data
     * @return A reconstructed ACK Packet from the provided binary data
     */
    static void DeserializeAckPacket(void *packetBytes, AckPacket **recovered);
};


#endif //UDPSOCKETLIB_SERIALIZER_H
