#include "testmanager.h"

string TestManager::getStatusStr(bool status) {
	return status ? "TEST PASSED" : "TEST FAILED";
}

void TestManager::run() {
	cardTests();
	deckTests();
	tableTests();
	playerTests();
	humanPlayerTests();
	computerPlayerTests();
}

void TestManager::cardTests() {
	std::vector<std::string> cardTestDesc;
	std::vector<bool> cardTestStatus;

	// Test1
	Card c1 = Card(HEART, SEVEN);
	Card c2 = Card(SPADE, KING);
	cardTestStatus.emplace_back(!(c1 == c2));
	cardTestDesc.emplace_back("Test1: Not equal cards");
	
	// Test2
	cardTestStatus.emplace_back(c1.getInfo() == "7H");
	cardTestDesc.emplace_back("Test2: Stringify rank and suit");

	// Test3
	Card c3 = Card("7S");
	cardTestStatus.emplace_back(c3.getInfo() == "7S");
        cardTestDesc.emplace_back("Test3: String Constructor");

	std::cout << "Card Tests" << std::endl;
	for (unsigned int i = 0; i < cardTestStatus.size(); ++i) {
		std::cout << cardTestDesc[i] << std::endl 
			  << getStatusStr(cardTestStatus[i]) << std::endl;	
	}
	std::cout << std::endl;
}

void TestManager::deckTests() {
	std::vector<std::string> deckTestDesc;
        std::vector<bool> deckTestStatus;

	// Test1
	Deck d = Deck{};
	bool createProperDeck = d.getDeckSize() == 52 && d.getCard(0)->getInfo() == "AC"
                                && d.getCard(51)->getInfo() == "KS";
	deckTestDesc.emplace_back("Test1: Creates Deck Properly");
	deckTestStatus.emplace_back(createProperDeck);
	
	// Test2
	Deck d2 = Deck{};
	d2.shuffleCards();
	bool shuffleProperly = d2.getCard(51)->getInfo() != d.getCard(51)->getInfo() || 
			       d2.getCard(0)->getInfo() != d.getCard(0)->getInfo();
	deckTestDesc.emplace_back("Test2: Shuffle Cards");
	deckTestStatus.emplace_back(shuffleProperly);

	// Test3
	Deck d3 = Deck{5};
	d3.shuffleCards();
	bool seedWork = d2.getCard(51)->getInfo() != d3.getCard(51)->getInfo() ||
                        d2.getCard(0)->getInfo() != d3.getCard(0)->getInfo();
	deckTestDesc.emplace_back("Test3: Seed Works Properly");
        deckTestStatus.emplace_back(seedWork);
		
	std::cout << "Deck Tests" << std::endl;
        for (unsigned int i = 0; i < deckTestStatus.size(); ++i) {
                std::cout << deckTestDesc[i] << std::endl
                          << getStatusStr(deckTestStatus[i]) << std::endl;
        }
        std::cout << std::endl;
}

void TestManager::tableTests() {
        std::vector<std::string> tableTestDesc;
        std::vector<bool> tableTestStatus;
	
	Table t = Table{};
	std::shared_ptr<Card> c1 = std::make_shared<Card>(HEART, SEVEN);
	std::shared_ptr<Card> c2 = std::make_shared<Card>(SPADE, KING);
	std::shared_ptr<Card> c3 = std::make_shared<Card>(HEART, SIX);
	std::shared_ptr<Card> c4 = std::make_shared<Card>(HEART, FIVE);
	std::shared_ptr<Card> c5 = std::make_shared<Card>(HEART, KING);
	std::shared_ptr<Card> c6 = std::make_shared<Card>(SPADE, SEVEN);
	std::shared_ptr<Card> c7 = std::make_shared<Card>(CLUB, SEVEN);
	
	// Test1
	t.addCard(c1);
	t.addCard(c2);
	std::string s1 = "Cards on the table:\nClubs: \nDiamonds: \nHearts: 7 \nSpades: K \n";
	tableTestDesc.emplace_back("Test1: Add cards");
        tableTestStatus.emplace_back(t.getInfo() == s1);
	
	// Test2	
	t.addCard(c3);
        t.addCard(c4);
	t.addCard(c5);
        t.addCard(c6);
	t.addCard(c7);
	std::string s2 = "Cards on the table:\nClubs: 7 \nDiamonds: \nHearts: 5 6 7 K \nSpades: 7 K \n";
        tableTestDesc.emplace_back("Test2: Add cards and order sorted");
        tableTestStatus.emplace_back(t.getInfo() == s2);
	
	// Test3
	std::shared_ptr<Card> c8 = std::make_shared<Card>(DIAMOND, EIGHT);
	tableTestDesc.emplace_back("Test3: Not a legal move");
	tableTestStatus.emplace_back(t.checkLegalMove(c8) == false);
	
	// Test4
	std::shared_ptr<Card> c9 = std::make_shared<Card>(DIAMOND, SEVEN);
	tableTestDesc.emplace_back("Test4: Legal move of rank 7");
        tableTestStatus.emplace_back(t.checkLegalMove(c9) == true);

	// Test5
	std::shared_ptr<Card> c10 = std::make_shared<Card>(SPADE, QUEEN);
	tableTestDesc.emplace_back("Test5: Legal move of non rank 7");
        tableTestStatus.emplace_back(t.checkLegalMove(c10) == true);

	std::cout << "Table Tests" << std::endl;
        for (unsigned int i = 0; i < tableTestStatus.size(); ++i) {
                std::cout << tableTestDesc[i] << std::endl
                          << getStatusStr(tableTestStatus[i]) << std::endl;
        }
        std::cout << std::endl;
}

