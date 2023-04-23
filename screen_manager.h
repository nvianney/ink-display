#ifndef screen_manager_h
#define screen_manager_h

#include <vector>
#include "screen.h"

class ScreenManager {

    std::vector<Screen*> screens;
    int index = 0;

public:
    void add(Screen *screen);

    Screen *get() const;

};

#endif
