#include "controller.h"

Controller::Controller(unsigned int seed) {
	gameOver = false;
	deck = std::make_shared<Deck>(seed);
	table = std::make_shared<Table>(); 
}

void Controller::setPreviousState(std::ifstream & inf) {
	std::string line;
	int count = 1;
	
	std::vector<std::shared_ptr<Card>> cards;
	unsigned int seed = deck->getSeed();
	// Making a new Deck
	while(count <= 4 && std::getline(inf, line)) {
		// Checks if file is readable   
                if (inf.fail()){
                        std::cerr << "Error, could not open input file" << std::endl;
                        break;
                }
		
		std::stringstream iss{line};
                std::string cmd;
		// Inputs the deck
		while (iss >> cmd) {
			if (cmd.length() == 2) {
				cards.emplace_back(std::make_shared<Card>(cmd));
			}			
		}
		count++;
	}
	deck = std::make_shared<Deck>(seed, cards);
 	
	// Setup the Table	
	std::getline(inf, line);
	count++;
	std::shared_ptr<Card> curCard = std::make_shared<Card>(line);
	table->clearTable();
	
	while(count <= 9 && std::getline(inf, line)) {
                // Checks if file is readable   
                if (inf.fail()){
                        std::cerr << "Error, could not open input file" << std::endl;
                        break;
                }

                std::stringstream iss{line};
                std::string cmd;
                // Inputs the table
                while (iss >> cmd) {
                        if (cmd.length() == 2 && line != "NA") {
				table->addCard(std::make_shared<Card>(cmd));
                        }
                }
		count++;
        }
	table->setCurCard(curCard);
	
	// Setup Players
	int score;
        int playerNum = 0;
        std::vector<std::shared_ptr<Card>> discards;
        std::vector<std::shared_ptr<Card>> hand;
        std::vector<std::shared_ptr<Card>> allLegalPlays;	
	while(count <= 21 && std::getline(inf, line)) {
		// Checks if file is readable   
                if (inf.fail()){
                        std::cerr << "Error, could not open input file" << std::endl;
                        break;
                }

		std::stringstream iss{line};
		std::string cmd;
		if (count % 3 == 1) {
			std::string playerType;
			int index = 1;
			while (index <= 3 && iss >> cmd) {
				if (index == 1) playerType = cmd;
				else if (index == 2) score = stoi(cmd);
				else if (index == 3) playerNum = stoi(cmd);
				index++;
			}
			if (playerType == "c") {
				players.emplace_back(std::make_shared<ComputerPlayer>(playerNum, score, hand, discards, allLegalPlays));
			} 
			else if (playerType == "h") {
				players.emplace_back(std::make_shared<HumanPlayer>(playerNum, score, hand, discards, allLegalPlays));
			}	
		}
		else if (count % 3 == 2) {
			while (iss >> cmd) {
				if (cmd.length() == 2 && cmd != "NA") {
					players[playerNum-1]->addHandCard(std::make_shared<Card>(cmd));
				}
			}
		}
		else {
			while (iss >> cmd) {
                                if (cmd.length() == 2 && cmd != "NA") {
                                        players[playerNum-1]->addDiscard(std::make_shared<Card>(cmd));
                                }
                        }
		}
		count++;
	}
}

void Controller::dealCards() {
	int playerCount = 0;
	for (unsigned int i = 0; i < deck->getDeckSize(); ++i) {
		if ( i % 13 == 0 && i != 0) {
			playerCount++;
		}
		std::shared_ptr<Card> c = deck->getCard(i);
		players[playerCount]->addHandCard(c);
	}
}

// Determines if the round is over.
bool Controller::roundOver() {
        for (unsigned int i = 0; i < players.size(); ++i) {
                if(!players[i]->emptyHand()) {
                        return false;
                }
        }
        return true;
}

