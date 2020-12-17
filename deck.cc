#include "deck.h"

using namespace std;

Deck::Deck(unsigned int seed): seed{seed} {
	createCards();
}

Deck::Deck(unsigned int seed, std::vector<std::shared_ptr<Card>> cards) : seed{seed}, cards{cards} {}

void Deck::createCards() {
	for (int i = 0; i < SUIT_MAX; ++i) {
		for (int j = 0; j < RANK_MAX; ++j) {
			cards.emplace_back(make_shared<Card>(Suit(i),Rank(j)));
		}
	}
}

void Deck::shuffleCards() {
	if (seed == 0) {
		seed = std::chrono::system_clock::now().time_since_epoch().count();
	}
	std::default_random_engine rng{seed};
	for (int i = 0; i < 1000; i++) {
        	std::shuffle(cards.begin(), cards.end(), rng);
        }
}

std::shared_ptr<Card> Deck::getCard(int index) {
	Suit s = cards[index]->getSuit();
	Rank r = cards[index]->getRank();
	std::shared_ptr<Card> c = std::make_shared<Card>(s, r);
	return c;
}

unsigned int Deck::getDeckSize() const {
	return cards.size();
}

std::string Deck::getInfo() const{
	int count = 0;
	string str = "";
        for ( auto c : cards ) {
                if (count % 13 == 0 && count != 0) {
                        str += "\n";
                }
		str+= c->getInfo() + " ";
		count++;
	}
	return str;
}

unsigned int Deck::getSeed() const {
	return seed;
}

std::ostream &operator<<(ostream & out, const Deck & d) {
	out << d.getInfo();
 	return out; 
}	
