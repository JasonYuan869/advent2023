#include <iostream>
#include <fstream>
#include <vector>

#include "Hand.h"
#include "Hand2.h"

using namespace std;

int part1(vector<Hand>& hands) {
  int ret = 0;
  for (int i = 0; i < hands.size(); i++) {
    ret += hands[i].bet * (i + 1);
  }
  return ret;
}

int part2(vector<Hand2>& hands) {
  int ret = 0;
  for (int i = 0; i < hands.size(); i++) {
    ret += hands[i].bet * (i + 1);
  }
  return ret;

}

int main(int argc, char* argv[]) {
  if (argc < 2) {
    return -1;
  }

  string path = argv[1];
  fstream input;
  input.open(path, ios::in);
  if (!input) {
    cout << "file not found" << endl;
  }

  vector<Hand> hands;
  Hand hand;
  while (input >> hand) {
    hands.push_back(hand);
  }

  sort(hands.begin(), hands.end());

  cout << part1(hands) << endl;

  vector<Hand2> hands2;
  for (auto& hand : hands) {
    hands2.emplace_back(hand);
  }

  sort(hands2.begin(), hands2.end());

  cout << part2(hands2) << endl;
}
