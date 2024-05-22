#include "CardsOnDesk.h"

CardsOnDesk::CardsOnDesk(vector<Card*> cards) {
	container = vector<Card*>(cards);
}
CardsOnDesk::CardsOnDesk() {
	container = vector<Card*>();
}
const vector<Card*>& CardsOnDesk::GetCardsOnDesk() {
	return container;
}

void CardsOnDesk::Clear() {
	container.clear();
}