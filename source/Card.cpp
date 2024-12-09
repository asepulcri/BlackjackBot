#include "Card.h"

Card::Card(Suit cardSuit, Rank cardRank) : m_suit(cardSuit), m_rank(cardRank) {};

// Getters
Suit Card::getSuit() {
    return m_suit;
};

Rank Card::getRank() {
    return m_rank;
};