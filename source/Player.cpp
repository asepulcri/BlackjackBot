#include "Player.h"

// Player base class

Player::Player() {
    m_lastHandIdx = 0;
    m_aces = {0};
    m_handValue = {0};
    m_softHand = {false};
    m_wallet = 10000;
    m_bet = 0;
    m_betSpread = {1, 2, 4, 7, 8, 10, 12};
    addNewHand();
}

void Player::drawCard(int p_hand, std::unique_ptr<Card> p_card) {
    // Draw card from shoe and update running count
    int cardValue = p_card->getRank();

    std::cout << "Player draws " << rankEnumToString(p_card->getRank()) << " of " << suitEnumToString(p_card->getSuit()) << "\n";

    m_hiLo.updateRunningCount(static_cast<Rank> (cardValue));
	
    // Calculate hand value
    if(cardValue >= 10)
        cardValue = 10;
    
    else if(cardValue == ace) {
        m_softHand[p_hand] = true;
        m_aces[p_hand] ++;
        cardValue = 11;
    }

    m_handValue[p_hand] += cardValue;

    while(m_handValue[p_hand] > 21 && m_aces[p_hand] > 0) {
        m_handValue[p_hand] -= 10;
        m_aces[p_hand] --;
    }

    // Add card to hand
    m_hand[p_hand].push_back(std::move(p_card));
    
    return;
};

void Player::addNewHand() {
    // Add new hand when splitting
    m_hand.emplace_back();
}

void Player::splitHand(int p_hand) {
    // Split hand
    m_lastHandIdx ++;
    addNewHand();

    m_hand[m_lastHandIdx].push_back(std::move(m_hand[p_hand][1]));
    m_hand[p_hand].pop_back();
}

void Player::betHand(int p_minimumBet) {
    // Bet hand based on true count
    int trueCount = m_hiLo.getTrueCount();

    if(trueCount < 0) {
        m_bet += p_minimumBet;
    }

    if(trueCount > 6) {
        m_bet += p_minimumBet * m_betSpread.back();
    }

    else {
        m_bet += p_minimumBet * m_betSpread[trueCount];
    }
}

void Player::updateWallet(Outcomes p_outcome) {
    // Update player money based on outcome of hand
    switch(p_outcome) {
        case win:
            m_wallet += 2 * m_bet;
            break;
        
        case lose:
            m_wallet -= m_bet;
            break;

        case push:
            break;
    }

    m_bet = 0;

    return;
}

void Player::updateRunningCount(Rank p_rank) {
    m_hiLo.updateRunningCount(p_rank);
    return;
}

void Player::updateTrueCount(int p_decksRemaining) {
    m_hiLo.updateTrueCount(p_decksRemaining);
    return;
}

void Player::resetHands() {
    // Reset hand
    m_hand.clear();
    m_lastHandIdx = 0;
    m_aces = {0};
    m_handValue = {0};
    m_softHand = {false};
    m_bet = 0;
    addNewHand();
}

void Player::resetCount() {
    m_hiLo.resetCount();
}

int Player::getHandValue(int p_hand) {
    return m_handValue[p_hand];
}

int Player::getLastHandIdx() {
    return m_lastHandIdx;
}

int Player::getBet() {
    return m_bet;
}

int Player::getRunningCount() {
    return m_hiLo.getRunningCount();
}

int Player::getTrueCount() {
    return m_hiLo.getTrueCount();
}

int Player::getWalletAmount() {
    return m_wallet;
}

Decisions Player::makeDecision(int p_hand, Rank p_dealerUpCard) {
    Decisions playerDecision;
    // Stand when at 21 or above
    if(m_handValue[p_hand] > 21)
        playerDecision = stand;

    if(m_handValue[p_hand] == 21)
        playerDecision = stand;

    // Decide whether to split when first two cards are the same rank
    if(m_hand[p_hand][0]->getRank() == m_hand[p_hand][1]->getRank() && m_hand.size() < 4) {
        Decisions splitDecision = pairSplittingDecisions(p_hand, p_dealerUpCard);

        if(splitDecision == split)
            playerDecision = split;
        else
            playerDecision = softTotalsDecisions(p_hand, p_dealerUpCard);
    }

    // Check if current hand is a soft hand
    if(m_softHand[p_hand])
        playerDecision = softTotalsDecisions(p_hand, p_dealerUpCard);

    // If none of the above are triggered then use hard total decision
    playerDecision = hardTotalsDecisions(p_hand, p_dealerUpCard);

    std::cout << decisionsEnumToString(playerDecision) << "\n";

    return playerDecision;
};

