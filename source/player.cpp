#include "../include/player.h"

players::player::player() : m_handValue(int(0)) {
};

int players::player::getHandValue() {
    calculateHandValue();
	return m_handValue;
};

void players::player::calculateHandValue() {
    int value = 0;
    int aces = 0;
    for (const auto& card : m_hand) {
        int cardValue = card->getRank();
        if (cardValue >= 10) {
            cardValue = 10;
        }
        else if (cardValue == cards::ace) {
            aces++;
            cardValue = 11;
        }
        value += cardValue;
    }

    while (value > 21 && aces > 0) {
        value -= 10;
        aces--;
    }

    m_handValue = value;
}

void players::player::drawCard(std::unique_ptr<cards::card> p_card) {
	m_hand.push_back(std::move(p_card));
};

players::dealer::dealer() : m_faceUpCard(cards::card(cards::Suit(cards::clubs), cards::Rank(cards::ace))), m_revealHand(bool(false)) {
};

void players::dealer::revealHand() {
	m_revealHand = true;
}

cards::card players::dealer::getFaceUpCard() {
	return m_faceUpCard;
}

void players::dealer::drawCard(std::unique_ptr<cards::card> p_card) {
	if (m_hand.empty())
		m_faceUpCard = *p_card;

	m_hand.push_back(std::move(p_card));
};

int players::dealer::getHandValue() {
    if (m_revealHand) {
        calculateHandValue();
		return m_handValue;
    }

	return -1;
}

players::Decisions players::dealer::makeDecision() {
    calculateHandValue();
    if (m_handValue < 17)
        return players::Decisions::hit;

    return players::Decisions::stand;
}