//
// Created by Andrea on 08/06/2023.
//
#ifndef BLACKJACKBOT_SHOEGENERATOR_H
#define BLACKJACKBOT_SHOEGENERATOR_H

#include <iostream>

namespace shoe {
    enum Suit {
        clubs = 0,
        diamonds = 1,
        hearts = 2,
        spades = 3
    };

    enum Rank {
        ace = 0,
        jack = 10,
        queen = 11,
        king = 12
    };

    class card {
    private:
        Suit m_suit;
        Rank m_rank;

    public:
        card(Suit cardSuit, Rank cardRank): m_suit(cardSuit), m_rank(cardRank) {}

        Suit getSuit() const {
            return m_suit;
        }

        Rank getRank() const {
            return m_rank;
        }
    };

    class shoe {
    private:
        int m_size;

    public:
        shoe(int shoeSize): m_size(shoeSize) {}

    };
}

#endif //BLACKJACKBOT_SHOEGENERATOR_H
