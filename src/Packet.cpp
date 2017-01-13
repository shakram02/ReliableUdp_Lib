//
// Created by ahmed on 1/5/17.
//

#include "Packet.h"
#include<iostream>

using std::cout;
using std::endl;
using std::unique_ptr;

Packet::Packet()
{
    this->data = unique_ptr<ByteVector>(new ByteVector());
}

Packet::~Packet()
{}

Packet::Packet(unique_ptr<ByteVector> &data, unsigned int seq_no)
{
    // A reference to a unique_ptr is needed so the pointer can be invalidated


    unsigned short checksum = 24930;   // Special value

    if (data != nullptr) {
        if (data->size() > DATA_FRAGMENT_SIZE) {
            throw std::invalid_argument("Data length is bigger than the packet pckt_data field");
        }
        this->header = unique_ptr<PacketHeader>(new PacketHeader(seq_no,
                (unsigned short) data->size(), checksum));

        this->data = (std::move(data));
    } else {

        // ACK packet
        this->data = nullptr;
        this->header = unique_ptr<PacketHeader>(new PacketHeader(seq_no, 0, checksum));
    }

    data.reset(nullptr);
}

unique_ptr<ByteVector> Packet::Serialize()
{
    // Reserve the size of the whole packet
    ByteVector *buffer = new ByteVector();
    buffer->reserve((unsigned long) (this->header->dataLen + header->Size()));

    unique_ptr<ByteVector> serializedHeader = this->header->Serialize();

    buffer->insert(buffer->begin(), serializedHeader->begin(), serializedHeader->end());
    if (data) {
        buffer->insert(buffer->end(), this->data->begin(), this->data->end());
    }

    return unique_ptr<ByteVector>(buffer);
}

// TODO Add template specialization for data ( data bytes in packet )
unique_ptr<Packet> Packet::Create(byte serializedPacket[], unsigned short arrayLength)
{
    if (arrayLength < PacketHeader::Size()) {
        throw std::invalid_argument("Length of raw packet is less than the minimal size");
    }

    Packet *p = new Packet();

    p->header = PacketHeader::Deserialize(serializedPacket);

    // ACK Packet, nothing to be done
    int dataStartIndex = PacketHeader::Size();

    if (arrayLength == dataStartIndex) return unique_ptr<Packet>(p);


    if (p->header->dataLen != (arrayLength - dataStartIndex)) {
        // Sanity check, will surely prove useful sometime later
        throw std::runtime_error(
                "packet length or content is corrupted,packet -extracted- len:" +
                std::to_string(p->header->dataLen)
                + " , actual length:" + std::to_string((arrayLength - dataStartIndex)));
    }


    p->data->reserve(p->header->dataLen);  // Prevent the vector from re-allocating memory

    for (int i = dataStartIndex; i < arrayLength; ++i) {

        // Deserialize the byte from the binary data
        byte b = DeSerialize<byte>(serializedPacket, i);
        p->data->push_back(b);
    }

    return unique_ptr<Packet>(p);
}

bool Packet::GetData(unique_ptr<ByteVector> &output)
{
    if (header->dataLen != 0) {
        output.reset(data.release());
        return true;
    }
    return false;

}

//Packet::Packet(Packet &&other)
//{
////    this->header->chksum = other.header->chksum;
////    this->header->dataLen = other.header->dataLen;
////    this->header->seqno = other.header->seqno;
////
////    this->data = std::move(other.data);
////
////    other.data.reset();
//    *this = std::move(other);
//}

Packet &Packet::operator=(Packet &&other)
{
    this->header->chksum = other.header->chksum;
    this->header->dataLen = other.header->dataLen;
    this->header->seqno = other.header->seqno;

    this->data = std::move(other.data);

    other.data.reset();

    return *this;
}