#pragma once
#include <vector>
#include "card.h"
using namespace ::std;

class CardsOnDesk {
private:
	vector<Card*> container;
public:
	CardsOnDesk(vector<Card*>);
	CardsOnDesk();
	const vector<Card*>& GetCardsOnDesk();
	void Clear();
};