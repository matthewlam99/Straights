#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <vector>
#include <memory>
#include <fstream>
#include <iostream>
#include <sstream>
#include <typeinfo>

#include "deck.h"
#include "table.h"
#include "player.h"
#include "computerplayer.h"
#include "humanplayer.h"
#include "testmanager.h"

class Controller {
	std::vector<std::shared_ptr<Player>> players;
	std::shared_ptr<Table> table;
	std::shared_ptr<Deck> deck;
	unsigned int seed;
	int curPlayer;
	bool gameOver;
public:
	Controller(unsigned int seed = 0);
	void setPreviousState(std::ifstream & inf);
	void invitePlayers();
	void startRound();
	void playerTurn();
	void setNextPlayer();
	void endRound();
	bool roundOver();
	void rageQuit();
	void clearGame();
	bool getGameOver() const;
	int getCurPlayer();
	
	// For Testing Purposes
	// friend class TestManager;
private:
	void dealCards();
	void checkWinner();
	void getWinner();
	void humanPlayerMove();
	void computerPlayerMove();
};
#endif
