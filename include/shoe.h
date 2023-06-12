//
// Created by Andrea on 08/06/2023.
//

#include "card.h"
#include <vector>
#include <algorithm>
#include <random>

namespace shoe {
    class shoe {
    private:
        int m_size;
        std::vector<card::card> currentShoe;

    public:
        shoe(int shoeSize): m_size(shoeSize) {
            for(int i = 1; i <= shoeSize; i++) {
                for(int j = 0; j < 52; j++) {
                    currentShoe.emplace_back(card::Suit(j / 13), card::Rank((j % 13) + 1));
                }
            }
        }

        void shuffleShoe() {
            std::random_device rd;
            std::mt19937 generator(rd());
            std::shuffle(currentShoe.begin(), currentShoe.end(), generator);
        }
    };
}
