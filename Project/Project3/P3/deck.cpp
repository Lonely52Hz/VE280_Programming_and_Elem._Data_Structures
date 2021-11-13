#include "deck.h"

Deck::Deck() {
	// EFFECTS: constructs a "newly opened" deck of cards. first the
 	// spades from 2 to A, then the hearts, then the clubs, then the
 	// diamonds. The first card dealt should be the 2 of Spades.
	reset();
}

void Deck::reset() {
	// EFFECTS: constructs a "newly opened" deck of cards. first the
 	// spades from 2 to A, then the hearts, then the clubs, then the
 	// diamonds. The first card dealt should be the 2 of Spades.
	for (int i = 0; i < 4; ++i) {
		for (int j = 0; j < 13; ++j) {
			int index = i * 13 + j;
			deck[index].spot = (Spot)j;
			deck[index].suit = (Suit)i;
		}
	}
	next = 0;
}

void Deck::shuffle(int n) {
	// REQUIRES: n is between 0 and 52, inclusive.
 	// MODIFIES: this
 	// EFFECTS: cut the deck into two segments: the first n cards,
 	// called the "left", and the rest called the "right". Note that
 	// either right or left might be empty. Then, rearrange the deck
 	// to be the first card of the right, then the first card of the
 	// left, the 2nd of right, the 2nd of left, and so on. Once one
	// side is exhausted, fill in the remainder of the deck with the
	// cards remaining in the other side. Finally, make the first
	// card in this shuffled deck the next card to deal. For example,
	// shuffle(26) on a newly-reset() deck results in: 2-clubs,
 	// 2-spades, 3-clubs, 3-spades ... A-diamonds, A-hearts.
	Card temp[DeckSize];
	for (int i = 0; i < DeckSize; ++i) {
		temp[i] = deck[i];
	}
	if (n <= 26) {
		for (int i = 0; i < n; ++i) {
			deck[2 * i] = temp[n + i];
			deck[2 * i + 1] = temp[i];
		}
	}
	else {
		for (int i = 0; i < DeckSize - n; ++i) {
			deck[2 * i] = temp[n + i];
			deck[2 * i + 1] = temp[i];
		}
		for (int i = 0; i < DeckSize - 2 * (DeckSize - n); ++i) {
			deck[2 * (DeckSize - n) + i] = temp[DeckSize - n + i];
		}
	}
	next = 0;
}

Card Deck::deal() {
	// MODIFIES: this
 	// EFFECTS: returns the next card to be dealt. If no cards
 	// remain, throws an instance of DeckEmpty.
	DeckEmpty deckEmpty;
	if (next < DeckSize) {
		return deck[next++];
	}
	else {
		throw deckEmpty;
	}
}

int Deck::cardsLeft() {
	// EFFECTS: returns the number of cards in the deck that have not
 	// been dealt since the last reset/shuffle.
	return DeckSize - next;
}