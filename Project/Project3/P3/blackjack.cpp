#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <cassert>
#include "card.h"
#include "deck.h"
#include "hand.h"
#include "player.h"
#include "rand.h"

using namespace std;

const int MINIMUM_BET = 5; // We assume that the minimum bet is 5

Player* settype(const string playertype);
// EFFECTS: return the correct player type based on the argument

void shuffle(Deck& deck, Player* player);
// EFFECTS: shuffle the deck
// MODIFES: deck, player

void firstfourcard(Deck& deck, Hand& playerhand, Hand& dealerhand, Player* player, Card& dealerupcard, Card& holecard);
// EFFECTS: deal the first four cards
// MODIFES: deck, playerhand, dealerhand, player, dealerupcard, holecard

void playerdraw(Deck& deck, Hand& playerhand, Player* player);
// EFFECTS: player draw the card
// MODIFES: deck, playerhand, player

void dealerdraw(Deck& deck, Hand& dealerhand, Player* player);
// EFFECTS: dealer draw the card
// MODIFES: deck, dealerhand, player

void win(Hand& playerhand, Hand& dealerhand, int& bankroll, int& wager);
// EFFECTS: judge who will win, and cout the corresponding message, and change bankroll
// MODIFES: bankroll

int main(int argc, char* argv[]) {
	int bankroll, hands, wager, thishand;
	string playertype;
	Player* player = NULL;
	Deck deck;
	Hand playerhand, dealerhand;
	Card holecard, dealerupcard;
	thishand = 0;
	bankroll = atoi(argv[1]);
	hands = atoi(argv[2]);
	playertype = argv[3];
	player = settype(playertype);// set playertype
	shuffle(deck, player);// shuffle the deck
	while (bankroll >= MINIMUM_BET && thishand < hands) {
		thishand++;
		playerhand.discardAll();
		dealerhand.discardAll();
		cout << "Hand " << thishand << " bankroll " << bankroll << endl;
		if (deck.cardsLeft() < 20) {
			shuffle(deck, player);// If there are fewer than 20 cards left, reshuffle the deck as described above
		}
		wager = player->bet(bankroll, MINIMUM_BET);
		cout << "Player bets " << wager << endl;
		firstfourcard(deck, playerhand, dealerhand, player, dealerupcard, holecard);//deal the first four cards
		if (playerhand.handValue().count == 21) {
			bankroll += 3 * wager / 2 ;
			cout << "Player dealt natural 21\n";
		}
		else {
			while (player->draw(dealerupcard, playerhand) && playerhand.handValue().count <= 21) {
				playerdraw(deck, playerhand, player); // If the player is not dealt a natural 21, have the player play his hand. Draw cards until the player either stands or busts.
			}
			cout << "Player's total is " << playerhand.handValue().count << endl;
			if (playerhand.handValue().count > 21) {
				cout << "Player busts\n";
				bankroll -= wager;
			}
			else {
				cout << "Dealer's hole card is " << SpotNames[holecard.spot] << " of " << SuitNames[holecard.suit] << endl;
				player->expose(holecard);
				while (dealerhand.handValue().count < 17) {
					dealerdraw(deck, dealerhand, player); // The dealer must hit until reaching seventeen or busting
				}
				cout << "Dealer's total is " << dealerhand.handValue().count << endl;
				if (dealerhand.handValue().count > 21) {
					cout << "Dealer busts\n";
					bankroll += wager;
				}
				else {
					win(playerhand, dealerhand, bankroll, wager); //judge who will win
				}
			}
		}
	}
	cout << "Player has " << bankroll << " after " << thishand << " hands\n";
	return 0;
}

Player* settype(const string playertype) {
	// EFFECTS: return the correct player type based on the argument
	if (playertype == "simple") {
		return get_Simple();
	}
	else {
		return get_Counting();
	}
}

void shuffle(Deck& deck, Player* player) {
	// EFFECTS: shuffle the deck
	// MODIFES: deck, player
	cout << "Shuffling the deck\n";
	for (int i = 0; i < 7; ++i) {
		int cut = get_cut();
		cout << "cut at " << cut << endl;
		deck.shuffle(cut);
		player->shuffled();
	}
}

void firstfourcard(Deck& deck, Hand& playerhand, Hand& dealerhand, Player* player, Card& dealerupcard, Card& holecard) {
	// EFFECTS: deal the first four cards
	// MODIFES: deck, playerhand, dealerhand, player, dealerupcard, holecard
	Card newcard;
	// one face-up to the player
	newcard = deck.deal();
	cout << "Player dealt " << SpotNames[newcard.spot] << " of " << SuitNames[newcard.suit] << endl;
	playerhand.addCard(newcard);
	player->expose(newcard);
	// one face-up to the dealer
	newcard = deck.deal();
	dealerupcard = newcard;
	cout << "Dealer dealt " << SpotNames[newcard.spot] << " of " << SuitNames[newcard.suit] << endl;
	dealerhand.addCard(newcard);
	player->expose(newcard);
	// one face-up to the player
	newcard = deck.deal();
	cout << "Player dealt " << SpotNames[newcard.spot] << " of " << SuitNames[newcard.suit] << endl;
	playerhand.addCard(newcard);
	player->expose(newcard);
	// one face-down to the dealer
	newcard = deck.deal();
	holecard = newcard;
	dealerhand.addCard(newcard);
}

void playerdraw(Deck& deck, Hand& playerhand, Player* player) {
	// EFFECTS: player draw the card
	// MODIFES: deck, playerhand, player
	Card newcard;
	newcard = deck.deal();
	cout << "Player dealt " << SpotNames[newcard.spot] << " of " << SuitNames[newcard.suit] << endl;
	playerhand.addCard(newcard);
	player->expose(newcard);
}

void dealerdraw(Deck& deck, Hand& dealerhand, Player* player) {
	// EFFECTS: dealer draw the card
	// MODIFES: deck, dealerhand, player
	Card newcard;
	newcard = deck.deal();
	cout << "Dealer dealt " << SpotNames[newcard.spot] << " of " << SuitNames[newcard.suit] << endl;
	dealerhand.addCard(newcard);
	player->expose(newcard);
}

void win(Hand& playerhand, Hand& dealerhand, int& bankroll, int& wager) {
	// EFFECTS: judge who will win, and cout the corresponding message, and change bankroll
	// MODIFES: bankroll
	if (playerhand.handValue().count > dealerhand.handValue().count) {
		cout << "Player wins\n";
		bankroll += wager;
	}
	else if (playerhand.handValue().count < dealerhand.handValue().count) {
		cout << "Dealer wins\n";
		bankroll -= wager;
	}
	else {
		cout << "Push\n";
	}
}