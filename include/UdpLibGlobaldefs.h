//
// Created by ahmed on 12/25/16.
//

#ifndef UDPSOCKETLIB_GLOBALDEFS_H
#define UDPSOCKETLIB_GLOBALDEFS_H

// TODO remove this after testing that it can be unbound
// IMPORTANT the total size of the class can't exceed 256 bytes
// Don't allocate so much memory, stack memory runs out
#define DATA_FRAGMENT_SIZE 128
#define UDP_MTU 256


#define PCKT_SLEEP 500

#include <vector>
#include <memory>
typedef unsigned char byte;
typedef std::vector<byte> ByteVector;

#endif //UDPSOCKETLIB_GLOBALDEFS_H
