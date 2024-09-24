#pragma once

enum Decisions {
	hit,
	stand,
	doubledown,
	split,
	surrender
};

enum Outcomes {
	lose,
	win,
	push,
    undetermined
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

enum Suit {
    clubs = 0,
    diamonds = 1,
    hearts = 2,
    spades = 3
};