#ifndef _DECK_H_
#define _DECK_H_

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <memory>

#include "card.h"

class Deck {
	unsigned int seed;	
 	std::vector<std::shared_ptr<Card>> cards;
	void createCards();
 public:
	Deck(unsigned int seed = 0);
	Deck(unsigned int seed, std::vector<std::shared_ptr<Card>> cards);
	void shuffleCards();
	void dealCards();
	unsigned int getDeckSize() const;
	std::shared_ptr<Card> getCard(int index);
	std::string getInfo() const;
	unsigned int getSeed() const;
};

std::ostream &operator<<(ostream & out, const Deck & d);

#endif
