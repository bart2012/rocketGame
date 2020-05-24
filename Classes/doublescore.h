#ifndef DOUBLESCORE_H
#define DOUBLESCORE_H
#include "booster.h"

class DoubleScore : public Booster
{
public:
    DoubleScore(void *gameScene);
    void start();
    ~DoubleScore();
};

#endif // DOUBLESCORE_H
