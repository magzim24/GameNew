#include <string>
#include "bot.h"
#include "action.h"
using namespace ::std;

int Bot::id = 1;
Bot::Bot() {
	this->setName();
	type = TypePlayer::Bot_t;
}
void Bot::setName() {
	this->Name = string("Bot");// + Bot::id
	//Bot::id++;
}
Action* Bot::MakeDecisionAboutAttack(vector<Card*> cardsInBattle, Player* defender) {
	map<int, Card*> availableCards = this->GetAvailableCardToAttack(cardsInBattle);
	if (availableCards.empty()) {
		return nullptr;
	}
	else {
		int max = availableCards.size();
		int min = 0;
		int random_num = rand() % (max - min + 1) + min;
		if (random_num == max) {
			return nullptr;
		}
		else {
			Action* action = new Action(this, defender, next(availableCards.begin(), random_num)->second);
			this->RemoveCard(random_num);
			return action;
		}
	}
}

Action* Bot::MakeDecisionAboutDefend(Action* action, Card* trump_card) {
	map<int, Card*> availableCards = this->GetAvailableCardToDefend(action->GetAttackingCard(), trump_card);
	if (availableCards.empty()) {
		action->SetDefendingCard(nullptr);
	}
	else {
		int max = availableCards.size();
		int min = 0;
		int random_num = rand() % (max - min + 1) + min;
		if (random_num == max) {
			action->SetDefendingCard(nullptr);
		}
		else {
			action->SetDefendingCard(next(availableCards.begin(), random_num)->second);
			this->RemoveCard(random_num);
		}
	}
	return action;
}
