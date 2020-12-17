#include "player.h"

Player::Player(int playerNum, int score): playerNum{playerNum}, score{score} {}

Player::Player(int playerNum, int score, std::vector<std::shared_ptr<Card>> hand,
               std::vector<std::shared_ptr<Card>> allLegalPlays, std::vector<std::shared_ptr<Card>> discards)
	       : playerNum{playerNum}, score{score}, hand{hand}, allLegalPlays{allLegalPlays},
	         discards{discards} {}

Player::~Player() {}

int Player::getScore() const {
        return score;
}

void Player::setScore(int s) {
	score = s;
}

int Player::getPlayerNum() const {
        return playerNum;
}

bool Player::has7S() const {
        for (unsigned int i = 0; i < hand.size(); ++i) {
                if (hand[i]->getSuit() == SPADE && hand[i]->getRank() == SEVEN) {
                        return true;
                }
        }
        return false;
}

// Clears all cards data on the player
void Player::clearCards() {
        discards.clear();
        hand.clear();
        allLegalPlays.clear();
}

// Functions for the Hand
void Player::addHandCard(std::shared_ptr<Card> c) {
	hand.push_back(c);	
}

void Player::removeHandCard(int index) {
	hand.erase(hand.begin() + index);
}

std::shared_ptr<Card> Player::findHandCard(int index) {
        return hand[index];
}

std::vector<std::shared_ptr<Card>> Player::getHand() {
	return hand;
}

int Player::getHandCardIndex(std::string s) const {
	for (unsigned int i = 0; i < hand.size(); ++i) {
		if (s == hand[i]->getInfo()) {
			return i;
		}
	}
	return -1;
}

bool Player::emptyHand() const {
        return hand.size() == 0;
}

std::string Player::getHandInfo() const {
	std::string str = "Your hand: ";
	for (unsigned int i = 0; i < hand.size(); ++i) {
                str += hand[i]->getInfo() + " ";
        }
	return str;	
}

// Functions for Legal Plays
void Player::findAllLegalPlays(std::shared_ptr<Table> & table) {
	// Clear previous allLegalPlays
	allLegalPlays.clear();

	// Determines current allLegalPlays
	for (unsigned int i = 0; i < hand.size(); ++i) {
		if (table->checkLegalMove(hand[i])) {
			allLegalPlays.emplace_back(hand[i]);
		}
	}
}

std::shared_ptr<Card> Player::findLegalCard(int index) {
        return allLegalPlays[index];
}

std::vector<std::shared_ptr<Card>> Player::getAllLegalPlays() {
	return allLegalPlays;
}

int Player::getAllLegalPlaysIndex(std::string s) const {
        for (unsigned int i = 0; i < allLegalPlays.size(); ++i) {
                if (s == allLegalPlays[i]->getInfo()) {
                        return i;
                }
        }
        return -1;
}

std::string Player::getLegalInfo() const{
        std::string str = "Legal plays: ";
        for (unsigned int i = 0; i < allLegalPlays.size(); ++i) {
                str += allLegalPlays[i]->getInfo() + " ";
        }
        return str;
}

bool Player::noLegalPlays() const {
        return allLegalPlays.size() == 0;
}

// Functions for Discards
void Player::addDiscard(std::shared_ptr<Card> c) {
        discards.push_back(c);
}

std::vector<std::shared_ptr<Card>> Player::getDiscards() {
	return discards;
}

// For testing only
int Player::getDiscardIndex(std::string s) const {
        for (unsigned int i = 0; i < discards.size(); ++i) {
                if (s == discards[i]->getInfo()) {
                        return i;
                }
        }
        return -1;
}

int Player::sumDiscard() const {
        int roundScore = 0;
        for (unsigned int i = 0; i < discards.size(); ++i) {
                roundScore += static_cast<int>(discards[i]->getRank()) + 1;
        }
        return roundScore;
}

std::string Player::getDiscardInfo() const {
        std::string str = "Player" + to_string(playerNum) + "’s discards: ";
        for (unsigned int i = 0; i < discards.size(); ++i) {
                str += discards[i]->getInfo() + " ";
        }
        return str;
}
