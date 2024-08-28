//
// Created by Andrea on 11/06/2023.
//

#include "Card.h"
#include "Shoe.h"
#include <vector>
#include <memory>
#include <iostream>

#pragma once

enum Decisions {
	hit,
	stand,
	doubledown,
	split,
	surrender
};

static std::vector<std::string> decisionNames = {"hit", "stand", "double down", "split", "surrender"};

class Person {
protected:
	Person();
	std::vector<std::unique_ptr<Card>> m_hand;
	int m_handValue;
	bool m_softHand;

public:
	void showHand();
	void showLastDrawnCard();
	int getHandValue();
	void calculateHandValue();
	void drawCard(std::unique_ptr<Card> p_card);
	void clearHand();
};

class Player : public Person {
protected:
	int m_wallet;

public:
	Player(int p_buyIn);

	int getWalletValue();
	void betHand(int p_betValue);
	void winMoney(int p_betValue);

	Decisions makeDecision(Card p_dealerUpCard);
	Decisions hardTotalsDecisions(Card p_dealerUpCard);
	Decisions softTotalsDecisions(Card p_dealerUpCard);
	Decisions pairSplittingDecisions(Card p_dealerUpCard);
};


class Dealer : public Person {
private:
	Card m_faceUpCard;
	bool m_revealHand;

public:
	Dealer();

	void revealHand();
	void drawCard(std::unique_ptr<Card> p_card);
	int getHandValue();
	Card getFaceUpCard();
	void showFaceUpCard();

	Decisions makeDecision();
};