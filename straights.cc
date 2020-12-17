#include <iostream>
#include <fstream>
#include <memory>
#include "controller.h"
#include "testmanager.h"

using namespace std;

int main(int argc, char **argv) {
	// Used for unit testing
	// TestManager test;
	// test.run();
	
	// Loading game from previous state
	std::ifstream inf;
	unsigned int seed = 0;
	bool readFileExist = false;
	
	for (int argi = 0; argi < argc; ++argi) {
		string s{argv[argi]};

		if (argi == 1) {
			seed = stoi(s);
		}
		
		// If read file is in command line args
                if (s.find(".txt") != std::string::npos) {
                        inf = std::ifstream{ s };
                        readFileExist = true;
                }
	}
	Controller ctrl{seed};

	if (readFileExist) {
		ctrl.setPreviousState(inf);
	}
	else {
		ctrl.invitePlayers();
        	ctrl.startRound();
	}
	
	//Main Game Loop
	while (!ctrl.getGameOver()) {
		ctrl.playerTurn();
		
		if (ctrl.roundOver()) {
			ctrl.endRound();
		}
	}
}

