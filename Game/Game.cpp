#include <map>
#include <conio.h>
#include <iostream>
#include "card.h"
#include "game.h"
#include "player.h"
#include "bot.h"
#include "user.h"
#include "battle.h"
using namespace ::std;




const map<string, int> Game::value_level = {
		{"6", 1}, {"7", 2}, {"8", 3},
		{"9", 4}, {"10", 5}, {"Jack", 6},
		{"Queen", 7}, {"King", 8}, {"Ace", 9}
};
Game::Game(int amount_players) {
	this->amount_players = amount_players;
	this->current_fighting_player = nullptr;
	this->battle = new Battle();
	if(this->amount_players >1 && this->amount_players <6){
		this->deck = new GameDeck();
		this->players = vector<Player*>();
		AddPlayersToArrayPlayers();
		this->deck->SetTrumpCard();
		SetFirstAttackingPlayer();
		consoleMenu = new ConsoleMenu(TypeAction::UserAttack, deck->trump_card, this->battle->GetAllActionsOfBattle());
	}
	else {
		this->deck = nullptr;
		this->players = vector<Player*>();
	}
}

void Game::AddPlayersToArrayPlayers() {
	for (int i = 0; i < this->amount_players - 1; i++) {
		Bot* bot = new Bot();
		FirstDistributionCards(bot);
	}
	User* user = new User();
	FirstDistributionCards(user);
}
void Game::FirstDistributionCards(Player* player) {
	for (int j = 0; j < 6; j++) {
		Card* card = this->deck->GetCard();
		player->TakeCard(card);
	}
	this->players.push_back(player);
}
void Game::ClearGameDeskOfCards() {

}

void Game::SetFirstAttackingPlayer() {
	Card* current_trump_card = nullptr;
	string trump_suit = this->deck->trump_card->suit;
	for (Player* player : this->players) {
		Card* card = player->GetMinTrumpCard(trump_suit);
		if (current_trump_card != nullptr) {
			
			if (card != nullptr) {
				if (value_level.at(card->value) <
					value_level.at(current_trump_card->value)) {
					current_trump_card = card;
					this->current_fighting_player = player;
				}
			}
		}
		else {
			current_trump_card = card;
			this->current_fighting_player = player;
		}
	}
}

int Game::indexOfVectorElem(Player* player) {
	return distance(players.begin(), find(players.begin(), players.end(), player));
}

void Game::BotRoundHandle() {
	int index = indexOfVectorElem(current_fighting_player);
	bool TookCard = false;
	for (int j = index + 1 == amount_players ? 0 : index+1; j != index; j == amount_players - 1 ? j = 0 : j++) {
		if (!TookCard) {
			switch (players[j]->type)
			{
			case TypePlayer::Bot_t: // бот атакует бота
				BotAttackBot(players[j], TookCard);
				break;
			case TypePlayer::User_t: // юзер атакует бота
				UserAttackHandle(players[j], TookCard);
				break;
			default:
				break;
			}
		}
	}
	
}

void Game::BotAttackBot(Player* player, bool& tookCard) {
	while (battle->AmountOfActions() < MAX_CARDS_TO_REPULSE) {
		Action* action = player->MakeDecisionAboutAttack(battle->GetCurrentCardsOnDesk(),
			current_fighting_player);
		if (action) {
			action = current_fighting_player->MakeDecisionAboutDefend(action, deck->trump_card);
			battle->AddAction(action);
			if (!action->GetDefendingCard()) {
				tookCard = true;
				break;
			}
		}
		else break;
	}
}

void Game::UserAttackHandle(Player* player, bool& tookCard) {
	this->consoleMenu->ChangeTypeAction(TypeAction::UserAttack);
	map<int, Card*> cards;
	Card* card;
	while (battle->AmountOfActions() < MAX_CARDS_TO_REPULSE) {
		cards = player->GetAvailableCardToAttack(battle->GetCurrentCardsOnDesk());
		this->consoleMenu->SetCards(cards);
		this->consoleMenu->display();
		card = HandleBtnInput();
		if (card) {
			player->RemoveCard(card);
			Action* action = new Action(player, current_fighting_player, card);
			action = current_fighting_player->MakeDecisionAboutDefend(action, deck->trump_card);
			battle->AddAction(action);
			if (!action->GetDefendingCard()) {
				tookCard = true;
				break;
			}
		}
		else break;
	}
}

void Game::BotAttackUser(Player* bot, bool& tookCard) {
	
	this->consoleMenu->ChangeTypeAction(TypeAction::UserDefense);
	map<int, Card*> cards;
	Card* card;
	while (battle->AmountOfActions() < amount_players) {
		Action* action = bot->MakeDecisionAboutAttack(battle->GetCurrentCardsOnDesk(),
			current_fighting_player);
		if (action) {
			consoleMenu->SetEnemyCard(action->GetAttackingCard());
			cards = current_fighting_player->GetAvailableCardToDefend(action->GetAttackingCard(), deck->trump_card);
			this->consoleMenu->SetCards(cards);
			this->consoleMenu->display();
			card = HandleBtnInput();
			action->SetDefendingCard(card);
			battle->AddAction(action);
			if (!action->GetDefendingCard()) {
				tookCard = true;
				break;
			}
		}
		else break;
	}
}

