#include "card.h"
#include <string>
#include <map>
#include <iostream>

using namespace std;

Card::Card(Suit s, Rank r) : suit{s}, rank{r} {}

Card::Card(std::string str) {
	map<std::string, int> r = {{"A", 1}, {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, 
				   {"8", 8}, {"9", 9}, {"T", 10}, {"J", 11}, {"Q", 12}, {"K", 13}};
	map<std::string, int> s = {{"C", 0}, {"D", 1}, {"H", 2}, {"S", 3}};
	std::string suitIndex = string{ str[1] };
	std::string  rankIndex = string{ str[0] };
	suit = static_cast<Suit>(s.at(suitIndex));
	rank = static_cast<Rank>(r.at(rankIndex) - 1 );
}

Suit Card::getSuit() const {
	return suit;
}

Rank Card::getRank() const {
	return rank;
}

string Card::getInfo() const {
	string suits[SUIT_MAX] = {"C", "D", "H", "S"};
	string ranks[RANK_MAX] = {"A", "2", "3", "4", "5", "6",
		"7", "8", "9", "T", "J", "Q", "K"};
	string str = string{ranks[rank] + suits[suit]};
	return str;	
}

bool Card::operator==(const Card & other) {
	return suit == other.getSuit() && rank == other.getRank();
}

std::ostream &operator<<(ostream & out, const Card & c) {
	out << c.getInfo();
	return out;
}
