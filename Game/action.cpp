#pragma once
#include "action.h"
#include "player.h"
#include "card.h"
#include "game.h"

Action::Action(Player* attacker, Player* defender, Card* attacker_card) {
	this->attacker_card = attacker_card;
	this->defending_card = nullptr;
}
bool Action::IsRepulsed(Card* TrumpCard) {
	if (this->attacker_card->suit != TrumpCard->suit) {
		if ((Game::value_level.at(this->defending_card->value) > Game::value_level.at(this->attacker_card->value) &&
			this->defending_card->suit == this->attacker_card->suit) || this->defending_card->suit == TrumpCard->suit) {
			return true;
		}
		return false;
	}
	else {
		if (Game::value_level.at(this->defending_card->value) > Game::value_level.at(this->attacker_card->value) &&
			this->defending_card->suit == this->attacker_card->suit) {
			return true;
		}
		return false;
	}
	
}
void Action::SetDefendingCard(Card* card) {
	this->defending_card = card;
}
Card* Action::GetDefendingCard() {
	return this->defending_card;
}
Card* Action::GetAttackingCard() {
	return this->attacker_card;
}