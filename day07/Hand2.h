#ifndef DAY07_HAND2_H
#define DAY07_HAND2_H

#include "BaseHand.h"
#include "Hand.h"

static const char* CARDS2 = "123456789:<=>";

class Hand2 : public BaseHand {
    void classify() override;
    void init();

public:
    Hand2(Hand& other);
    friend std::ostream& operator<<(std::ostream& lhs, Hand2& rhs);
};

#endif //DAY07_HAND2_H
