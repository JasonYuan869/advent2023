#ifndef DAY07_BASEHAND_H
#define DAY07_BASEHAND_H

#include <iostream>
#include <string>
#include <algorithm>

#include "Classification.h"

class BaseHand {
protected:
    virtual void classify() = 0;

public:
    std::string cards;
    Classification type;
    int bet;

    BaseHand(std::string, int);
    const bool operator<(const BaseHand& other);
};



#endif //DAY07_BASEHAND_H
