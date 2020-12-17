#ifndef _TABLE_H_
#define _TABLE_H_

#include <algorithm>
#include <memory>
#include <vector>
#include <string>

#include "card.h"

class Table {
	std::shared_ptr<Card> lastCard;
	std::vector<std::vector<std::shared_ptr<Card>>> curCards;
public:
	Table();
	void initialize();
	void addCard(std::shared_ptr<Card> c);
	void clearTable();
	bool checkLegalMove(std::shared_ptr<Card> c) const;
	std::string getInfo() const;
	void setCurCard(std::shared_ptr<Card> c);
	std::shared_ptr<Card> getLastCard();
};

#endif