void TestManager::playerTests() {
	std::vector<std::string> playerTestDesc;
        std::vector<bool> playerTestStatus;

	HumanPlayer h = HumanPlayer{1};
	
	// Test1
	bool emptyPlayer = h.getPlayerNum() == 1 && h.emptyHand() == true && h.getHandInfo() == "Your hand: ";
	playerTestDesc.emplace_back("Test1: Empty cards and correct playerNum");
        playerTestStatus.emplace_back(emptyPlayer == true);

	// Test2
	std::shared_ptr<Card> c1 = std::make_shared<Card>(HEART, SEVEN);
        std::shared_ptr<Card> c2 = std::make_shared<Card>(SPADE, KING);
        std::shared_ptr<Card> c3 = std::make_shared<Card>(HEART, SIX);
	h.addHandCard(c1);
	h.addHandCard(c2);
	h.addHandCard(c3);

	bool handAdded = h.getHandCardIndex("7H") == 0 && h.getHandCardIndex("KS") == 1 &&
	       	             h.getHandCardIndex("6H") == 2 && h.emptyHand() == false &&
			     h.getHandInfo() == "Your hand: 7H KS 6H ";
	playerTestDesc.emplace_back("Test2: Adding and finding cards");
        playerTestStatus.emplace_back(handAdded == true);
	
	// Test3
	h.removeHandCard(h.getHandCardIndex("KS"));
	bool handRemoved = h.getHandCardIndex("7H") == 0 && h.getHandCardIndex("KS") == -1 &&
			       h.getHandCardIndex("6H") == 1 && h.emptyHand() == false &&
			       h.getHandInfo() == "Your hand: 7H 6H ";
	playerTestDesc.emplace_back("Test3: Removing and finding cards");
        playerTestStatus.emplace_back(handRemoved == true);
	
	// Test4
	std::shared_ptr<Card> c4 = std::make_shared<Card>(HEART, FIVE);
        std::shared_ptr<Card> c5 = std::make_shared<Card>(HEART, KING);
        std::shared_ptr<Card> c6 = std::make_shared<Card>(SPADE, SEVEN);
        std::shared_ptr<Card> c7 = std::make_shared<Card>(CLUB, SEVEN);
        h.addHandCard(c4);
        h.addHandCard(c5);
        h.addHandCard(c6);
        h.addHandCard(c7);
	std::shared_ptr<Card> handFindRes = h.findHandCard(3);
	bool handFind = h.getHandInfo() == "Your hand: 7H 6H 5H KH 7S 7C " && handFindRes->getInfo() == c5->getInfo();	
	playerTestDesc.emplace_back("Test4: Retrieving cards in the hand");
        playerTestStatus.emplace_back(handFind == true);
	
	// Test5
	HumanPlayer h2 = HumanPlayer{2};
	std::shared_ptr<Table> table = std::make_shared<Table>();
	table->addCard(std::make_shared<Card>(SPADE, SEVEN));
	table->addCard(std::make_shared<Card>(CLUB, SEVEN));
	
	//4H QS QC JS QH 7D 6S 8H 5D TC 3C AC TH
	h2.addHandCard(std::make_shared<Card>(HEART, FOUR));
	h2.addHandCard(std::make_shared<Card>(SPADE, QUEEN));
	h2.addHandCard(std::make_shared<Card>(CLUB, QUEEN));
	h2.addHandCard(std::make_shared<Card>(SPADE, JACK));
	h2.addHandCard(std::make_shared<Card>(HEART, QUEEN));
	h2.addHandCard(std::make_shared<Card>(DIAMOND, SEVEN));
	h2.addHandCard(std::make_shared<Card>(SPADE, SIX));
	h2.addHandCard(std::make_shared<Card>(HEART, EIGHT));
	h2.addHandCard(std::make_shared<Card>(DIAMOND, FIVE));
	h2.addHandCard(std::make_shared<Card>(CLUB, TEN));
	h2.addHandCard(std::make_shared<Card>(CLUB, THREE));
	h2.addHandCard(std::make_shared<Card>(CLUB, ACE));
	h2.addHandCard(std::make_shared<Card>(HEART, TEN));
	h2.findAllLegalPlays(table);
	bool checkLegalPlays = h2.getLegalInfo() == "Legal plays: 7D 6S ";
	playerTestDesc.emplace_back("Test5: Calculating all legal plays");
        playerTestStatus.emplace_back(checkLegalPlays == true);
		
	// Test6
	bool findLegalPlays = h2.getAllLegalPlaysIndex("7D") == 0 && h2.getAllLegalPlaysIndex("6S") == 1;
        playerTestDesc.emplace_back("Test6: Finding legal plays");
        playerTestStatus.emplace_back(findLegalPlays == true);

	// Test7
	h2.removeHandCard(5);
	h2.removeHandCard(5);
	//4H QS QC JS QH 8H 5D TC 3C AC TH
	h2.findAllLegalPlays(table);
	bool noLegalPlays = h2.getLegalInfo() == "Legal plays: " && h2.noLegalPlays();
	playerTestDesc.emplace_back("Test7: No legal plays");
        playerTestStatus.emplace_back(noLegalPlays == true);
	
	// Test8
	h2.discard("4H");
	h2.discard("QS");
	h2.discard("TC");
	h2.discard("AC");
	//QC JS QH 8H 5D 3C TH
	bool discardSumWork = h2.sumDiscard() == 27 && h2.getHandInfo() == "Your hand: QC JS QH 8H 5D 3C TH ";
	playerTestDesc.emplace_back("Test8: Discard sum calculation");
        playerTestStatus.emplace_back(discardSumWork == true);
	
	// Test9
	bool discardIndexing = h2.getDiscardIndex("4H") == 0 && h2.getDiscardIndex("TC") == 2 &&
			       h2.getDiscardInfo() == "Player2’s discards: 4H QS TC AC ";
	playerTestDesc.emplace_back("Test9: Discard indexing");
        playerTestStatus.emplace_back(discardIndexing == true);

	// Test10
	playerTestDesc.emplace_back("Test10: Has 7S");
        playerTestStatus.emplace_back(h.has7S() == true && h2.has7S() == false);	
	
	// Test11
	h2.setScore(100);
	playerTestDesc.emplace_back("Test11: Setting score");
        playerTestStatus.emplace_back(h2.getScore() == 100);

	// Test12
	h2.clearCards();
	bool playCardsClear = h2.getDiscardInfo() == "Player2’s discards: " && h2.getHandInfo() == "Your hand: " && 
			      h2.getLegalInfo() == "Legal plays: " && h2.noLegalPlays();
	playerTestDesc.emplace_back("Test12: Clearing all cards");
        playerTestStatus.emplace_back(playCardsClear == true);
	
	std::cout << "Player Tests" << std::endl;
        for (unsigned int i = 0; i < playerTestStatus.size(); ++i) {
                std::cout << playerTestDesc[i] << std::endl
                          << getStatusStr(playerTestStatus[i]) << std::endl;
        }
        std::cout << std::endl;
}

