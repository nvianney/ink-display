#ifndef screen_h
#define screen_h

#include <Arduino.h>
#include <renderer.h>

class Screen {

    bool dirty = true;

protected:
    const int width;
    const int height;

public:
    Screen(int width, int height);

    virtual String getTitle() = 0;

    virtual void show();
    virtual void update(float delta) = 0;
    virtual void draw(Renderer *renderer) = 0;
    virtual void hide();

    void setDirty();
    void clearDirty();
    bool isDirty();
};

#endif
