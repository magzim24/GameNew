#pragma once
#include <string>
#include "deck.h"
using namespace ::std;


class Card {
public:
	string suit;
	string value;
	static const string* suit_array;
	Card(string suit, string value);
	Card();
};