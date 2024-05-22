#pragma once
#include <vector>
#include "battle.h"
#include "deck.h"
#include "player.h"
#include "card.h"
#include "CardsOnDesk.h"
#include <map>
using namespace ::std;

constexpr auto MAX_CARDS_TO_REPULSE = 6;;

class Player;
class Card;

enum TypeAction {
	UserAttack,
	UserDefense
};
class ConsoleMenu {
public:
	ConsoleMenu(TypeAction type, Card* trump_card, const vector<Action*>& actions);
	void display();
	void ChangeTypeAction(TypeAction type);
	void SetCards(map<int, Card*> cards);
	void MoveRight();
	void MoveLeft();
	void SetEnemyCard(Card* EnemyCard);
	Card* GetCurrentCard();
	void PrintAttackHeader();
	void PrintDefenseHeader();
	void PrintAllPairs();
private:
	int posCursor;
	map<int, Card*> cards;
	map<int, int[2]> indexesOfStrings; /* первый элемент массива - координата posCursor,
	а второй - длина строки вместе с пробелом и отступами после""*/
	const int MARGIN_AFTER_CARD = 3;
	TypeAction type;
	void UpdateIndexesOfStrings();
	Card* EnemyCard;
	const vector<Action*>* actionPairs;
	Card* trump_card;
};

class Game {
private:
	int amount_players;
	
	vector<Player*> players;
	GameDeck* deck; // колода
	Player* current_fighting_player;
	Battle* battle;
	ConsoleMenu* consoleMenu;
	int indexOfVectorElem(Player*);
	void AddPlayersToArrayPlayers();
	void ClearGameDeskOfCards();
	void FirstDistributionCards(Player*);
	void SetFirstAttackingPlayer();
	void PlayerRoundHandle();
	void UserRoundHandle();
	void BotRoundHandle();
	Card* HandleBtnInput();
	void UserAttackHandle(Player*, bool& tookCard);
	void FillPlayersCards();
	void BotAttackBot(Player* player, bool& tookCard);
	void BotAttackUser(Player* bot, bool& tookCard);
public:
	static const map<string, int> value_level;
	//const int MAX_CARDS_TO_REPULSE = 6;
	Game(int amount_players);
	void GameStart();
	
};
