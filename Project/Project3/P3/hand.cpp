#include "hand.h"

Hand::Hand() {
	// EFFECTS: establishes an empty blackjack hand.
	discardAll();
}

void Hand::discardAll() {
	// MODIFIES: this
 	// EFFECTS: discards any cards presently held, restoring the state
 	// of the hand to that of an empty blackjack hand.
	curValue.count = 0;
	curValue.soft = false;
}

void Hand::addCard(Card c) {
	// MODIFIES: this
 	// EFFECTS: adds the card "c" to those presently held.
	switch (c.spot) {
	case TWO:
	case THREE:
	case FOUR:
	case FIVE:
	case SIX:
	case SEVEN:
	case EIGHT:
	case NINE:
	case TEN:
		curValue.count += c.spot + 2;
		break;
	case JACK:
	case QUEEN:
	case KING:
		curValue.count += 10;
		break;
	case ACE:
		if (curValue.soft) {
			curValue.count++;
		}
		else if (curValue.count + 11 <= 21) {
			curValue.count += 11;
			curValue.soft = true;
		}
		else {
			curValue.count++;
		}
		break;
	}
	if (curValue.count > 21 && curValue.soft) {
		curValue.count -= 10;
		curValue.soft = false;
	}
}

HandValue Hand::handValue() const {
	// EFFECTS: returns the present value of the blackjack hand. The
 	// count field is the highest blackjack total possible without
 	// going over 21. The soft field should be true if and only if at
 	// least one ACE is present, and its value is counted as 11 rather
 	// than 1. If the hand is over 21, any value over 21 may be
 	// returned.
	return curValue;
}