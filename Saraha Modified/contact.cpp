#include "contact.h"

contact::contact()
{
	contact::name = contact::number = "";
}

contact::contact(string name, string number)
{
	contact::name = name;
	contact::number = number;
}

string contact::getName()
{
	return name;
}

string contact::getNumber()
{
	return number;
}
