//
// Created by ahmed on 1/11/17.
//

#ifndef UDPSOCKETLIB_RAWSOCKET_H
#define UDPSOCKETLIB_RAWSOCKET_H

#include <arpa/inet.h>
#include <string>
#include <vector>
#include <memory>
#include "AddressInfo.h"
#include "Packet.h"

using std::string;

class RawUdpSocket
{
public:

    RawUdpSocket(AddressInfo &info);

    void SetReceiveTimeout(int timeout_secs, int timeout_micros);

    void SetSendTimeout(int timeout_secs, int timeout_micros);

    int Receive(AddressInfo &sender_info, void *buff, int buff_length);

    int Receive(void *buff, int buff_length);

    string ReceiveString();

    std::unique_ptr<Packet> ReceivePacket() noexcept (false);   // TODO read more about noexcept

    static bool GetDetailedSocketError(long num_bytes, string &msg);

    void Send(AddressInfo &receiver_info, void *msg, int length);

    void SendString(AddressInfo &receiver_info, string &msg);

    void SendPacket(AddressInfo &receiver_info, std::unique_ptr<Packet> &packet);

    void Bind();

    unsigned short GetPortNumber();

    string GetIpAdress();

    ~RawUdpSocket();

private:
    void LogError(const char *extra_info);

    string socket_ip;
    unsigned int sockaddr_in4_size = sizeof(sockaddr_in); // For IPv4 only
    bool bound = false;
    int socket_fd;
    sockaddr_in socket_info;
};


#endif //UDPSOCKETLIB_RAWSOCKET_H
