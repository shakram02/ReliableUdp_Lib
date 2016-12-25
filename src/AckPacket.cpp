//
// Created by ahmed on 12/24/16.
//

#include <Checksum.h>
#include "AckPacket.h"


AckPacket::AckPacket(unsigned int acknum)
{
    this->ack_num = acknum;
    this->chksum = 62709;
    this->len = sizeof(acknum) + sizeof(chksum);
}
