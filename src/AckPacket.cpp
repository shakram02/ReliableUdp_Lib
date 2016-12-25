//
// Created by ahmed on 12/24/16.
//

#include "AckPacket.h"


AckPacket::AckPacket(unsigned int acknum)
{
    this->ack_num = acknum;
    this->chksum = 3;
    this->len = sizeof(acknum) + sizeof(chksum);
}
