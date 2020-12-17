#ifndef _PLAYER_H_
#define _PLAYER_H_

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "card.h"
#include "table.h"

class Player {
	int playerNum;
	int score;
        std::vector<std::shared_ptr<Card>> hand;
	std::vector<std::shared_ptr<Card>> allLegalPlays;
	std::vector<std::shared_ptr<Card>> discards;
public:
	Player(int playerNum, int score = 0); 
	Player(int playerNum, int score, std::vector<std::shared_ptr<Card>> hand,
	       std::vector<std::shared_ptr<Card>> allLegalPlays, std::vector<std::shared_ptr<Card>> discards);
	virtual ~Player() = 0;
	virtual std::shared_ptr<Card> play(std::string s = "") = 0; 
	virtual void discard(std::string s = "") = 0;

        int getPlayerNum() const;
	void setScore(int s);
        int getScore() const;;
        bool has7S() const;
	void clearCards();

	// Methods for Hand Cards
	void addHandCard(std::shared_ptr<Card> c);
	void removeHandCard(int index);
	std::shared_ptr<Card> findHandCard(int index);
	std::vector<std::shared_ptr<Card>> getHand();
	int getHandCardIndex(std::string s) const;
	std::string getHandInfo() const;
	bool emptyHand() const;

	// Methods for Legal Plays
	void findAllLegalPlays(std::shared_ptr<Table> & table);
	std::shared_ptr<Card> findLegalCard(int index);
	std::vector<std::shared_ptr<Card>> getAllLegalPlays();
	int getAllLegalPlaysIndex(std::string s) const;
	std::string getLegalInfo() const;
	bool noLegalPlays() const;

	// Methods for Discards
	void addDiscard(std::shared_ptr<Card> c);
	std::vector<std::shared_ptr<Card>> getDiscards();	
	int getDiscardIndex(std::string s) const;
	int sumDiscard() const;	
	std::string getDiscardInfo() const;
};

#endif
