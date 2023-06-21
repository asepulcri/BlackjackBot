#include "../include/card.h"

cards::card::card(cards::Suit cardSuit, cards::Rank cardRank) : m_suit(cardSuit), m_rank(cardRank) {};

cards::Suit cards::card::getSuit() {
    return m_suit;
};

cards::Rank cards::card::getRank() {
    return m_rank;
};

