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
        m_softHand = true;
        m_aces ++;
        cardValue = 11;
    }

    m_handValue += cardValue;

    while(m_handValue > 21 && m_aces > 0) {
        m_handValue -= 10;
        m_aces --;
    }

    m_hand.push_back(std::move(p_card));
    
    return;
};

Decisions Player::makeDecision(Rank p_dealerUpCard) {
    if(m_handValue > 21)
        return stand;

    if(m_handValue == 21)
        return stand;

    if(m_hand[0]->getRank() == m_hand[1]->getRank()) {
        Decisions splitDecision = pairSplittingDecisions(p_dealerUpCard);

        if(splitDecision == split)
            return split;
        else
            return softTotalsDecisions(p_dealerUpCard);
    }


    if(m_softHand)
        return softTotalsDecisions(p_dealerUpCard);

    return hardTotalsDecisions(p_dealerUpCard);
};

Decisions Player::hardTotalsDecisions(Rank p_dealerUpCard) {
    if (m_handValue < 8)
        return hit;

    if (m_handValue > 17)
        return stand;
    
    int arr[10][10] = {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 2, 2, 2, 2, 0, 0, 0, 0, 0},
        {2, 2, 2, 2, 2, 2, 2, 2, 0, 0},
        {2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1} };

    int totalIndex = m_handValue - int(8);

    int dealerIndex = p_dealerUpCard < 10 ? p_dealerUpCard != ace ? p_dealerUpCard - int(2) : int(9) : int(8);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<Decisions>(decisionToMake);
}

Decisions Player::softTotalsDecisions(Rank p_dealerUpCard) {

    int arr[8][10] = {
        {0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 2, 2, 0, 0, 0, 0, 0},
        {0, 2, 2, 2, 2, 0, 0, 0, 0, 0},
        {2, 2, 2, 2, 2, 1, 1, 0, 0, 0},
        {1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    int totalIndex = m_handValue - int(13);

    int dealerIndex = p_dealerUpCard < 10 ? p_dealerUpCard != ace ? p_dealerUpCard - int(2) : int(9) : int(8);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<Decisions>(decisionToMake);
}

Decisions Player::pairSplittingDecisions(Rank p_dealerUpCard) {
    if (m_handValue < 8)
        return hit;

    if (m_handValue > 17)
        return stand;

    int arr[10][10] = {
        {3, 3, 3, 3, 3, 3, 1, 1, 1, 1},
        {3, 3, 3, 3, 3, 3, 1, 1, 1, 1},
        {1, 1, 1, 3, 3, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {3, 3, 3, 3, 3, 1, 1, 1, 1, 1},
        {3, 3, 3, 3, 3, 3, 1, 1, 1, 1},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {3, 3, 3, 3, 3, 1, 3, 3, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3}};

    int totalIndex = m_handValue / int(2) - int(2);

    int dealerIndex = p_dealerUpCard < 10 ? p_dealerUpCard != ace ? p_dealerUpCard - int(2) : int(9) : int(8);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<Decisions>(decisionToMake);
}

Dealer::Dealer() {
};

Decisions Dealer::makeDecision() {
    if(m_handValue < 17)
        return hit;

    return stand;
};

void Dealer::checkUpCard() {
    m_upCardRank = m_hand[1]->getRank();
}

Rank Dealer::getUpCard() {
    return m_upCardRank;
}