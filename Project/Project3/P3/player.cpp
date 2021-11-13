#include "player.h"

class Simpleplayer :public Player {
public:
	virtual int bet(unsigned int bankroll, unsigned int minimum);
	// REQUIRES: bankroll >= minimum
 	// EFFECTS: returns the player's bet, between minimum and bankroll
 	// inclusive


	bool draw(Card dealer, const Hand& player);
	// EFFECTS: returns true if the player wishes to be dealt another
 	// card, false otherwise.

	virtual void expose(Card c);
	// EFFECTS: allows the player to "see" the newly-exposed card c.

	virtual void shuffled();
	// EFFECTS: tells the player that the deck has been re-shuffled.
};

int Simpleplayer::bet(unsigned int bankroll, unsigned int minimum) {
	// REQUIRES: bankroll >= minimum
	// EFFECTS: returns the player's bet, between minimum and bankroll
	// inclusive
	return minimum;
}

bool Simpleplayer::draw(Card dealer, const Hand& player) {
	// EFFECTS: returns true if the player wishes to be dealt another
	// card, false otherwise.
	if (player.handValue().soft == false) {
		// hard count
		if (player.handValue().count <= 11) {
			// If the player’s hand totals 11 or less, he always hits
			return true;
		}
		else if (player.handValue().count == 12) {
			// If the player’s hand totals 12
			if (dealer.spot == FOUR || dealer.spot == FIVE || dealer.spot == SIX) {
				// he stands if the dealer shows 4, 5, or 6
				return false;
			}
			else {
				// otherwise he hits
				return true;
			}
		}
		else if (player.handValue().count >= 13 && player.handValue().count <= 16) {
			// If the player’s hand totals between 13 and 16 inclusive
			if (dealer.spot >= TWO && dealer.spot <= SIX) {
				// he stands if the dealer shows a 2 through a 6 inclusive
				return false;
			}
			else {
				// otherwise he hits
				return true;
			}
		}
		else {
			// If the player's hand totals 17 or greater, he always stands
			return false;
		}
	}
	else {
		// soft count
		if (player.handValue().count <= 17) {
			// If the player’s hand totals 17 or less, he always hits.
			return true;
		}
		else if (player.handValue().count == 18) {
			// If the player’s hand totals 18
			if (dealer.spot == TWO || dealer.spot == SEVEN || dealer.spot == EIGHT) {
				// he stands if the dealer shows a 2, 7, or 8
				return false;
			}
			else {
				// otherwise he hits
				return true;
			}
		}
		else {
			// If the player’s hand totals 19 or greater, he always stands
			return false;
		}
	}
}

void Simpleplayer::expose(Card c) {
	// EFFECTS: allows the player to "see" the newly-exposed card c.
}

void Simpleplayer::shuffled() {
	// EFFECTS: tells the player that the deck has been re-shuffled.
}

class Countingplayer :public Simpleplayer {
private:
	int count;
public:
	int bet(unsigned int bankroll, unsigned int minimum);
	// REQUIRES: bankroll >= minimum
 	// EFFECTS: returns the player's bet, between minimum and bankroll
 	// inclusive

	void expose(Card c);
	// EFFECTS: allows the player to "see" the newly-exposed card c.
	
	void shuffled();
	// EFFECTS: tells the player that the deck has been re-shuffled.
};

int Countingplayer::bet(unsigned int bankroll, unsigned int minimum) {
	// REQUIRES: bankroll >= minimum
	// EFFECTS: returns the player's bet, between minimum and bankroll
	// inclusive
	if (count >= 2 && bankroll >= 2 * minimum) {
		return 2 * minimum;
	}
	else {
		return minimum;
	}
}

void Countingplayer::expose(Card c) {
	// EFFECTS: allows the player to "see" the newly-exposed card c.
	if (c.spot == TEN || c.spot == JACK || c.spot == QUEEN || c.spot == KING || c.spot == ACE) {
		count--;
	}
	else if (c.spot == TWO || c.spot == THREE || c.spot == FOUR || c.spot == FIVE || c.spot == SIX) {
		count++;
	}
}

void Countingplayer::shuffled() {
	// EFFECTS: tells the player that the deck has been re-shuffled.
	count = 0;
}

Player* get_Simple() {
	return (Player*) new Simpleplayer();
}

Player* get_Counting() {
	return (Player*) new Countingplayer();
}