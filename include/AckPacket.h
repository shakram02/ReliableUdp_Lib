//
// Created by ahmed on 12/24/16.
//

#ifndef ENHANCEDUDPCLIENT_ACKPACKET_H
#define ENHANCEDUDPCLIENT_ACKPACKET_H


class AckPacket
{
    AckPacket();

public:
    unsigned short cksum;
    unsigned short len;
    unsigned ackno;

    static AckPacket Create(unsigned int ackno);


};


#endif //ENHANCEDUDPCLIENT_ACKPACKET_H
