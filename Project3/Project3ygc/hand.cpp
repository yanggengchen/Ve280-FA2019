#include "hand.h"



Hand::Hand() {
// EFFECTS: establishes an empty blackjack hand.
	curValue.count = 0;
	curValue.soft = 0;
}

void Hand::discardAll() {
// MODIFIES: this
// EFFECTS: discards any cards presently held, restoring the state
// of the hand to that of an empty blackjack hand.
	curValue.count = 0;
	curValue.soft = 0;
}

void Hand::addCard(Card c) {
// MODIFIES: this
// EFFECTS: adds the card "c" to those presently held.
	if (c.spot <= TEN) {
		curValue.count = curValue.count + c.spot + 2;
	}
	else if (c.spot <= KING) {
		curValue.count += 10;
	}
	else {
		if (curValue.soft == 1) curValue.count += 1;
		else {
			curValue.count += 11;
			curValue.soft = 1;
		}
	}
}

HandValue Hand::handValue() const {
// EFFECTS: returns the present value of the blackjack hand.  The
// count field is the highest blackjack total possible without
// going over 21.  The soft field should be true if and only if at
// least one ACE is present, and its value is counted as 11 rather
// than 1.  If the hand is over 21, any value over 21 may be returned.
//
// Note: the const qualifier at the end of handValue means that
// you are not allowed to change any member variables inside
// handValue. Adding this prevents the accidental change by you.
	HandValue Best_result;
	if ((curValue.soft == 1) && (curValue.count > 21)) {
		Best_result.soft = 0;
		Best_result.count = curValue.count - 10;
	}
	else Best_result = curValue;
	return Best_result;
}
