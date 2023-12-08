#include "Hand.h"

Hand::Hand() : BaseHand{"", 0} {}

void Hand::classify() {
    int counts[13] = {0};
    for (int i = 0; i < 13; i++) {
        char card = CARDS[i];
        for (int k = 0; k < 5; k++) {
            if (cards.at(k) == card) {
                counts[i]++;
            }
        }
    }

    int pair_count = 0;
    bool triple = false;
    for (int i = 0; i < 13; i++) {
        switch (counts[i]) {
            case 5:
                type = FIVE_OF_A_KIND;
                return;
            case 4:
                type = FOUR_OF_A_KIND;
                return;
            case 3:
                triple = true;
                break;
            case 2:
                pair_count++;
                break;
        }
    }

    switch (pair_count) {
        case 0:
            if (triple) {
                type = THREE_OF_A_KIND;
            } else {
                type = HIGH_CARD;
            }
            break;
        case 1:
            if (triple) {
                type = FULL_HOUSE;
            } else {
                type = ONE_PAIR;
            }
            break;
        case 2:
            type = TWO_PAIR;
            break;
    }
}

std::istream& operator>>(std::istream& lhs, Hand& rhs) {
    std::string items;
    lhs >> items;
    if (items.size() != 5) {
        lhs.setstate(std::ios_base::failbit);
        return lhs;
    }

    rhs.cards.clear();

    for (int i = 0; i < 5; i++) {
        char c;
        switch (items.at(i)) {
            case 'T':
                c = ':';
                break;
            case 'J':
                c = ';';
                break;
            case 'Q':
                c = '<';
                break;
            case 'K':
                c = '=';
                break;
            case 'A':
                c = '>';
                break;
            default:
                c = items[i];
                break;
        }
        rhs.cards.push_back(c);
    }

    rhs.classify();

    lhs >> rhs.bet;

    return lhs;
}

std::ostream& operator<<(std::ostream& lhs, Hand& rhs) {
    return lhs << rhs.cards << " " << rhs.type << " " << rhs.bet;
}