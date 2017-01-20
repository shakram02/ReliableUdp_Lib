//
// Created by ahmed on 1/19/17.
//

#include "GbnWindow.h"

GbnWindow::GbnWindow(int frag_count, int window_size) : Window(frag_count, window_size)
{
    if (window_size > frag_count) {
        throw std::runtime_error("Window size can't be larger than fragment count");
    }

    for (int i = 0; i < window_size; ++i) {
        this->current_window.push(i);    // Push the first window to the queue
    }
}

bool GbnWindow::Receive(int seqno)
{

    // GBN cumulative ACK
    if (this->current_window.back() == seqno || max_acked_seqid < window_size) {
        return SlideWindow();
    } else {
        return false;
    }
}

bool GbnWindow::SlideWindow()
{
    this->current_window.pop();

    if (max_acked_seqid + 1 <= max_seq_id) {
        max_acked_seqid++;  // Move window base

        // Don't push more than frag count
        this->current_window.push(max_acked_seqid + 1); // Push the next ack to receive
        return true;
    } else {
        // End of packets
        return false;
    }
}

bool GbnWindow::IsDone()
{
    return max_acked_seqid == max_seq_id;
}
