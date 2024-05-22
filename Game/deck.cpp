#include "deck.h"
#include "card.h"
#include <string>
#include <algorithm>
#include <iostream>
#include <random>
#include <vector>
using namespace ::std;

GameDeck::GameDeck() {
    this->deck = stack<Card*>();
    GenerateRandomStack();
}

void GameDeck::GenerateRandomStack() {
    vector<Card*> set_cards = vector<Card*>();
    FillSetCards(set_cards);
    random_device rd;
    mt19937 g(rd());
    shuffle(set_cards.begin(), set_cards.end(), g);
    for (Card* card : set_cards) {
        this->deck.push(card);
    }
}

void GameDeck::FillSetCards(vector<Card*>& set_cards) {
    string valuesCards[9] = {
        "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"
    };
    for (int j = 0; j < 4; j++) {
        for (string i : valuesCards) {
            Card* card = new Card(Card::suit_array[j], i);
            set_cards.push_back(card);
        }
    }
    
}
Card* GameDeck::GetCard() {
    if (!this->deck.empty())
    {
        Card* card = this->deck.top();
        this->deck.pop();
        return card;
    }
    else return nullptr;
}
void GameDeck::SetTrumpCard() {
    Card* card = this->deck.top();
    this->deck.pop();
    this->trump_card = card;
}
int GameDeck::GetLengthStack() {
    return this->deck.size();
}