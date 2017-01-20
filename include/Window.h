//
// Created by ahmed on 1/19/17.
//

#ifndef UDPSOCKETLIB_SENDWINDOW_H
#define UDPSOCKETLIB_SENDWINDOW_H

#include <queue>


class Window
{

protected:
    // Any id is one less than a cound
    Window(int frag_count, int window_size) : max_seq_id(frag_count - 1), window_size(window_size)
    {};

    virtual bool Receive(int seqno)=0;

    virtual bool SlideWindow()=0;

    virtual bool IsDone()=0;

    std::queue<int> current_window;
    int max_seq_id;
    int window_size;
    int max_acked_seqid = -1;
};


#endif //UDPSOCKETLIB_SENDWINDOW_H
