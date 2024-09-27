#include <iostream>
#include <memory>
#include "Card.h"
#include "Player.h"
#include "Shoe.h"

#pragma once

class Game{
    private:
        std::unique_ptr<Player> m_player;
	    std::unique_ptr<Dealer> m_dealer;
	    std::unique_ptr<Shoe> m_shoe;

        Outcomes m_playerOutcome;
    
    public:
        Game();

        void playShoe();
        void resetShoe();
};