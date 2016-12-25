//
// Created by ahmed on 12/25/16.
//

#ifndef UDPSOCKETLIB_PACKETSTORE_H
#define UDPSOCKETLIB_PACKETSTORE_H


#include "DataPacket.h"
#include "AckPacket.h"
#include <Checksum.h>

class PacketStore
{
    /**
    * Creates a data packet to be serialized then sent to the client
    * @param data Data that will be placed inside the packet
    * @param data_length length of the data field
    * @param seq_no sequence number of this packet
    * @return a constructed packet that's ready for serialization
    */
    static DataPacket CreateDataPacket(void *data, unsigned int data_length, unsigned int seq_no);

    /**
     * Creates an ACK packet to be serialized then sent to the client
     * @param ackno Acknowledgement number of this packet
     * @return a constructed packet that's ready for serialization
     */
    static AckPacket CreateAckPacket(unsigned int ackno);


    /**
     * Releases the resources acquired by a packet
     * @param pckt_ptr Pointer too the packet that will be disposed
     */
    void DeleteDataPacket(DataPacket *pckt_ptr);
};


#endif //UDPSOCKETLIB_PACKETSTORE_H
