#include "player.h"

class Simple_Player : public Player {
public:
	Simple_Player(){}
	int bet(unsigned int bankroll, unsigned int minimum) {
	// REQUIRES: bankroll >= minimum
	// EFFECTS: returns the player's bet, between minimum and bankroll 
	// inclusive
		return minimum;
	}
	bool draw(Card dealer, const Hand& player) {
	// EFFECTS: returns true if the player wishes to be dealt another
	// card, false otherwise.
		if (player.handValue().soft == 0) {
			if (player.handValue().count <= 11) return 1;
			else if (player.handValue().count == 12) {
				if ((dealer.spot >= FOUR) && (dealer.spot <= SIX)) return 0;
				else return 1;
			}
			else if (player.handValue().count <= 16) {
				if ((dealer.spot >= TWO) && (dealer.spot <= SIX)) return 0;
				else return 1;
			}
			else return 0;
		}
		else {
			if (player.handValue().count <= 17) return 1;
			else if (player.handValue().count == 18) {
				if ((dealer.spot == TWO) || (dealer.spot == SEVEN) || (dealer.spot == EIGHT))
					return 0;
				else return 1;
			}
			else return 0;
		}
	}
	void expose(Card c){}
	// EFFECTS: allows the player to "see" the newly-exposed card c.
	// For example, each card that is dealt "face up" is expose()d.
	// Likewise, if the dealer must show his "hole card", it is also
	// expose()d.  Note: not all cards dealt are expose()d---if the
	// player goes over 21 or is dealt a natural 21, the dealer need
	// not expose his hole card.
	void shuffled(){}
	// EFFECTS: tells the player that the deck has been re-shuffled.
};


class Counting_Player : public Simple_Player {
	int count;
public:
	Counting_Player() :count(0){}
	int bet(unsigned int bankroll, unsigned int minimum) {
	// REQUIRES: bankroll >= minimum
	// EFFECTS: returns the player's bet, between minimum and bankroll 
	// inclusive
		if ((count >= 2) && (bankroll >= 2 * minimum)) return 2 * minimum;
		else return minimum;
	}
	void expose(Card c) {
	// EFFECTS: allows the player to "see" the newly-exposed card c.
	// For example, each card that is dealt "face up" is expose()d.
	// Likewise, if the dealer must show his "hole card", it is also
	// expose()d.  Note: not all cards dealt are expose()d---if the
	// player goes over 21 or is dealt a natural 21, the dealer need
	// not expose his hole card.
		if (c.spot >= TEN) count--;
		else if (c.spot <= SIX) count++;
	}
	void shuffled() {
	// EFFECTS: tells the player that the deck has been re-shuffled.
		count = 0;
	}
};

static Simple_Player simp_ply;
static Counting_Player cout_ply;
extern Player* get_Simple() {
// EFFECTS: returns a pointer to a "simple player", as defined by the
// project specification
	return &simp_ply;
}

extern Player* get_Counting() {
// EFFECTS: returns a pointer to a "counting player", as defined by
// the project specification.
	return &cout_ply;
}
