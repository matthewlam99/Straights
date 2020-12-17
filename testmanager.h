#ifndef _TESTMANAGER_H_
#define _TESTMANAGER_H_

#include <memory>
#include <vector>
#include <string>

#include "card.h"
#include "deck.h"
#include "table.h"
#include "player.h"
#include "computerplayer.h"
#include "humanplayer.h"
#include "controller.h"

class TestManager {
public:
	std::string getStatusStr(bool status);
	void run();
	void cardTests();
	void deckTests();
	void tableTests();
	void playerTests();
	void humanPlayerTests();
	void computerPlayerTests();
};

#endif
