#include <iostream>
#include <fstream>
#include <memory>
#include "Card.h"
#include "GameStats.h"
#include "Player.h"
#include "Shoe.h"

#pragma once

class Game{
    private:
        std::unique_ptr<Player> m_player;
	    std::unique_ptr<Dealer> m_dealer;
	    std::unique_ptr<Shoe> m_shoe;
        std::unique_ptr<GameStats> m_gameStats;

        int m_minimumBet;

        Outcomes m_playerOutcome;
    
    public:
        Game();

        // Actions
        void playShoe();
        void resetShoe();
        void writeStatstoTXT();
};