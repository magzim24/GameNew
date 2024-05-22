#include <string>
#include "card.h"

using namespace std;

Card::Card() {}
Card::Card(string suit, string value) {
	this->suit = suit;
	this->value = value;
}

const string* Card::suit_array = new string[4] {
	"Hearts",
	"Spades",
	"Diamonds",
	"Clubs"
};