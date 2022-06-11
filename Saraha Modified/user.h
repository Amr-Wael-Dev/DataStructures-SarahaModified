#pragma once

#include <queue>
#include <list>
#include <stack>
#include "contact.h"

class user
{
private:
	int id;
	string username, password, number;
	
public:
	vector<contact> contacts;
	list<string> favorites;
	queue<string> recievedMessages;
	stack<string> sentMessages;

	user();

	user(int id, string username, string password, string number);

	int getId();

	string getUsername();

	string getPassword();

	string getNumber();

	void sendMessage();

	void undoMessage();

	void searchContact();

	void viewContacts();

	void viewSentMessages();

	void viewRecievedMessages();

	void viewAllRecievedMessages();

	void addToFavorites();

	void removeOldestFavorite();

	void viewFavorites();
};
