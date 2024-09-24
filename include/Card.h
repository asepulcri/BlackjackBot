//
// Created by Andrea on 09/06/2023.
//

#include "EnumNames.h"
#include <vector>
#include <string>
#include <memory>

#pragma once

class Card {
private:
    Suit m_suit;
    Rank m_rank;

public:
    Card(Suit cardSuit, Rank cardRank);
    
    Suit getSuit();
    Rank getRank();
};