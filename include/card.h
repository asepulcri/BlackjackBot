//
// Created by Andrea on 09/06/2023.
//

#ifndef BLACKJACKBOT_CARD_H
#define BLACKJACKBOT_CARD_H

namespace card {
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
}

#endif //BLACKJACKBOT_CARD_H
