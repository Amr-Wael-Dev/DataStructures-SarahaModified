#pragma once

#include <vector>
#include <string>

using namespace std;

class contact
{
private:
	string name;
	string number;

public:
	vector<string> recievedMessages, sentMessages;

	contact();

	contact(string name, string number);

	string getName();

	string getNumber();
};
