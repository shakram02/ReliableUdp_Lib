//
// Created by ahmed on 1/19/17.
//

#ifndef UDPSOCKETLIB_GBNWINDOW_H
#define UDPSOCKETLIB_GBNWINDOW_H

#include "Window.h"
#include <stdexcept>

class GbnWindow : virtual protected Window
{
    bool SlideWindow() override;

public:
    GbnWindow(int frag_count, int window_size);

    bool Receive(int seqno) override;

    bool IsDone() override;
};


#endif //UDPSOCKETLIB_GBNWINDOW_H
