#include <iostream>
#include <string>
#include <algorithm>

const char* CARDS = "23456789:;<=>";
const char* CARDS2 = "123456789:<=>";

enum Classification {
  FIVE_OF_A_KIND = 0,
  FOUR_OF_A_KIND,
  FULL_HOUSE,
  THREE_OF_A_KIND,
  TWO_PAIR,
  ONE_PAIR,
  HIGH_CARD
};

class Hand2 {
private:
  std::string cards;
  Classification type;

  void classify() {
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
public:
  int bet;

  // From Hand
  Hand2(std::string cards, int bet) : cards{cards}, type{HIGH_CARD}, bet{bet} {
    for (int i = 0; i < 5; i++) {
      if (this->cards.at(i) == ';') {
        this->cards.replace(i, 1, 1, '1');
      }
    }

    classify();
  }

  const bool operator<(const Hand2& other) {
    if (this->type > other.type) {
      return true;
    } else if (this->type == other.type) {
      return (this->cards.compare(other.cards) < 0);
    } else {
      return false;
    }
  }

  friend std::ostream& operator<<(std::ostream& lhs, Hand2& rhs) {
    return lhs << rhs.cards << " " << rhs.type << " " << rhs.bet;
  }
};

class Hand {
private:
  std::string cards;
  Classification type;
  void classify() {
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

public:
  int bet;

  const bool operator<(const Hand& other) {
    if (this->type > other.type) {
      return true;
    } else if (this->type == other.type) {
      return (this->cards.compare(other.cards) < 0);
    } else {
      return false;
    }
  }

  friend std::istream& operator>>(std::istream& lhs, Hand& rhs) {
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

  friend std::ostream& operator<<(std::ostream& lhs, Hand& rhs) {
    return lhs << rhs.cards << " " << rhs.type << " " << rhs.bet;
  }

  Hand2 intoHand2() {
    return Hand2(cards, bet);
  }
};


