#include "screen.h"

Screen::Screen(int width, int height) : width(width), height(height) {
}

void Screen::show() {
    setDirty();
}

void Screen::hide() {
}

void Screen::setDirty() {
    dirty = true;
}

void Screen::clearDirty() {
    dirty = false;
}

bool Screen::isDirty() {
    return dirty;
}