void Controller::invitePlayers() {
	std::cin.exceptions(ios::eofbit|ios::failbit);
	string cmd;
	int countPlayers = 1;
	
	try {
		while(countPlayers <= 4) {
			try {
				std::cout << "Is Player " << countPlayers 
					  << " a human (h) or a computer (c)?" << std::endl;	
				std::cout << ">";	
				std::cin >> cmd;

				// Sets the Player as a Human
				if (cmd == "h") {
					std::shared_ptr<HumanPlayer> hp = std::make_shared<HumanPlayer>(countPlayers);
					players.emplace_back(hp);	
					countPlayers++;	
				}
				// Sets the Player as a Computer
				else if (cmd == "c") {
					std::shared_ptr<ComputerPlayer> cp = std::make_shared<ComputerPlayer>(countPlayers);
					players.emplace_back(cp);
					countPlayers++;
				}
			}
			catch (std::invalid_argument & e) {
				std::cerr << e.what() << std::endl;
			}
		}
	}
	catch (ios::failure &) {}
}

void Controller::startRound() {
	clearGame();
	deck->shuffleCards();
	dealCards();
	bool foundPlayer = false;

	// Sets the player with 7S to start the round
	for (unsigned int i = 0; i < players.size() && !foundPlayer; ++i) {
		if (players[i]->has7S()) {
			curPlayer = i;
			foundPlayer = true;
		}
	}
	cout << "A new round begins. It's Player" << curPlayer + 1 << "'s turn to play." << endl;	
}

void Controller::playerTurn() {
	cout << table->getInfo();
	// Calculates all legal moves
        players[curPlayer]->findAllLegalPlays(table);
	cout << players[curPlayer]->getHandInfo() << endl;
	cout << players[curPlayer]->getLegalInfo() << endl;
	
	// Human Players' Move
	if (typeid(*players[curPlayer]) == typeid(HumanPlayer)) {
		humanPlayerMove();
	}
        // Computer Player's Move
        if (typeid(*players[curPlayer]) == typeid(ComputerPlayer)) {
                computerPlayerMove();
        }
        setNextPlayer();
}


void Controller::humanPlayerMove() {
	cin.exceptions(ios::eofbit|ios::failbit);
        string s;
	bool validMove = false;
	try {
		while(!validMove && !gameOver) {
			try {
				cout << ">";
				getline(std::cin, s);
				std::istringstream iss{s};
				std::string cmd;
				iss >> cmd;
				
				if (cmd == "play") {
					try {
						std::string card;
						iss >> card;
						
						if (card == "") {
							throw std::invalid_argument("Failed to obtain a rank. \n");
						}

						int cardIndex = players[curPlayer]->getAllLegalPlaysIndex(card);
						if (cardIndex != -1) {
							table->addCard(players[curPlayer]->play(card));
							cout << "Player" << curPlayer + 1 << " plays " << card 
							     << "." << endl;
							validMove = true;
						}
						else {
							throw std::invalid_argument("");
						}
					}	
					catch (std::invalid_argument & e) {
						cout << e.what() << "This is not a legal play." << endl;
					}					
				}
				else if (cmd == "discard") {
					try {
						std::string card;
                                                iss >> card;

						if (card == "") {
                                                        throw std::invalid_argument("Failed to obtain a rank.\n");
                                                }

						int cardIndex = players[curPlayer]->getHandCardIndex(card);
						if (players[curPlayer]->noLegalPlays() && cardIndex != -1) {
							players[curPlayer]->discard(card);
							cout << "Player" << curPlayer + 1 << " discards " 
							     << card <<"." << endl;
							validMove = true;
						}
						else {
							throw std::invalid_argument("");
						}
					}
					catch(std::invalid_argument & e) {
						if (!players[curPlayer]->noLegalPlays()) {
							cout << "You have a legal play. You may not discard." << endl;
					
						}
						else {
							cout << e.what() << "This is not a legal play." << endl;
						}
					}
				}
				else if (cmd == "deck") {
					cout << *deck << endl;
				}
				else if (cmd == "quit") {
					gameOver = true;
				}
				else if (cmd == "ragequit") {
					rageQuit();
					cout << "Player" << curPlayer + 1 
					     << " ragequits. A computer will now take over." << endl;
					validMove = true;
				}
				else if (cmd != "") {
					std::cerr << "Unrecognized command " << cmd << "!" << std::endl;
				}
			}
			catch (std::invalid_argument & e) {
                		std::cerr << e.what() << std::endl;
            		}  
		}
	} 
	catch (ios::failure &) {} // Any I/O failure quits
	
}

