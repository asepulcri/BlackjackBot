//
// Created by Andrea on 08/06/2023.
//

#include "Card.h"
#include <vector>
#include <algorithm>
#include <random>
#include <memory>

#pragma once

class Shoe {
    private:
        int m_size;
        std::vector<std::unique_ptr<Card>> m_currentShoe;

    public:
        Shoe(int shoeSize);

        void shuffleShoe();
        std::unique_ptr<Card> drawCard();

        int getDecksRemaining();
};