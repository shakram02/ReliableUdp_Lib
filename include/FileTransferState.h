//
// Created by ahmed on 1/19/17.
//

#ifndef UDPSOCKETLIB_FILETRANSFERSTATE_H
#define UDPSOCKETLIB_FILETRANSFERSTATE_H

struct FileTransferState
{
    FileTransferState(int last_acked) :
            last_acked_seqid(last_acked)
    {}

    int last_acked_seqid;
};

#endif //UDPSOCKETLIB_FILETRANSFERSTATE_H
