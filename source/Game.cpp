#include "Game.h"

Game::Game() {
    m_player = std::make_unique<Player>();
    m_dealer = std::make_unique<Dealer>();
    m_shoe = std::make_unique<Shoe>(6);
    m_gameStats = std::make_unique<GameStats>();

    m_minimumBet = 10;

    m_playerOutcome = undetermined;
}

void Game::playShoe() {

    std::ofstream gameStats("stats.txt", std::ofstream::out | std::ofstream::app);

    m_shoe->shuffleShoe();

	while(m_shoe->getDecksRemaining() > 1.5){
        
		// Start gameplay loop
		
		// Dealer draws card
		Rank dealerCardRank = m_dealer->drawCard(m_shoe->drawCard());

        // Player updates running count
        m_player->updateRunningCount(dealerCardRank);
		
		// Player game loop
		for(int i = 0; i < m_player->getLastHandIdx() + 1; i ++) {
			
			// Player draws cards and decides what to do
			m_player->drawCard(i, m_shoe->drawCard());
			m_player->drawCard(i, m_shoe->drawCard());
			Decisions playerDecision = m_player->makeDecision(i, m_dealer->getUpCardRank());
			
			// Place bets
			m_player->updateTrueCount(m_shoe->getDecksRemaining());
			m_player->betHand(m_minimumBet);
			
			// Player plays turn

			while(playerDecision != stand) {
				if(playerDecision == hit)
					m_player->drawCard(i, m_shoe->drawCard());

				if(playerDecision == split) {
					m_player->splitHand(i);
					m_player->drawCard(i, m_shoe->drawCard());
					m_player->betHand(m_minimumBet);
				}

                if(playerDecision == doubledown) {
                    m_player->drawCard(i, m_shoe->drawCard());
                    m_player->betHand(m_minimumBet);
                    playerDecision = stand;
                }

                if(playerDecision != stand)
			        playerDecision = m_player->makeDecision(i, m_dealer->getUpCardRank());
			}

			if(m_player->getHandValue(i) > 21){
				std::cout << "Player busted" << "\n";
				m_playerOutcome = lose;
			}

		}

        if(m_playerOutcome != lose) {
            // Dealer plays turn
            dealerCardRank = m_dealer->drawCard(m_shoe->drawCard());

            m_player->updateRunningCount(dealerCardRank);

            Decisions dealer1Decision = m_dealer->makeDecision();
            
            // Dealer makes decisions
            while(dealer1Decision != stand) {
                if(dealer1Decision == hit) {
                    dealerCardRank = m_dealer->drawCard(m_shoe->drawCard());
                    m_player->updateRunningCount(dealerCardRank);
                }
                
                dealer1Decision = m_dealer->makeDecision();
            }

            if(m_dealer->getHandValue() > 21) {
                std::cout << "Dealer busted" << "\n";
                m_playerOutcome = win;
            }

            // Check for win, lose or push
            if(m_playerOutcome != win) {
                for(int i = 0; i < m_player->getLastHandIdx() + 1; i ++) {
                    if(m_player->getHandValue(i) > m_dealer->getHandValue()) {
                        std::cout << "Player wins hand " << i << "\n";
                        m_playerOutcome = win;
                    }

                    else if(m_player->getHandValue(i) < m_dealer->getHandValue()) {
                        std::cout << "Player loses hand " << i << "\n";
                        m_playerOutcome = lose;
                    }

                    else if(m_player->getHandValue(i) == m_dealer->getHandValue()){
                        std::cout << "Hand is tied" << "\n";
                        m_playerOutcome = push;
                    }
            }

            }       
        }

        // Update player chip count
        m_player->updateWallet(m_playerOutcome);

        // Update hand stats
        m_gameStats->updateHandStats(m_player->getRunningCount(), m_player->getTrueCount(), m_player->getWalletAmount());

        // Reset for next hand
        m_playerOutcome = undetermined;
        m_player->resetHands();
        m_dealer->resetHand();
	}

    return;
}

void Game::resetShoe() {
    // Create new shoe and reset player count
    m_player->resetCount();
    m_shoe = std::make_unique<Shoe>(6);
}

void Game::writeStatstoTXT() {
    // Provide stat tracking
    std::ofstream outFile("../stats.txt");
    for (const auto &e : m_gameStats->m_walletHistory) outFile << e << "\n";
    outFile.close();
}