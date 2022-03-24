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

void deck_shuffle(Deck* deck, Player* player) {
//MODIFIES: deck;
//EFFECTS: shuffle the deck, print the message, and tells the player that the deck is shuffled.
	int cut = get_cut();
	cout << "cut at " << cut << endl;
	deck->shuffle(cut);
	player->shuffled();
}

void deal_card(Deck* deck, Player* player, Hand* hand_player, Hand* hand_dealer, Card* card) {
//MODIFIES: this
//EFFECTS: deal four cards to the player and dealer according to the rules, and print corrsponding messages
	for (int i = 0; i < 4; i++) { //deals card
		card[i] = deck->deal();
		if ((i == 0) || (i == 2)) {
			player->expose(card[i]);
			hand_player->addCard(card[i]);
			cout << "Player dealt " << SpotNames[card[i].spot] << " of " << SuitNames[card[i].suit] << endl;
		}
		else {
			hand_dealer->addCard(card[i]);
			if (i == 1) {
				cout << "Dealer dealt " << SpotNames[card[i].spot] << " of " << SuitNames[card[i].suit] << endl;
				player->expose(card[i]);
			}
		}
	}
}

void dealer_turn(Deck* deck, Player* player, Hand* hand_player, Hand* hand_dealer, Card* card) {
//MODIFIES: this
//EFFECTS: let the dealer play his hand, tell the exposed card to the player, and print corrsponding messages
	while (hand_dealer->handValue().count < 17) {
		Card temp = deck->deal();
		hand_dealer->addCard(temp);
		player->expose(temp);
		cout << "Dealer dealt " << SpotNames[temp.spot] << " of " << SuitNames[temp.suit] << endl;
	}
	cout << "Dealer's total is " << hand_dealer->handValue().count << endl;
}

void player_turn(Deck* deck, Player* player, Hand* hand_player, Card* card) {
//MODIFIES: this
//EFFECTS:let the player play his hand according to the alogorithem
	while (player->draw(card[1], *hand_player) == 1) {
		Card temp = deck->deal();
		hand_player->addCard(temp);
		player->expose(temp);
		cout << "Player dealt " << SpotNames[temp.spot] << " of " << SuitNames[temp.suit] << endl;
	}
	cout << "Player's total is " << hand_player->handValue().count << endl;
}

void compare_results(Hand* hand_player, Hand* hand_dealer, int* bankroll, int* wager) {
//MODIFIES: bankroll
//EFFECTS: compare the count of player's hand and dealer's hand, and operate bankroll correspondingly
	if (hand_player->handValue().count > hand_dealer->handValue().count) {
		*bankroll = *bankroll + *wager;
		cout << "Player wins\n";
	}
	else if (hand_player->handValue().count < hand_dealer->handValue().count) {
		*bankroll = *bankroll - *wager;
		cout << "Dealer wins\n";
	}
	else {
		cout << "Push\n";
	}
}

int main(int argc, char* argv[]) {
//MODIFIES: this
//EFFECTS: implement the driver
	/*char simple[7] = "simple";
	int bankroll = atoi(argv[1]);
	int hands = atoi(argv[2]);
	Player* player;
	if (argv[3] == simple) player = get_Simple();
	else player = get_Counting();*/
	int bankroll = 100;
	int hands = 60;
	Player* player = get_Counting();
	Deck deck;
	//initial shuffling
	cout << "Shuffling the deck\n";
	for (int i = 0; i < 7; i++) {
		deck_shuffle(&deck, player);
	}
	int thishand = 0;
	while ((bankroll >= 5) && (thishand < hands)) {
		Card card[4]; //the four cards used in every hand
		Hand hand_player; //the hand of the player
		Hand hand_dealer;//dealer's hand
		//initial preparation
		thishand++;
		cout << "Hand " << thishand << " bankroll " << bankroll << endl;
		if (deck.cardsLeft() < 20) {
			cout << "Shuffling the deck\n";
			for (int i = 0; i < 7; i++) {
				deck_shuffle(&deck, player);
			}
		}
		int wager = player->bet(bankroll, 5); //player bets
		cout << "Player bets " << wager << endl; 
		deal_card(&deck, player, &hand_player, &hand_dealer, card); //deal the initial four cards
		if (hand_player.handValue().count == 21) { //player has dealt a natural 21
			bankroll = bankroll + 3 * wager / 2;
			cout << "Player dealt natural 21\n";
			continue;
		}
		player_turn(&deck, player, &hand_player, card); //player plays his hand
		if (hand_player.handValue().count > 21) { //judge whether player busts
			cout << "Player busts\n";
			bankroll = bankroll - wager;
			continue;
		}
		player->expose(card[3]); //expose dealer's hole card
		cout << "Dealer's hole card is " << SpotNames[card[3].spot] << " of " << SuitNames[card[3].suit] << endl;
		dealer_turn(&deck, player, &hand_player, &hand_dealer, card); //dealer play his hand
		if (hand_dealer.handValue().count > 21) { //judge whether dealer busts
			cout << "Dealer busts\n";
			bankroll = bankroll + wager;
			continue;
		}
		compare_results(&hand_player, &hand_dealer, &bankroll, &wager); //compare player's value and dealer's value
	}
	cout << "Player has " << bankroll << " after " << thishand << " hands\n";
}