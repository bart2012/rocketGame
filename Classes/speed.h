#ifndef SPEED_H
#define SPEED_H
#include "booster.h"

class SpeedUp : public Booster
{
public:
    SpeedUp(void *gameScene);
    void start();
    ~SpeedUp();
};

#endif // SPEED_H