void TestManager::humanPlayerTests() {
	std::vector<std::string> humanPlayerTestDesc;
        std::vector<bool> humanPlayerTestStatus;

        HumanPlayer h = HumanPlayer{1};
	std::shared_ptr<Card> c1 = std::make_shared<Card>(HEART, SEVEN);
        std::shared_ptr<Card> c2 = std::make_shared<Card>(SPADE, KING);
        std::shared_ptr<Card> c3 = std::make_shared<Card>(HEART, SIX);
        h.addHandCard(c1);
        h.addHandCard(c2);
        h.addHandCard(c3);
	std::shared_ptr<Card> result = h.play("KS");
	// Test1 
	bool properlyPlay = result == c2 && h.getHandCardIndex("KS") == -1; 
        humanPlayerTestDesc.emplace_back("Test1: HumanPlayer making a play");
        humanPlayerTestStatus.emplace_back(properlyPlay == true);

	// Test2 
	std::shared_ptr<Card> c4 = std::make_shared<Card>(HEART, FIVE);
        std::shared_ptr<Card> c5 = std::make_shared<Card>(HEART, KING);
        std::shared_ptr<Card> c6 = std::make_shared<Card>(SPADE, SEVEN);
        std::shared_ptr<Card> c7 = std::make_shared<Card>(CLUB, SEVEN);			
        h.addHandCard(c4);
        h.addHandCard(c5);
        h.addHandCard(c6);
        h.addHandCard(c7);
	h.discard("5H");
	h.discard("6H");
	bool properlyDiscard = h.getHandCardIndex("5H") == -1 && h.getHandCardIndex("6H") == -1 &&
			       h.getDiscardIndex("5H") != -1 && h.getDiscardIndex("6H") != -1 && 
			       h.sumDiscard() == 11;
	humanPlayerTestDesc.emplace_back("Test2: HumanPlayer making a discard");
        humanPlayerTestStatus.emplace_back(properlyDiscard == true);

	std::cout << "HumanPlayer Tests" << std::endl;
        for (unsigned int i = 0; i < humanPlayerTestStatus.size(); ++i) {
                std::cout << humanPlayerTestDesc[i] << std::endl
                          << getStatusStr(humanPlayerTestStatus[i]) << std::endl;
        }
        std::cout << std::endl;
} 