void Game::UserRoundHandle() {
	int index = indexOfVectorElem(current_fighting_player);
	bool TookCard = false;
	for (int j = index + 1 == amount_players ? 0 : index + 1; j != index; j == amount_players - 1 ? j = 0 : j++) {
		if (!TookCard) {
			BotAttackUser(players[j], TookCard);
		}
	}
}

Card* Game::HandleBtnInput() {
	int btn = _getch();
	while (btn != 13) {
		if (btn == 224) //Проверка нажатия функциональной клавиши
		{
			btn = _getch();
			switch (btn)
			{
			case 75:
				consoleMenu->MoveLeft();
				break;
			case 77:
				consoleMenu->MoveRight();
				break;
			}
		}
		btn = _getch();
	}
	
	Card* card = consoleMenu->GetCurrentCard();
	if (card) {
		return card;
	}
	else return nullptr;
}

void Game::PlayerRoundHandle() {
	switch (current_fighting_player->type)
	{
		case TypePlayer::Bot_t:
			BotRoundHandle();
			break;
		case TypePlayer::User_t:
			UserRoundHandle();
			break;
		default:
			break;
	}
}

void Game::FillPlayersCards() {
	int index = indexOfVectorElem(current_fighting_player);
	int counterPlayers = 0;
	for (int j = index + 1 == amount_players ? 0 : index; counterPlayers != amount_players; j == amount_players - 1 ? j = 0 : j++, counterPlayers++) {
		
		if (!(players[j]->GetLenghtSetCards() >= 6)) {
			while (players[j]->GetLenghtSetCards() != 6) {
				if (deck->GetLengthStack() > 0) {
					players[j]->TakeCard(deck->GetCard());
				}
				else return;
			}
		}
		
	}
}

void Game::GameStart(){
	int index = indexOfVectorElem(current_fighting_player);
	for (int j = index + 1 == amount_players ? 0 : index; ; j == amount_players - 1 ? j = 0:j++) {
		current_fighting_player = players[j];
		PlayerRoundHandle();
		FillPlayersCards();
		battle->CardsOnDeskReset();
		battle->ActionsReset();
	}
}

ConsoleMenu::ConsoleMenu(TypeAction type, Card* trump_card, const vector<Action*>& actions){
	this->type = type;
	posCursor = 0;
	EnemyCard = new Card();
	indexesOfStrings = map<int, int[2]>();
	this->trump_card = trump_card;
	this->actionPairs = &actions;
}

void ConsoleMenu::ChangeTypeAction(TypeAction type) {
	posCursor = 0;
	this->type = type;
}

void ConsoleMenu::SetCards(map<int, Card*> cards) {
	this->cards = cards;
	UpdateIndexesOfStrings();
}

void ConsoleMenu::SetEnemyCard(Card* EnemyCard) {
	if (EnemyCard) this->EnemyCard = EnemyCard;
}

void ConsoleMenu::UpdateIndexesOfStrings() {
	indexesOfStrings.clear();
	int amountCards = cards.size();
	int lenStrings = 0;
	Card* card;
	int i = 0;
	for (i; i < amountCards; ++i) {
		card = (next(cards.begin(), i))->second;
		int lenCurStr = card->suit.size() + card->value.size() + 1 + MARGIN_AFTER_CARD;
		if (i == 0) {
			indexesOfStrings[0][0] = 0;
			indexesOfStrings[0][1] = lenCurStr;

		}
		else {
			indexesOfStrings[i][0] = lenStrings + 1;
			indexesOfStrings[i][1] = lenCurStr;

		}
		lenStrings += lenCurStr;
	}
	indexesOfStrings[amountCards][0] = lenStrings + 1;
	indexesOfStrings[amountCards][1] = 4;
}

void ConsoleMenu::PrintAttackHeader() {
	cout << "Карты, которые вы можете использовать: " << endl;
}

void ConsoleMenu::PrintDefenseHeader() {
	cout << "Карта оппонента: " << EnemyCard->suit << " " << EnemyCard->value<<endl;
	cout << "Карты, которые вы можете использовать: " << endl;
}

void ConsoleMenu::PrintAllPairs() {
	Action* action;
	for (int i = 0; i < actionPairs->size(); ++i) {
		action = this->actionPairs->at();

	}
}

void ConsoleMenu::display() {
	system("cls");
	Card* card;
	
	switch (type) {
	case TypeAction::UserAttack:
		PrintAttackHeader();
		break;
	case TypeAction::UserDefense:
		PrintDefenseHeader();
		break;
	}
	for (int i = 0; i < cards.size(); ++i) {
		card = (next(cards.begin(), i))->second;
		cout << card->suit << " " << card->value << string(MARGIN_AFTER_CARD, ' ');
	}
	cout << "Пасс"<<endl;
	cout << string(indexesOfStrings[posCursor][0],' ') << "^" << posCursor << endl;
}

void ConsoleMenu::MoveRight() {
	if (posCursor < cards.size()) {
		posCursor++;
		display();
	}
}
void ConsoleMenu::MoveLeft() {
	if (posCursor != 0) {
		posCursor--;
		display();
	}
}
Card* ConsoleMenu::GetCurrentCard() {
	if (posCursor == cards.size()) {
		return nullptr;
	}
	else return cards[posCursor];
}