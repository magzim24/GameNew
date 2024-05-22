#pragma once
#include <vector>
#include <map>
#include <string>
#include "card.h"
#include "action.h"
using namespace ::std;



enum TypePlayer
{
	User_t,
	Bot_t
};
class Action;
class Player {
		
private:
	vector<Card*> set_cards;
	map<int, Card*> GetMapFromSetCards();
public:
	string Name;
	TypePlayer type;
	void TakeCard(Card*);
	Card* GetMinTrumpCard(string suit_trump);
	Card* Attack(int);
	map<int, Card*> GetAvailableCardToAttack(vector<Card*>);
	virtual string getTypeOfPlayer();
	virtual Action* MakeDecisionAboutAttack(vector<Card*>, Player*);
	virtual  Action* MakeDecisionAboutDefend(Action* action, Card* trump_card);
	void RemoveCard(int);
	void RemoveCard(Card*);
	map<int, Card*> GetAvailableCardToDefend(const Card*, const Card*);
	int GetLenghtSetCards();
};

