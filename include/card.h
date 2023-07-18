//
// Created by Andrea on 09/06/2023.
//

#include <vector>
#include <string>
#ifndef BLACKJACKBOT_CARD_H
#define BLACKJACKBOT_CARD_H

#pragma once

namespace cards {
    enum Suit {
        clubs = 0,
        diamonds = 1,
        hearts = 2,
        spades = 3
    };

    enum Rank {
        ace = 1,
        two,
        three,
        four,
        five,
        six,
        seven,
        eight,
        nine,
        ten,
        jack,
        queen,
        king
    };

    static std::vector<std::string> suitNames = {"clubs", "diamonds", "hearts", "spades"};
    static std::vector<std::string> rankNames = {"ace", "two", "three", "four", "five", "six", "seven", "eight", "nine", "ten", "Jack", "Queen", "King"};

    class card {
    private:
        Suit m_suit;
        Rank m_rank;

    public:
        card(Suit cardSuit, Rank cardRank);

        Suit getSuit();
        Rank getRank();
    };
}

#endif //BLACKJACKBOT_CARD_H
