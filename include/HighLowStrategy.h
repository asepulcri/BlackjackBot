#include "Card.h"
#include "Shoe.h"

#pragma once

class HighLowStrategy {
    private:
        int m_runningCount;
        int m_trueCount;
    
    public:
        HighLowStrategy();

        void updateRunningCount(Rank p_rank);
        void updateTrueCount(Shoe p_shoe);
        int getRunningCount();
        int getTrueCount();
};