void TestManager::computerPlayerTests() {
	std::vector<std::string> computerPlayerTestDesc;
        std::vector<bool> computerPlayerTestStatus;	

	ComputerPlayer c = ComputerPlayer{1};
	std::shared_ptr<Table> table = std::make_shared<Table>();

	// Test1
	std::shared_ptr<Card> c1 = std::make_shared<Card>(HEART, SEVEN);
        std::shared_ptr<Card> c2 = std::make_shared<Card>(SPADE, KING);
        std::shared_ptr<Card> c3 = std::make_shared<Card>(HEART, SIX);
        c.addHandCard(c1);
        c.addHandCard(c2);
        c.addHandCard(c3);
	c.findAllLegalPlays(table);
	std::shared_ptr<Card> result = c.play();
	bool properlyPlay = result == c1 && c.getHandCardIndex("7H") == -1;
	computerPlayerTestDesc.emplace_back("Test1: ComputerPlayer making a play");
        computerPlayerTestStatus.emplace_back(properlyPlay == true);

	// Test2 
	std::shared_ptr<Card> c4 = std::make_shared<Card>(HEART, FIVE);
        std::shared_ptr<Card> c5 = std::make_shared<Card>(HEART, KING);
        std::shared_ptr<Card> c6 = std::make_shared<Card>(SPADE, SEVEN);
        std::shared_ptr<Card> c7 = std::make_shared<Card>(CLUB, SEVEN);
        c.addHandCard(c4);
        c.addHandCard(c5);
        c.addHandCard(c6);
        c.addHandCard(c7);
        c.discard();
        c.discard();
        bool properlyDiscard = c.getHandCardIndex("KS") == -1 && c.getHandCardIndex("6H") == -1 &&
                               c.getDiscardIndex("KS") != -1 && c.getDiscardIndex("6H") != -1 &&
			       c.sumDiscard() == 19;
        computerPlayerTestDesc.emplace_back("Test2: ComputerPlayer making a discard");
        computerPlayerTestStatus.emplace_back(properlyDiscard == true);

	std::cout << "ComputerPlayer Tests" << std::endl;
        for (unsigned int i = 0; i < computerPlayerTestStatus.size(); ++i) {
                std::cout << computerPlayerTestDesc[i] << std::endl
                          << getStatusStr(computerPlayerTestStatus[i]) << std::endl;
        }
        std::cout << std::endl;
}
