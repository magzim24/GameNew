#pragma once
#include <stack>
#include <vector>

#include "card.h"

using namespace std;

class Card;
class GameDeck {
	
private:
	stack<Card*> deck;
	void FillSetCards(vector<Card*>&);
public:
	Card* trump_card;
	GameDeck();
	Card* GetCard();
	void GenerateRandomStack();
	void SetTrumpCard();
	int GetLengthStack();
};