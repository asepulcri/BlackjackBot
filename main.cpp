#include <iostream>
#include "shoe.h"

int main() {
    card::card testCard((card::Suit(card::Suit::clubs)), card::Rank(11));

    shoe::shoe testShoe(int(3));

    testShoe.shuffleShoe();

    return 0;
}
