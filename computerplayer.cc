#include "computerplayer.h"

ComputerPlayer::ComputerPlayer(int playerNum): Player{playerNum} {}

ComputerPlayer::ComputerPlayer(int playerNum, int score, std::vector<std::shared_ptr<Card>> hand, 
		std::vector<std::shared_ptr<Card>> allLegalPlays, std::vector<std::shared_ptr<Card>> discards)
		: Player{playerNum, score, hand, allLegalPlays, discards} {}

std::shared_ptr<Card> ComputerPlayer::play(std::string s) {	
	std::shared_ptr<Card> temp;
	int index;
	if (has7S()) {
		index = getHandCardIndex("7S");
		temp = findHandCard(index);	
	}
	else {
		temp = findLegalCard(0);
		index = getHandCardIndex(temp->getInfo());
	}

	removeHandCard(index);
	return temp;
}

// Discard the first card in hand
void ComputerPlayer::discard(std::string s) {
	std::shared_ptr<Card> temp = findHandCard(0);
	addDiscard(temp);
	removeHandCard(0);
}
