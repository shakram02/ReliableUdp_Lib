//
// Created by ahmed on 1/11/17.
//

#include "RawUdpSocket.h"
#include <unistd.h>
#include <cstring>
#include <chrono>
#include <thread>
#include "UdpLibGlobaldefs.h"

RawUdpSocket::RawUdpSocket(AddressInfo &info)
{
    memset(&socket_info, 0, sizeof(socket_info));

    this->socket_ip = info.ip;  // TODO , IP Address.Any

    this->socket_info.sin_family = AF_INET;  /* Server is in Internet Domain */
    this->socket_info.sin_port = htons(info.port_number);

    if (inet_pton(AF_INET, info.ip.c_str(), &socket_info.sin_addr.s_addr) == -1) {
        LogError("Failed to convert IP address");
    }

    if ((this->socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        LogError("Failed to create socket");
    }



//    unsigned int namelen = sizeof(this->socket_info);
//    if (getsockname(this->socket_fd, (struct sockaddr *) &socket_info, &namelen) < 0) {
//        LogError("Failed to get socket name");
//    }
}

RawUdpSocket::RawUdpSocket(string socket_ip)
{
    memset(&socket_info, 0, sizeof(socket_info));

    this->socket_ip = socket_ip;  // TODO , IP Address.Any

    this->socket_info.sin_family = AF_INET;  /* Server is in Internet Domain */
    this->socket_info.sin_port = 0;

    if (inet_pton(AF_INET, socket_ip.c_str(), &socket_info.sin_addr.s_addr) == -1) {
        LogError("Failed to convert IP address");
    }

    if ((this->socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        LogError("Failed to create socket");
    }
}

void RawUdpSocket::SetReceiveTimeout(int timeout_secs, int timeout_micros)
{
    timeval timeout;
    // Removing memset causes unidentified behaviour as the values are originally garbage
    memset(&timeout, 0, sizeof(timeout));
    timeout.tv_sec = timeout_secs;
    timeout.tv_usec = timeout_micros;

    if (setsockopt(this->socket_fd, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeval)) < 0) {
        LogError("set receive timeout");
    }
}

void RawUdpSocket::SetSendTimeout(int timeout_secs, int timeout_micros)
{
    timeval timeout;
    // Removing memset causes unidentified behaviour as the values are originally garbage
    memset(&timeout, 0, sizeof(timeout));
    timeout.tv_sec = timeout_secs;
    timeout.tv_usec = timeout_micros;

    if (setsockopt(this->socket_fd, SOL_SOCKET, SO_SNDTIMEO, (char *) &timeout, sizeof(timeval)) < 0) {
        // Whatever we're sending might be locked, so a send timeout is set
        LogError("set send timeout");
    }
}


int RawUdpSocket::Receive(AddressInfo &sender_info, void *buff, int buff_length)
{
    struct sockaddr_in sender;
    unsigned int sender_addr_size = sizeof(sender);

    int received_size =
            (int) recvfrom(this->socket_fd,
                    (buff),
                    (size_t) buff_length, 0,
                    (struct sockaddr *) &sender,
                    &sender_addr_size);
    // Fill sender AddressInfo
    sender_info.ip = inet_ntoa(sender.sin_addr);
    sender_info.port_number = ntohs(sender.sin_port);

    return received_size;
}

int RawUdpSocket::Receive(void *buff, int buff_length)
{
    AddressInfo dummy;
    return Receive(dummy, buff, buff_length);
}

void RawUdpSocket::LogError(const char *extra_info)
{
    string error(extra_info);
    error = error.append(strerror(errno));

    if (errno == 0)return;  // Do nothing if the operation succeeded

    throw std::runtime_error(error);
}

void RawUdpSocket::Send(AddressInfo &receiver_info, void *msg, int length)
{
    sockaddr_in receiver;
    memset(&receiver, 0, sizeof(receiver));

    receiver.sin_family = AF_INET;  /* Server is in Internet Domain */
    receiver.sin_port = htons(receiver_info.port_number);
    inet_pton(AF_INET, receiver_info.ip.c_str(), &receiver.sin_addr.s_addr);

    sendto(this->socket_fd, msg, (size_t) length, 0,
            (struct sockaddr *) &receiver, sockaddr_in4_size);
}

string RawUdpSocket::GetIpAdress()
{
    return string(inet_ntoa(socket_info.sin_addr));
}

unsigned short RawUdpSocket::GetPortNumber()
{
    return ntohs(socket_info.sin_port);
}

void RawUdpSocket::UpdateSocketInfo()
{
    // Updates the socket info in the "socket_info" object by calling getsockname,
    // this function must be called after binding to the address, otherwise it corrupts
    // the previously stored socket info
    unsigned int namelen = sizeof((this->socket_info));
    if (getsockname(this->socket_fd, (struct sockaddr *) &(this->socket_info), &namelen) < 0) {
        LogError("Can't update info ");
    }

}

void RawUdpSocket::Bind()
{
    int yes = 1;

    if (setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(yes)) == -1) {
        LogError("Failed to set reuse port option ");
    }

    if (bind(this->socket_fd, (struct sockaddr *) &this->socket_info, sizeof(this->socket_info)) < 0) {
        LogError("failed to bind ");
    }

    UpdateSocketInfo(); // After the address is bound, we can get its info
}

bool RawUdpSocket::GetDetailedSocketError(long num_bytes, string &msg)
{
    bool is_err = false;
    if (num_bytes == 0) {
        msg = msg.append("#connection closed");
        is_err = true;
    } else if (num_bytes == -1) {
        msg = msg.append("# receive err:");
        msg = msg.append(strerror(errno));
        is_err = true;
    }
    return is_err;
}

string RawUdpSocket::ReceiveString()
{
    AddressInfo dummy;
    return ReceiveString(dummy);
}

string RawUdpSocket::ReceiveString(AddressInfo &sender_info)
{
    char buff[UDP_MTU] = {0};
    int count = Receive(sender_info, buff, UDP_MTU);

    string detail("Failed to receive string");
    if (GetDetailedSocketError(count, detail)) {
        throw std::runtime_error(detail);
    }

    return string(buff);
}

void RawUdpSocket::SendString(AddressInfo &receiver_info, string &msg)
{
    Send(receiver_info, (void *) msg.data(), (int) msg.size());
}


bool RawUdpSocket::ReceivePacket(std::unique_ptr<Packet> &packet)
{
    byte *data = (byte *) calloc(1, (size_t) UDP_MTU);

    int size = Receive(data, UDP_MTU);

    string detail("Failed to receive packet");

    if (size < 0 && errno == EAGAIN) {
        return false;   // Timeout
    } else if (GetDetailedSocketError(size, detail)) {
        throw std::runtime_error(detail);
    }
    packet = Packet::Create(data, (unsigned short) size);
    return true;
}

void RawUdpSocket::SendPacket(AddressInfo &receiver_info, unique_ptr<Packet> &packet)
{
    unique_ptr<ByteVector> bytes = packet->Serialize();
    Send(receiver_info, bytes->data(), (int) bytes->size());
}

RawUdpSocket::~RawUdpSocket()
{
    close(this->socket_fd);
}