void Controller::computerPlayerMove() {
	if (!players[curPlayer]->noLegalPlays()) {
        	table->addCard(players[curPlayer]->play());
		cout << "Player" << curPlayer + 1 << " plays " << table->getLastCard()->getInfo() <<"." << endl;
        }
        else {
		std::shared_ptr<Card> temp = players[curPlayer]->findHandCard(0);	
		cout << "Player" << curPlayer + 1 << " discards " << temp->getInfo() <<"." << endl;
        	players[curPlayer]->discard();
        }
}

// Sets the next player
void Controller::setNextPlayer() {
	curPlayer = (curPlayer + 1) % 4;
}

void Controller::endRound() {
	for (unsigned int i = 0; i < players.size(); ++i) {
		int oldScore = players[i]->getScore();
		int roundScore = players[i]->sumDiscard();
		players[i]->setScore(oldScore + roundScore);
		std::cout <<  players[i]->getDiscardInfo() << std::endl
			  << "Player" << i + 1 << "'s score: "
			  << oldScore << " + " << roundScore << " = " 
			  << oldScore + roundScore << std::endl;
	}	

	// check if there is a winner
	for (unsigned int i = 0; i < players.size(); ++i) {
        	if (players[i]->getScore() >= 80) {
                        gameOver = true;
                }
        }

	if (gameOver) {
		getWinner();
		return;
	}
	startRound();
}

// Determines who is the winner and output message.
void Controller::getWinner() {
	int minScore = INT8_MAX;
	std::vector<int> winningPlayers;

	// Determines the minimum score.
        for (unsigned int i = 0; i < players.size(); ++i) {
                int playerScore = players[i]->getScore();
                if (playerScore < minScore) {
                        minScore = playerScore;
                }
        }

        // Gets list of winning players.
        for (unsigned int i = 0; i < players.size(); ++i) {
                if (players[i]->getScore() == minScore) {
                        winningPlayers.push_back(players[i]->getPlayerNum());
                }
        }	

	for (unsigned int i = 0; i < winningPlayers.size(); ++i) {
        	if (winningPlayers.size() != 1 || i != winningPlayers.size() -1) {
			std::cout << "Player" << winningPlayers[i] << ", ";
		}
		else {
			std::cout << "Player" << winningPlayers[i];
		}
	}
	std::cout << " wins!" << std::endl;
}

void Controller::rageQuit() {
	std::vector<std::shared_ptr<Card>> hand = players[curPlayer]->getHand();
    	std::vector<std::shared_ptr<Card>> discards = players[curPlayer]->getDiscards();
    	std::vector<std::shared_ptr<Card>> allLegalPlays = players[curPlayer]->getAllLegalPlays();
	int score = players[curPlayer]->getScore();
    	std::shared_ptr<ComputerPlayer> p = make_shared<ComputerPlayer>(curPlayer + 1, score, hand, 
					                                allLegalPlays, discards);
	players.erase(players.begin() + curPlayer);
	players.insert(players.begin() + curPlayer, p);
}

bool Controller::getGameOver() const {
	return gameOver;
}

// Only for testing
int Controller::getCurPlayer() {
	return curPlayer;
}
	
void Controller::clearGame() {
	table->clearTable();
	
	// Clears information about the player
	for (unsigned int i = 0; i < players.size(); ++i) {
		players[i]->clearCards();
	}	
}

