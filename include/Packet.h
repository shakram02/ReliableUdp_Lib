//
// Created by ahmed on 12/24/16.
//

#ifndef ENHANCEDUDPCLIENT_DATAPACKET_H
#define ENHANCEDUDPCLIENT_DATAPACKET_H

#include "globaldefs.h"
#include <memory>
#include <iostream>
#include <cstring>
#include <vector>
#include <deque>

using std::unique_ptr;

namespace Networking
{
    typedef unsigned char byte;

    class Packet
    {

    public:

        inline Packet();

        /**
         * Move constructor
         * into the current instance, a pointer is used only to improve efficiency
         * @param source Source Packet location
         */
        inline Packet(Packet &&source);

        inline Packet &operator=(Packet &&other);

        /**
         * The copy constructor isn't needed, this is an immutable object
         * @param source
         */
        inline Packet(Packet &source) = delete;

        /**
         * The copy assignment operator isn't needed, this is an immutable object
         * @param source
         */
        inline Packet &operator=(Packet &other)= delete;

        /**
         * Creates a data packet by copying the data supplied in *data to the
         * local data field of the packet using the given length
         * @param data Data to be copied to the packet
         * @param data_len Length of data
         * @param seq_no Sequence number of the packet
         */
        inline Packet(std::vector<byte> &data_bytes, unsigned short data_len, unsigned int seq_no);

        /**
         * Transforms the content of the packet to an array of bytes
         * @return Serialized byte array
         */
        inline unique_ptr<std::deque<byte>> Serialize();

        /**
         * Checksum for all the other fields in the packet
         */
        unsigned short chksum;
        /**
         * Length of data inside the data field
         * Header + data
         */
        unsigned short len;
        /**
         * Sequence number of the packet
         */
        unsigned int seqno;

        /**
         * The size data in the packet isn't dynamic
         * but will rather be known using the len field
         */
        unique_ptr<byte> data = nullptr;

        template<typename T>
        static inline unique_ptr<T> DeSerialize(std::deque<byte> *bytes);

        static inline unique_ptr<std::vector<byte>>
        DeSerializeData(std::deque<byte> *bytes, unsigned short length);

    private:
        inline void Serialize(unsigned short data, std::deque<byte> *bytes);

        inline void Serialize(unsigned int data, std::deque<byte> *bytes);
    };
}


#endif //ENHANCEDUDPCLIENT_DATAPACKET_H