#include "screen_manager.h"

#include <Arduino.h>

void ScreenManager::add(Screen *screen) {
    if (screens.size() == 0) {
        screen->show();
    }

    screens.push_back(screen);
}

Screen *ScreenManager::get() const {
    if (screens.size() == 0) {
        Serial.println("ScreenManager not initialized");
        return nullptr;
    }

    return screens.at(index);
}
