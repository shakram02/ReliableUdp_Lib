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

    /**
     * Use this constructor when creating a client socket, picks a random port number
     * @param socket_ip IP of the created socket
     */
    RawUdpSocket(string socket_ip);

    void SetReceiveTimeout(int timeout_secs, int timeout_micros);

    void SetSendTimeout(int timeout_secs, int timeout_micros);

    int Receive(AddressInfo &sender_info, void *buff, int buff_length);


    //string ReceiveString();

    //string ReceiveString(AddressInfo &sender_info);
//    void SendString(AddressInfo &receiver_info, string &msg);

    int ReceiveStringPacket(string &str);

    int ReceiveStringPacket(AddressInfo &sender_info, string &str);

    bool ReceivePacket(std::unique_ptr<Packet> &packet);

    bool ReceivePacket(AddressInfo &sender_info, std::unique_ptr<Packet> &packet);

    static bool GetDetailedSocketError(long num_bytes, string &msg);

    void Send(AddressInfo &receiver_info, void *msg, int length);

    void SendStringPacket(AddressInfo &receiver_info, string &msg, int protocol_seqno);

    void SendPacket(AddressInfo &receiver_info, std::unique_ptr<Packet> &packet);

    void Bind();

    unsigned short GetPortNumber();

    string GetIpAdress();

    ~RawUdpSocket();

private:
    void LogError(const char *extra_info);

    int Receive(void *buff, int buff_length);

    void UpdateSocketInfo();

    string socket_ip;
    unsigned int sockaddr_in4_size = sizeof(sockaddr_in); // For IPv4 only
    bool bound = false;
    int socket_fd;
    sockaddr_in socket_info;
};


#endif //UDPSOCKETLIB_RAWSOCKET_H
