#ifndef _COMPUTERPLAYER_H_
#define _COMPUTERPLAYER_H_
#include "player.h"

class ComputerPlayer: public Player {

public:
        ComputerPlayer(int playerNum);
	ComputerPlayer(int playerNum, int score, std::vector<std::shared_ptr<Card>> hand,
                std::vector<std::shared_ptr<Card>> allLegalPlays, std::vector<std::shared_ptr<Card>> discards);

	std::shared_ptr<Card> play(std::string s = "") override;
        void discard(std::string s = "") override;
};

#endif
