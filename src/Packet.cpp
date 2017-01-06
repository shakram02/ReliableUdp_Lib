//
// Created by ahmed on 1/5/17.
//

#include "Packet.h"

using std::unique_ptr;

Packet::Packet()
{
    this->data = unique_ptr<ByteVector>(new ByteVector());
}

Packet::~Packet()
{}

Packet::Packet(unique_ptr<ByteVector> &data, unsigned int seq_no)
{
    if (data->size() > DATA_FRAGMENT_SIZE) {
        throw std::invalid_argument("Data length is bigger than the packet pckt_data field");
    }

    this->chksum = 24930;   // Special value
    this->seqno = seq_no;
    this->len = (unsigned short) data->size();
    this->data = (std::move(data));
    data = nullptr;
}

unique_ptr<ByteList> Packet::Serialize()
{
    // Put the binary representation of each field and the content
    // of the data pointer into the char[]

    ByteList *buffer = new ByteList();

    SerializeValue<unsigned short>(&(this->len), *buffer);
    SerializeValue<unsigned short>(&(this->chksum), *buffer);
    SerializeValue<unsigned int>(&(this->seqno), *buffer);

    for (int i = 0; i < this->len; ++i) {
        // TODO move data content to the output list
        buffer->push_back((this->data->operator[](i)));
    }

    return unique_ptr<std::list<byte>>(buffer);
}

// TODO Add template specialization for data ( data bytes in packet )
unique_ptr<Packet> Packet::Create(byte serializedPacket[], unsigned short arrayLength)
{
    if (arrayLength < (sizeof(unsigned short) + sizeof(unsigned int))) {
        throw std::invalid_argument("Length of raw packet is less than the minimal size");
    }

    Packet *p = new Packet();

    // The code is detailed for readability
    unsigned short len = DeSerialize<unsigned short>(serializedPacket, 0);
    unsigned short checksum = DeSerialize<unsigned short>(serializedPacket, sizeof(len));
    unsigned int seqno = DeSerialize<unsigned int>(serializedPacket, sizeof(len) + sizeof(checksum));

    p->len = len;
    p->seqno = seqno;
    p->chksum = checksum;

    int dataStartIndex = sizeof(len) + sizeof(checksum) + sizeof(seqno);

    if (len != (arrayLength - dataStartIndex)) {
        throw std::runtime_error(
                "packet length or content is corrupted,packet -extracted- len:" + std::to_string(len)
                + " , actual length:" + std::to_string((arrayLength - dataStartIndex)));
    }

    p->data->reserve(len);  // Prevent the vector from re-allocating memory

    for (int i = dataStartIndex; i < arrayLength; ++i) {

        // Deserialize the byte from the binary data
        byte b = DeSerialize<byte>(serializedPacket, i);
        p->data->push_back(b);
    }

    return unique_ptr<Packet>(p);
}

const ByteVector Packet::GetData() const
{
    return *data;
}