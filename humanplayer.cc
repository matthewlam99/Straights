#include "humanplayer.h"

HumanPlayer::HumanPlayer(int playerNum) : Player{playerNum} {}

HumanPlayer::HumanPlayer(int playerNum, int score, std::vector<std::shared_ptr<Card>> hand,
                std::vector<std::shared_ptr<Card>> allLegalPlays, std::vector<std::shared_ptr<Card>> discards)
                : Player{playerNum, score, hand, allLegalPlays, discards} {}

std::shared_ptr<Card> HumanPlayer::play(std::string s) {
	int cardIndex = getHandCardIndex(s);
	std::shared_ptr<Card> temp = findHandCard(cardIndex);
        removeHandCard(cardIndex);
        return temp;	
}

void HumanPlayer::discard(std::string s) {
	int cardIndex = getHandCardIndex(s);
	std::shared_ptr<Card> temp = findHandCard(cardIndex);
        addDiscard(temp);
        removeHandCard(cardIndex);
}
