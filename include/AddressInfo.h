//
// Created by ahmed on 1/11/17.
//

#ifndef UDPSOCKETLIB_CLIENTINFO_H
#define UDPSOCKETLIB_CLIENTINFO_H

#include <string>

struct AddressInfo
{
    std::string ip;
    unsigned short port_number;

    inline AddressInfo();

    inline AddressInfo(std::string ip, unsigned short port_number);


};

AddressInfo::AddressInfo(std::string ip, unsigned short port_number)
{
    this->ip = ip;
    this->port_number = port_number;
}

AddressInfo::AddressInfo()
{}


#endif //UDPSOCKETLIB_CLIENTINFO_H
