#include "../include/shoe.h"
#include "../include/card.h"
#include <vector>
#include <algorithm>
#include <random>


shoes::shoe::shoe(int shoeSize) : m_size(shoeSize)
{
    for (int i = 1; i <= shoeSize; i++) {
        for (int j = 0; j < 52; j++) {
            m_currentShoe.push_back(std::make_unique<cards::card>(cards::Suit(j / 13), cards::Rank((j % 13) + 1)));
        }
    }
};

void shoes::shoe::shuffleShoe() {
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(m_currentShoe.begin(), m_currentShoe.end(), generator);
};

std::unique_ptr<cards::card> shoes::shoe::drawCard() {
    if (m_currentShoe.empty())
        return nullptr;

    std::unique_ptr<cards::card> card = std::move(m_currentShoe.back());
    m_currentShoe.pop_back();
    return card;
};