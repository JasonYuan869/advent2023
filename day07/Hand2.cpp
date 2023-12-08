#include "Hand2.h"

void Hand2::classify() {
    int counts[13] = {0};
    for (int i = 0; i < 13; i++) {
        char card = CARDS2[i];
        for (int k = 0; k < 5; k++) {
            if (cards.at(k) == card) {
                counts[i]++;
            }
        }
    }

    int pair_count = 0;
    bool triple = false;
    int jokers = counts[0];
    for (int i = 1; i < 13; i++) {
        switch (counts[i]) {
            case 5:
                type = FIVE_OF_A_KIND;
                return;
            case 4:
                type = jokers == 1 ? FIVE_OF_A_KIND : FOUR_OF_A_KIND;
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
                switch (jokers) {
                    case 0:
                        type = THREE_OF_A_KIND;
                        break;
                    case 1:
                        type = FOUR_OF_A_KIND;
                        break;
                    case 2:
                        type = FIVE_OF_A_KIND;
                        break;
                }
            } else {
                switch (jokers) {
                    case 0:
                        type = HIGH_CARD;
                        break;
                    case 1:
                        type = ONE_PAIR;
                        break;
                    case 2:
                        type = THREE_OF_A_KIND;
                        break;
                    case 3:
                        type = FOUR_OF_A_KIND;
                        break;
                    case 4:
                    case 5:
                        type = FIVE_OF_A_KIND;
                        break;
                }
            }
            break;
        case 1:
            if (triple) {
                type = FULL_HOUSE;
            } else {
                switch (jokers) {
                    case 0:
                        type = ONE_PAIR;
                        break;
                    case 1:
                        type = THREE_OF_A_KIND;
                        break;
                    case 2:
                        type = FOUR_OF_A_KIND;
                        break;
                    case 3:
                        type = FIVE_OF_A_KIND;
                        break;
                }
            }
            break;
        case 2:
            switch (jokers) {
                case 0:
                    type = TWO_PAIR;
                    break;
                case 1:
                    type = FULL_HOUSE;
                    break;
            }
            break;
    }
}

void Hand2::init() {
    classify();
}

Hand2::Hand2(Hand& other) : BaseHand{other.cards, other.bet} {
    for (int i = 0; i < 5; i++) {
        if (this->cards.at(i) == ';') {
            this->cards.replace(i, 1, 1, '1');
        }
    }

    init();
}

std::ostream& operator<<(std::ostream& lhs, Hand2& rhs) {
    return lhs << rhs.cards << " " << rhs.type << " " << rhs.bet;
}