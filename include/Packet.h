//
// Created by ahmed on 12/24/16.
//

#ifndef ENHANCEDUDPLIB_PACKET_H
#define ENHANCEDUDPLIB_PACKET_H


#include "UdpLibGlobaldefs.h"
#include <vector>
#include <memory>
#include <sstream>
#include <PacketHeader.h>

using std::unique_ptr;


/**
 *  Represents a data packet, this class is immutable
 */
class Packet
{
private:
    /**
     * The size data in the packet isn't dynamic
     * but will rather be known using the len field
     */
    unique_ptr<ByteVector> data;

    /**
     * This constructor is used in the deserialization process
     */
    Packet();

    /**
     * Deserialize a type from its raw representation
     * this function is inline-d for performance
     * @tparam T Type of item to be serialized ( must be a primitive type )
     * @param bytes Raw bytes of data
     * @param startIndex starting index of the desired data in the given raw representation
     * @return An instance of the requested type deserialized from raw representation
     */
    template<typename T>
    static inline T DeSerialize(byte bytes[], int startIndex);

    template<typename T>
    void SerializeValue(T *val, ByteVector &bytes);


public:
    unique_ptr<PacketHeader> header;

    /**
     * Creates a data packet by copying the data supplied in *data to the
     * local data field of the packet using the given length
     * @param data Data to be moved to packet, the data is then invalidated for outsiders
     * @param seq_no Sequence number of the packet
     */
    Packet(unique_ptr<ByteVector> &data, unsigned int seq_no);

    /**
     * Transforms the content of the packet to an array of bytes
     * @return Serialized byte array
     */
    unique_ptr<ByteVector> Serialize();

    /**
     * Returns the data stored in a packet
     * @return Byte data in the packet
     */
    bool GetData(unique_ptr<ByteVector> &output);

    /**
     * Creates a packet instance from given raw data
     * @param serializedPacket Raw packet in a byte array
     * @param arrayLength Length of the byte array
     * @return A unique pointer to the newly created packet
     */
    static unique_ptr<Packet> Create(byte serializedPacket[], unsigned short arrayLength);


    ~Packet();

    /**
     * Move constructor, deleted as this is an immutable type
     * @param source Source Packet location
     */
    Packet(Packet &&source) = delete;

    /**
     * Move assignment operator, deleted as this is an immutable type
     * @param source Source Packet location
     */
    Packet &operator=(Packet &&other)= delete;

    /**
     * The copy constructor isn't needed, this is an immutable object
     * @param source
     */
    Packet(Packet &source) = delete;

    /**
     * The copy assignment operator isn't needed, this is an immutable object
     * @param source
     */
    Packet &operator=(Packet &other)= delete;

};

template<typename T>
inline T Packet::DeSerialize(byte bytes[], int startIndex)
{
    // put a static field to remember the last start index ? -more readability-
    T result = 0;
    T *resultPtr = &result;
    int length = sizeof(T);

    for (int j = 0; j < length; ++j) {
        auto temp = bytes[startIndex + j];
        ((byte *) resultPtr)[j] = temp;
    }

    return result;
}

template<typename T>
void Packet::SerializeValue(T *val, ByteVector &bytes)
{
    for (int i = 0; i < sizeof(T); ++i) {
        byte temp = ((byte *) (val))[i];
        bytes.push_back(temp);
    }
}


#endif //ENHANCEDUDPLIB_PACKET_H
