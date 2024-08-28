#include "Player.h"

// Player base class

Player::Player() {
    m_aces = 0;
    m_handValue = 0;
    m_softHand = false;
}

void Player::drawCard(std::unique_ptr<Card> p_card) {
    int cardValue = p_card->getRank();
	
    if(cardValue >= 10)
        cardValue = 10;
    
    else if(cardValue == ace) {
        m_aces ++;
        cardValue = 11;
    }

    m_handValue += cardValue;

    m_hand.push_back(std::move(p_card));
    
    return;
};

Decisions Player::makeDecision() {
    if(m_handValue > 21)
        return stand;

    if(m_handValue == 21)
        return stand;
};

Dealer::Dealer() {
    m_upCardValue = 0;
};

Decisions Dealer::makeDecision() {
    if(m_handValue < 17)
        return hit;

    if(m_handValue > 21 && m_aces > 1) {
        m_handValue -= 10;
        m_aces --;

        return hit;
    }

    return stand;
};