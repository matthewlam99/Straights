#ifndef _HUMANPLAYER_H_
#define _HUMANPLAYER_H_
#include "player.h"

class HumanPlayer: public Player {

public:
	HumanPlayer(int playerNum);
	HumanPlayer(int playerNum, int score, std::vector<std::shared_ptr<Card>> hand, 
		    std::vector<std::shared_ptr<Card>> allLegalPlays, 
		    std::vector<std::shared_ptr<Card>> discards);
	std::shared_ptr<Card> play(std::string s) override;
        void discard(std::string s) override;
};

#endif
