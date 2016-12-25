//
// Created by ahmed on 12/24/16.
//

#ifndef ENHANCEDUDPCLIENT_ACKPACKET_H
#define ENHANCEDUDPCLIENT_ACKPACKET_H


class AckPacket
{
public:
    unsigned ack_num;
    unsigned short chksum;
    unsigned short len;

    AckPacket()
    {}

    AckPacket(unsigned int acknum);
};


#endif //ENHANCEDUDPCLIENT_ACKPACKET_H
