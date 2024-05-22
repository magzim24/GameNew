#include <string>
#include "user.h"

User::User() {
	setName();
	type = TypePlayer::User_t;
}
void User::setName() {
	this->Name = string("User");// + Bot::id
	//Bot::id++;
}