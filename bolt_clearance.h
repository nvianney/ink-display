#ifndef bolt_clearance_h
#define bolt_clearance_h

#include <renderer.h>
#include <table.h>

#include "screen.h"

class BoltClearance : public Screen {

    TableProperties itProperties;
    Table *imperialTable;
    TableProperties mtProperties;
    Table *metricTable;

public:
    BoltClearance(int width, int height);
    ~BoltClearance();

    virtual String getTitle() override;

    virtual void update(float delta) override;
    virtual void draw(Renderer *renderer) override;
};

#endif