Decisions Player::hardTotalsDecisions(int p_hand, Rank p_dealerUpCard) {
    // Basic strategy matrix
    if (m_handValue[p_hand] < 8)
        return hit;

    if (m_handValue[p_hand] > 17)
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

    int totalIndex = m_handValue[p_hand] - int(8);

    int dealerIndex = p_dealerUpCard < 10 ? p_dealerUpCard != ace ? p_dealerUpCard - int(2) : int(9) : int(8);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<Decisions>(decisionToMake);
}

Decisions Player::softTotalsDecisions(int p_hand, Rank p_dealerUpCard) {
    // Basic strategy matrix
    int arr[8][10] = {
        {0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 0, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 2, 2, 0, 0, 0, 0, 0},
        {0, 0, 2, 2, 2, 0, 0, 0, 0, 0},
        {0, 2, 2, 2, 2, 0, 0, 0, 0, 0},
        {2, 2, 2, 2, 2, 1, 1, 0, 0, 0},
        {1, 1, 1, 1, 2, 1, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    int totalIndex = m_handValue[p_hand] - int(13);

    int dealerIndex = p_dealerUpCard < 10 ? p_dealerUpCard != ace ? p_dealerUpCard - int(2) : int(9) : int(8);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<Decisions>(decisionToMake);
}

Decisions Player::pairSplittingDecisions(int p_hand, Rank p_dealerUpCard) {
    // Basic strategy matrix
    int arr[10][10] = {
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {1, 3, 3, 3, 3, 3, 3, 1, 1, 1},
        {1, 3, 3, 3, 3, 3, 3, 1, 1, 1},
        {1, 1, 1, 1, 3, 3, 1, 1, 1, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1},
        {1, 3, 3, 3, 3, 3, 1, 1, 1, 1},
        {1, 3, 3, 3, 3, 3, 3, 1, 1, 1},
        {3, 3, 3, 3, 3, 3, 3, 3, 3, 3},
        {1, 3, 3, 3, 3, 3, 1, 3, 3, 1},
        {1, 1, 1, 1, 1, 1, 1, 1, 1, 1}};

    int rankCard = m_hand[p_hand][0]->getRank();

    int totalIndex = rankCard < 10 ? rankCard - 1 : int(9);

    int dealerIndex = p_dealerUpCard < 10 ? p_dealerUpCard - 1 : int(9);

    int decisionToMake = arr[totalIndex][dealerIndex];

    return static_cast<Decisions>(decisionToMake);
}

Dealer::Dealer() {
    m_handValue = 0;
    m_softHand = false;
    m_aces = 0;
};

Decisions Dealer::makeDecision() {
    // Dealer hits below 17 and stands if 17 or higher
    Decisions dealerDecision;

    dealerDecision = m_handValue < 17 ? hit : stand;

    std::cout << decisionsEnumToString(dealerDecision) << "\n";

    return dealerDecision;
};

Rank Dealer::drawCard(std::unique_ptr<Card> p_card) {
    // Draw dealer card
    int cardValue = p_card->getRank();

    std::cout << "Dealer draws " << rankEnumToString(p_card->getRank()) << " of " << suitEnumToString(p_card->getSuit()) << "\n";

    // Give up card rank for player to make decisions
    if(m_hand.empty()) {
        m_upCardRank = static_cast<Rank> (cardValue);
    }

	// Calculate hand value
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

    // Add card to hand
    m_hand.push_back(std::move(p_card));
    
    // Return card rank so player can update running count
    return static_cast<Rank>(cardValue);
};

void Dealer::resetHand() {
    // Reset hand
    m_hand.clear();
    m_handValue = 0;
    m_softHand = false;
    m_aces = 0;
}

int Dealer::getHandValue() {
    return m_handValue;
}

Rank Dealer::getUpCardRank() {
    return m_upCardRank;
}