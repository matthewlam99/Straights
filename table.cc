#include "table.h"

Table::Table(): lastCard{std::make_shared<Card>(Suit::SPADE, Rank::SEVEN)} {
	initialize();
}

// Helper function to sort the cards on the table in order
bool sortHelper(std::shared_ptr<Card> lhs, std::shared_ptr<Card> rhs) {
	return lhs->getRank() < rhs->getRank();
}

// Updates the top card on the table and updates the list of cards in the pile.
void Table::addCard(std::shared_ptr<Card> c) {
	int suitIndex = static_cast<int>(c->getSuit());
	curCards[suitIndex].emplace_back(c);
	std::sort(curCards[suitIndex].begin(), curCards[suitIndex].end(), sortHelper);
	lastCard = c;
}

void Table::initialize() {
	// Index 0 is for Clubs, 1 for Diamonds, 2 for Hearts, 3 for Spades following enums
	curCards.emplace_back(std::vector<std::shared_ptr<Card>>());
	curCards.emplace_back(std::vector<std::shared_ptr<Card>>());
	curCards.emplace_back(std::vector<std::shared_ptr<Card>>());
	curCards.emplace_back(std::vector<std::shared_ptr<Card>>());
}

// Clears the table of the old card and sets it up for the next round.
void Table::clearTable() {
	curCards.clear();
	lastCard = std::make_shared<Card>(Suit::SPADE, Rank::SEVEN);
	initialize(); 
}

bool Table::checkLegalMove(std::shared_ptr<Card> c) const {
	Suit s = c->getSuit();
	Rank r = c->getRank();

	if (r == SEVEN) {
		return true;
	}

	for (unsigned int i = 0; i < curCards[s].size(); ++i) {
		if (r + 1 == curCards[s][i]->getRank() ||  r - 1 == curCards[s][i]->getRank()) {
			return true;
		}	
	}
	return false;
}
std::string Table::getInfo() const {
	string str = "Cards on the table:\n";
	string suits[SUIT_MAX] = {"Clubs", "Diamonds", "Hearts", "Spades"};
	string ranks[RANK_MAX] = {"A", "2", "3", "4", "5", "6",
                "7", "8", "9", "T", "J", "Q", "K"};
	for (unsigned int i = 0; i < curCards.size(); ++i) {
		str += suits[i] + ": ";
	        for (unsigned int j = 0; j < curCards[i].size(); ++j) {
			str += ranks[curCards[i][j]->getRank()] + " ";
		}	
		str += "\n";
	}	
	return str;
}

void Table::setCurCard(std::shared_ptr<Card> c) {
	lastCard = c;
}

std::shared_ptr<Card> Table::getLastCard() {
	return lastCard;
}
