//
// Created by ahmed on 12/24/16.
//

#include "PacketHeader.h"

PacketHeader::PacketHeader()
{
    this->chksum = 0;
    this->dataLen = 0;
    this->seqno = 0;

}

PacketHeader::PacketHeader(unsigned int ackNum, unsigned short dataLen, unsigned short dataChecksum)
{
    this->seqno = ackNum;
    this->chksum = (unsigned short) (dataChecksum + 0);   // TODO do the checksum
    this->dataLen = dataLen;
}

unique_ptr<PacketHeader> PacketHeader::Deserialize(byte serializedPacket[])
{
    PacketHeader *p = new PacketHeader();

    // The code is detailed for readability
    p->seqno = DeSerializeValue<unsigned int>(serializedPacket, 0);
    p->chksum = DeSerializeValue<unsigned short>(serializedPacket, sizeof(seqno));
    p->dataLen = DeSerializeValue<unsigned short>(serializedPacket, sizeof(seqno) + sizeof(chksum));

    return unique_ptr<PacketHeader>(p);
}

PacketHeader::~PacketHeader()
{

}

unique_ptr<ByteVector> PacketHeader::Serialize()
{
    ByteVector *raw = new ByteVector();

    // Preallocate all the memory you need
    raw->reserve((unsigned long) this->Size());

    SerializeValue<unsigned int>(&(this->seqno), *raw);
    SerializeValue<unsigned short>((&this->chksum), *raw);
    SerializeValue<unsigned short>(&(this->dataLen), *raw);

    // TODO temporary sanity check
    if (raw->size() != Size()) {
        throw std::invalid_argument("Error while serializing header");
    }

    return unique_ptr<ByteVector>(raw);
}

int PacketHeader::Size()
{
    return sizeof(dataLen) + sizeof(seqno) + sizeof(chksum);
}