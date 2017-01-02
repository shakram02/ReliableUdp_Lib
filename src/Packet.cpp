//
// Created by ahmed on 12/24/16.
//


#include "Packet.h"

using namespace Networking;

Packet::Packet()
{}

Packet::Packet(std::vector<byte> &data_bytes, unsigned short data_len, unsigned int seq_no)
{
    if (data_len > DATA_FRAGMENT_SIZE) {
        throw std::invalid_argument("Data length is bigger than the packet pckt_data field");
    }

    std::cout << "String length:" << data_len << std::endl;

    this->chksum = 24930;
    this->seqno = 23;
    this->len = data_len;
    this->data = unique_ptr<byte>(new byte[data_len]());
    memset(reinterpret_cast<void *>(this->data.get()), 0, data_len);
    memcpy(this->data.get(), data_bytes.data(), data_len);

    for (int i = 0; i < data_len; ++i) {
        (this->data.get())[i] = data_bytes[i];
    }

}

Packet::Packet(Packet &&other)
{
    this->chksum = other.chksum;
    this->seqno = other.seqno;
    this->len = other.len;
    this->data = std::move(other.data);

    other.data = nullptr;
    other.chksum = 0;
    other.seqno = 0;
    other.len = 0;
}

Packet &Packet::operator=(Packet &&other)
{
    Packet(std::move(other));
    return *this;
}

unique_ptr<std::deque<byte>> Packet::Serialize()
{
    // Put the binary representation of each field and the content
    // of the data pointer into the char[]

    std::deque<byte> *buffer = new std::deque<byte>();
    Serialize(this->len, buffer);
    Serialize(this->seqno, buffer);

    const byte *traverser = this->data.get();

    for (int i = 0; i < this->len; ++i) {
        buffer->push_back(traverser[i]);
    }
    return unique_ptr<std::deque<byte>>(buffer);
}

unique_ptr<Packet> Deserialize(std::deque<byte> bytes)
{

}

void Packet::Serialize(unsigned short data, std::deque<byte> *bytes)
{
    // Use hton() here, to make it compatible across processors
    byte *projected = reinterpret_cast<byte *>(&data);
    for (int i = 0; i < sizeof(short); ++i) {
        bytes->push_back(projected[i]);
    }
}

void Packet::Serialize(unsigned int data, std::deque<byte> *bytes)
{
    // Use hton() here, to make it compatible across processors
    byte *projected = reinterpret_cast<byte *>(&data);
    for (int i = 0; i < sizeof(int); ++i) {
        bytes->push_back(projected[i]);
    }
}

/// TODO Add template specialization for data
unique_ptr<std::vector<byte>> Packet::DeSerializeData(std::deque<byte> *bytes, unsigned short length)
{
    std::cout << "Length:" << length << std::endl;

    // TODO do sanity checks on length?, use the remaining bytes in the deque anyway ?
    std::vector<byte> *result = new std::vector<byte>();
    result->reserve(length);

    for (int i = 0; i < length; ++i) {

        // TODO memory leak ?
        auto byte_d = DeSerialize<byte>(bytes).release();
        result->push_back(*byte_d);
    }
    return unique_ptr<std::vector<byte>>(result);
}

template<typename T>
unique_ptr<T> Packet::DeSerialize(std::deque<byte> *bytes)
{
    T *result = new T();

    for (int i = 0; i < sizeof(T); ++i) {

        ((byte *) result)[i] = bytes->front();

        bytes->pop_front();
    }

    return unique_ptr<T>(result);
}
