#include <iostream>
#include "player.h"
#include "game.h"
#include "card.h"
#include <string>

using namespace ::std;

Card* Player::GetMinTrumpCard(string suit_trump) {
	Card* current_min_trump_card = nullptr;
	for (Card* card : this->set_cards) {
		if (card->suit == suit_trump) {
			string value = card->value;
			if (current_min_trump_card != nullptr) {
				if (Game::value_level.at(current_min_trump_card->value) >
					Game::value_level.at(card->value)) {
					current_min_trump_card = card;
				}
			}
			else current_min_trump_card = card;
		}
	}
	return current_min_trump_card;
}
void Player::TakeCard(Card* inserting_card){
	this->set_cards.push_back(inserting_card);
}
Card* Player::Attack(int index) {
	Card* card = this->set_cards.at(index);
	this->set_cards.erase(this->set_cards.begin() + index);
	return card;
}
bool VectorHasValue(string value, vector<Card*> cards) {
	map<string, bool> values;
	for (Card* card : cards) {
		values[card->value] = true;
	}
	return values.find(value) != values.end();
}
bool VectorHasSuit(string suit, vector<Card*> cards) {
	map<string, bool> suits;
	for (Card* card : cards) {
		suits[card->suit] = true;
	}
	return suits.find(suit) != suits.end();
}
map<int, Card*> Player::GetMapFromSetCards() {
	map<int, Card*> cards = map<int, Card*>();
	for (int i = 0; i < this->set_cards.size(); ++i) {
		cards[i] = this->set_cards[i];
	}
	return cards;
}
map<int, Card*> Player::GetAvailableCardToAttack(vector<Card*> currentCardsInBattle) {
	if (!currentCardsInBattle.empty()) {
		map<int, Card*> cards = map<int, Card*>();
		for (int i = 0; i < this->set_cards.size(); i++) {
			if (VectorHasValue(this->set_cards[i]->value, currentCardsInBattle)) {
				cards[i] = this->set_cards.at(i);
			}
		}
		return cards;
	}
	else {
		return GetMapFromSetCards();
	}
	
}

bool CompareCardsValueByValueLevel(const Card* card, const Card* AttackingCard) {
	if (Game::value_level.at(card->value) > Game::value_level.at(AttackingCard->value)) {
		return true;
	}
	return false;
}

map<int, Card*> Player::GetAvailableCardToDefend(const Card* AttackingCard, const Card* TrumpCard) {
	map<int, Card*> result = map<int, Card*>();
	int i = 0;
	if (AttackingCard->suit == TrumpCard->suit) {
		
		for (Card* card : this->set_cards) {
			if (card->suit == TrumpCard->suit && CompareCardsValueByValueLevel(card, AttackingCard)) {
				result[i] = card;
			}
			i++;
		}
	}
	else {
		for (Card* card : this->set_cards) {
			if ((card->suit == AttackingCard->suit && CompareCardsValueByValueLevel(card, AttackingCard)) || card->suit == TrumpCard->suit) {
				result[i] = card;
			}
			i++;
		}
	}
	
	return result;
}
string Player::getTypeOfPlayer() {
	return string("Player");
}
Action* Player::MakeDecisionAboutAttack(vector<Card*> values, Player* defender) {
	return nullptr;
}
Action* Player::MakeDecisionAboutDefend(Action* action, Card* trump_card) {
	return nullptr;
}
void Player::RemoveCard(int index) {
	if(index < this->set_cards.size())
		this->set_cards.erase(this->set_cards.begin() + index);
}
void Player::RemoveCard(Card* card) {
	auto index = find(this->set_cards.begin(), this->set_cards.end(), card);
	if (index != this->set_cards.end()) {
		this->set_cards.erase(index);
	}
}
int Player::GetLenghtSetCards() {
	return this->set_cards.size();
}