#include <iostream>
#include "user.h"

user::user()
{
	user::id = 0;
	user::username = "";
	user::password = "";
}

user::user(int id, string username, string password, string number)
{
	user::id = id;
	user::username = username;
	user::password = password;
	user::number = number;
}

int user::getId()
{
	return id;
}

string user::getUsername()
{
	return username;
}

string user::getPassword()
{
	return password;
}

string user::getNumber()
{
	return number;
}

void user::sendMessage()
{
	if (contacts.empty())
	{
		cout << "You have no contacts\n\n";
	}
	else
	{
		string number, message;
		bool found = false;

		viewContacts();

		cout << "Enter (0) at any point to go back\n\n";
		cout << "Your message: ";
		getline(cin, message, '\n');

		if (message != "0")
		{
			cout << "Enter the reciever's number: ";
			getline(cin, number, '\n');
			cout << endl;

			if (number != "0")
			{
				for (int i = 0; i < contacts.size(); i++)
				{
					if (contacts.at(i).getNumber() == number)
					{
						found = true;

						sentMessages.push(message);
						contacts.at(i).recievedMessages.push_back(message);

						cout << "Message sent successfully\n\n";
					}
				}

				if (!found)
				{
					cout << "There is no contact with this number\n\n";
				}
			}
		}
	}
}

void user::undoMessage()
{
	if (!sentMessages.empty())
	{
		for (int i = 0; i < contacts.size(); i++)
		{
			for (int j = 0; j < contacts.at(i).recievedMessages.size(); j++)
			{
				if (sentMessages.top() == contacts.at(i).recievedMessages.at(j))
				{
					contacts.at(i).recievedMessages.erase(contacts.at(i).recievedMessages.begin() + (j - 1));
				}
			}
		}

		sentMessages.pop();

		cout << "Last sent message deleted successfully\n\n";
	}
	else
	{
		cout << "You didn't send any messages\n\n";
	}
}

void user::searchContact()
{
	if (contacts.empty())
	{
		cout << "You have no contacts\n\n";
	}
	else
	{
		bool found = false;
		string username;

		cout << "Enter (0) at any point to go back\n\n";
		cout << "Enter the contact name: ";
		getline(cin, username, '\n');
		cout << endl;

		if (username != "0")
		{
			for (int i = 0; i < contacts.size(); i++)
			{
				if (contacts.at(i).getName() == username)
				{
					cout << "Contact found \n\n";
					cout << contacts.at(i).getName() << "\n";
					cout << contacts.at(i).getNumber() << "\n\n";

					found = true;

					break;
				}
			}

			if (!found)
			{
				cout << "Contact not found\n\n";
			}
		}
	}
}

void user::viewContacts()
{
	if (!contacts.empty())
	{
		cout << "Contacts:" << endl;

		for (int i = 0; i < contacts.size(); i++)
		{
			cout << "\t" << i + 1 << ": " << contacts.at(i).getName() << "\n";
			cout << "\t" << i + 1 << ": " << contacts.at(i).getNumber() << "\n\n";
		}
	}
	else
	{
		cout << "You have no contacts\n\n";
	}
}

void user::viewSentMessages()
{
	if (!sentMessages.empty())
	{
		stack<string> temp = sentMessages;

		cout << "Sent messages:" << endl;

		for (int i = 0; i < sentMessages.size(); i++)
		{
			cout << "\t" << temp.top() << endl;

			temp.pop();
		}

		cout << endl;
	}
	else
	{
		cout << "There are no sent messages\n\n";
	}
}

void user::viewRecievedMessages()
{
	string number;

	cout << "Enter (0) at any point to go back\n\n";
	cout << "Enter the contact number: ";
	getline(cin, number, '\n');
	cout << endl;

	if (number != "0")
	{
		bool found = false;

		for (int i = 0; i < contacts.size(); i++)
		{
			if (contacts.at(i).getNumber() == number)
			{
				queue<string> temp = recievedMessages;
				bool ok = false;

				for (int j = 0; j < contacts.at(i).sentMessages.size(); j++)
				{
					if (contacts.at(i).sentMessages.at(j) == temp.front())
					{
						cout << "\t" << j + 1 << ": " << contacts.at(i).sentMessages.at(j);

						ok = true;
					}

					temp.pop();
				}

				if (!ok)
				{
					cout << "You have no recieved messages from this contact\n\n";
				}

				found = true;
			}
		}

		if (!found)
		{
			cout << "Invalid number\n\n";
		}
	}
}

void user::viewAllRecievedMessages()
{
	queue<string> temp = recievedMessages;

	cout << "Recieved messages:";

	for (int i = 0; i < temp.size(); i++)
	{
		cout << "\t" << i + 1 << ": " << temp.front();

		temp.pop();
	}
}

void user::addToFavorites()
{
	if (recievedMessages.empty())
	{
		cout << "You have no recieved messages\n\n";
	}
	else
	{
		viewAllRecievedMessages();

		string number;
		int num;
		bool isNum = false;

		cout << "Enter (0) at any point to go back\n\n";
		cout << "Enter the message number: ";
		getline(cin, number, '\n');
		cout << endl;
		
		if (number != "0")
		{
			try
			{
				num = stoi(number);

				isNum = true;
			}
			catch (exception e)
			{
				cout << "Please enter only a number\n\n";
			}

			if (num < 1 || num > recievedMessages.size())
			{
				bool added = false;
				vector<string> tempV;
				queue<string> tempQ = recievedMessages;

				for (int i = 0; i < tempQ.size(); i++)
				{
					tempV.push_back(tempQ.front());

					tempQ.pop();
				}

				for (int i = 0; i < tempV.size(); i++)
				{
					if ((i + 1) == num)
					{
						favorites.push_back(tempV.at(i));

						cout << "Message added to favorites successfully\n\n";

						added = true;
					}

				}

				if (!added)
				{
					cout << "Invalid input\n\n";
				}
			}
			else
			{
				cout << "Invalid input\n\n";
			}
		}
	}
}

void user::removeOldestFavorite()
{
	if (favorites.empty())
	{
		cout << "You have no favorites\n\n";
	}
	else
	{
		favorites.pop_front();

		cout << "Oldest favorite removed successfully\n\n";
	}
}

void user::viewFavorites()
{
	if (favorites.empty())
	{
		cout << "You have no favorites\n\n";
	}
	else
	{
		vector<string> temp{ favorites.begin(), favorites.end() };

		cout << "Favorites:" << endl;

		for (int i = 0; i < temp.size(); i++)
		{
			cout << "\t" << temp.at(i) << endl;
		}
	}
}
