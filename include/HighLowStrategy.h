#include "Card.h"
#include "EnumNames.h"
#include "Shoe.h"

#pragma once

class HighLowStrategy {
    private:
        int m_runningCount;
        int m_trueCount;

    public:
        HighLowStrategy();

        void updateRunningCount(Rank p_rank);
        void updateTrueCount(int p_decksRemaining);
        int getRunningCount();
        int getTrueCount();
};