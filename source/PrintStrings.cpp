#include "PrintStrings.h"

std::map<Decisions, std::string> decisionsToString = {{hit, 			"Hit"},
													  {stand, 		    "Stand"},
													  {doubledown, 		"Double down"},
													  {split, 			"Split"},
													  {surrender, 		"Surrender"}};

std::map<Outcomes, std::string> outcomesToString = {{lose, "You lost"},
											        {win,  "You won"},
													{push, "Push"}};

std::map<Rank, std::string> rankToString = {{ace, "ace"},
                                            {two, "two"},
                                            {three, "three"},
                                            {four, "four"},
                                            {five, "five"},
                                            {six, "six"},
                                            {seven, "seven"},
                                            {eight, "eight"},
                                            {nine, "nine"},
                                            {ten, "ten"},
                                            {jack, "jack"},
                                            {queen, "queen"},
                                            {king, "king"}};

std::map<Suit, std::string> suitToString = {{clubs,    "clubs"},
                                            {diamonds, "diamonds"},
                                            {hearts,   "hearts"},
                                            {spades,   "spades"}};

std::string suitEnumToString(Suit suit) { return suitToString[suit]; }

std::string outcomesEnumToString(Outcomes outcome) { return outcomesToString[outcome]; }

std::string rankEnumToString(Rank rank) { return rankToString[rank]; }

std::string decisionsEnumToString(Decisions decision) {	return decisionsToString[decision]; }