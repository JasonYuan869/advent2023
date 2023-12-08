#include "BaseHand.h"

BaseHand::BaseHand(std::string cards, int bet) : cards{cards}, type{HIGH_CARD}, bet{bet} {}

const bool BaseHand::operator<(const BaseHand& other) {
    if (this->type > other.type) {
        return true;
    } else if (this->type == other.type) {
        return (this->cards.compare(other.cards) < 0);
    } else {
        return false;
    }
}