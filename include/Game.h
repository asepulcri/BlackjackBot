#include <iostream>
#include <memory>
#include "Card.h"
#include "Player.h"
#include "Shoe.h"

#pragma once

class Game {
    private:
        void resetHands(Player p_player, Dealer p_dealer, Outcomes p_playerOutcome);

    public:
        void playGame();
};
