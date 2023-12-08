#ifndef DAY07_HAND_H
#define DAY07_HAND_H

#include "BaseHand.h"

static const char* CARDS = "23456789:;<=>";

class Hand : public BaseHand {
    void classify() override;
public:
    Hand();
    friend std::ostream& operator<<(std::ostream& lhs, Hand& rhs);
    friend std::istream& operator>>(std::istream& lhs, Hand& rhs);
};


#endif //DAY07_HAND_H
