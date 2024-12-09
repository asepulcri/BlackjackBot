#include "Shoe.h"

Shoe::Shoe(int shoeSize) : m_size(shoeSize)
{
    // Create 52 cards to put into shoe
    for (int i = 1; i <= shoeSize; i++) {
        for (int j = 0; j < 52; j++) {
            m_currentShoe.push_back(std::make_unique<Card>(Suit(j / 13), Rank((j % 13) + 1)));
        }
    }
};

void Shoe::shuffleShoe() {
    // Initiate rng and shuffle cards
    std::random_device rd;
    std::mt19937 generator(rd());
    std::shuffle(m_currentShoe.begin(), m_currentShoe.end(), generator);
};

std::unique_ptr<Card> Shoe::drawCard() {
    // Return card as a unique pointer
    if (m_currentShoe.empty())
        return nullptr;

    std::unique_ptr<Card> card = std::move(m_currentShoe.back());
    m_currentShoe.pop_back();
    return card;
};

int Shoe::getDecksRemaining() {
    // Return decks remaining so player can estimate the true count
    std::cout << m_currentShoe.size() / 52 << " decks remaining \n";
    return (m_currentShoe.size() / 52);
}