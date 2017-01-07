//
// Created by ahmed on 12/24/16.
//

#ifndef ENHANCEDUDPCLIENT_ACKPACKET_H
#define ENHANCEDUDPCLIENT_ACKPACKET_H

#include "UdpLibGlobaldefs.h"
#include <memory>

using std::unique_ptr;

class PacketHeader
{


public:
    /**
     * Checksum for all the other fields in the packet
     */
    unsigned short chksum;

    /**
     * Sequence number of the packet
     */
    unsigned int seqno;

    /**
     * Length of data inside the data field
     */
    unsigned short dataLen;

    PacketHeader();

    ~PacketHeader();

    PacketHeader(unsigned int ackNum, unsigned short dataLen, unsigned short dataChecksum);

    /**
     * Deserializes the raw array of bytes to a PacketHeader
     * @param serializedPacket Raw data
     * @return Pointer to the newly created header
     */
    static unique_ptr<PacketHeader> Deserialize(byte serializedPacket[]);

    /**
     * Convert this instance to raw byte vector
     * @return A raw representation of this header
     */
    unique_ptr<ByteVector> Serialize();

    static int Size();

private:
    template<typename T>
    static inline T DeSerializeValue(byte bytes[], int startIndex);

    template<typename T>
    void SerializeValue(T *val, ByteVector &bytes);
};

template<typename T>
void PacketHeader::SerializeValue(T *val, ByteVector &bytes)
{
    for (int i = 0; i < sizeof(T); ++i) {
        byte temp = ((byte *) (val))[i];
        bytes.push_back(temp);
    }
}


template<typename T>
inline T PacketHeader::DeSerializeValue(byte bytes[], int startIndex)
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


#endif //ENHANCEDUDPCLIENT_ACKPACKET_H
