#ifndef _CARD_H_
#define _CARD_H_
#include <string>
#include <iostream>

using namespace std;

enum Suit { CLUB, DIAMOND, HEART, SPADE, SUIT_MAX};
enum Rank { ACE, TWO, THREE, FOUR, FIVE, SIX, SEVEN,
                EIGHT, NINE, TEN, JACK, QUEEN, KING, RANK_MAX};

class Card {
        Suit suit;
        Rank rank;
public:
        Card(Suit s, Rank r);
	Card(std::string str);
        Suit getSuit() const;
        Rank getRank() const;
        string getInfo() const;
        bool operator==(const Card & other);
};

std::ostream &operator<<(ostream & out, const Card & c);

#endif
