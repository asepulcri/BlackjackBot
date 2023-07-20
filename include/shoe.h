//
// Created by Andrea on 08/06/2023.
//

#include "card.h"
#include <vector>
#include <algorithm>
#include <random>

#pragma once

namespace shoes {
    class shoe {
    private:
        int m_size;
        std::vector<std::unique_ptr<cards::card>> m_currentShoe;

    public:
        shoe(int shoeSize);

        void shuffleShoe();
        std::unique_ptr<cards::card> drawCard();

    };
}
