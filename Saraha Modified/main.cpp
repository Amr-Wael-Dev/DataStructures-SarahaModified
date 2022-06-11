#include <iostream>
#include <fstream>
#include "user.h"

bool loggedIn = false;
int userIndex;
vector<user> users;

bool isNumber(string str);
void logIn();
void signUp();
void showMenu();
void viewAllUsers();

int main()
{
    string choice, text;

    /* ifstream file("users.txt");
    while (getline(file, text))
    {
        cout << text << endl << endl;
    }
    file.close(); */

    cout << "Welcome!\n\n";
    cout << "Enter(1) to: Log in\n";
    cout << "Enter(2) to: Sign up\n";
    cout << "Enter(0) to: Exit\n";
    cout << "Your choice : ";
    getline(cin, choice, '\n');
    cout << endl;

    if (isNumber(choice))
    {
        if (choice == "1")
        {
            logIn();

            if (loggedIn)
            {
                showMenu();
            }
            else
            {
                main();
            }
        }
        else if (choice == "2")
        {
            signUp();

            if (loggedIn)
            {
                showMenu();
            }
            else
            {
                main();
            }
        }
        else if (choice == "0")
        {
            /* ofstream file("users.txt");
            file << "Files can be tricky, but it is fun enough!";
            file.close(); */

            return 0;
        }
        else
        {
            cout << "Please enter only one of the specified values\n\n";
        }
    }
    else
    {
        cout << "Please enter only a number\n\n";
    }

    main();

    return 0;
}

bool isNumber(string str)
{
    for (int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]))
        {
            return false;
        }
    }

    return true;
}

void logIn()
{
    bool found = false;

    string username, password;
    loggedIn = false;

    cout << "Enter (0) at any point to go back\n\n";
    cout << "Enter a Username: ";
    getline(cin, username, '\n');

    if (username != "0")
    {
        cout << "Enter the Password: ";
        getline(cin, password, '\n');
        cout << endl;

        if (password != "0")
        {
            for (int i = 0; i < users.size(); i++)
            {
                if (users.at(i).getUsername() == username && users.at(i).getPassword() == password)
                {
                    loggedIn = true;
                    userIndex = i;
                    found = true;

                    break;
                }
            }

            if (!found)
            {
                cout << "Username or password incorrect\n\n";
            }
        }
    }
}

void signUp()
{
    string username, password, number;
    int id = (int)users.size() + 1;
    loggedIn = false;
    bool exists = false;

    cout << "Enter (0) at any point to go back\n\n";
    cout << "Enter a Username: ";
    getline(cin, username, '\n');

    if (username != "0")
    {
        for (int i = 0; i < users.size(); i++)
        {
            if (users.at(i).getUsername() == username)
            {
                exists = true;

                break;
            }
        }

        // NUMBER SIGN UP HAMDY :)
        if (exists)
        {
            cout << "This username already exists\n\n";
        }
        else
        {
            cout << "Enter a phone number((11) digit): ";
            getline(cin, number, '\n');

            if (number != "0")
            {
                if (!isNumber(number))
                {
                    cout << "Please enter digits only\n\n";
                }
                else
                {
                    for (int i = 0; i < users.size(); i++)
                    {
                        if (users.at(i).getNumber() == number)
                        {
                            exists = true;

                            break;
                        }
                    }

                    if (exists)
                    {
                        cout << "This phone number already exists\n\n";
                    }
                    else if (number.size() != 11)
                    {
                        cout << "This phone is wrong please enter (11) digit\n\n";
                    }
                    else
                    {
                        cout << "Enter a Password: ";
                        getline(cin, password, '\n');
                        cout << endl;

                        if (password != "0")
                        {
                            users.push_back(user(id, username, password, number));

                            userIndex = users.size() - 1;

                            cout << endl;

                            loggedIn = true;
                        }
                    }
                }
            }
        }
    }
}

void showMenu()
{
    string choice;

    cout << "\tID: " << users.at(userIndex).getId();
    cout << "\t\tphone number: " << users.at(userIndex).getNumber() << "\n\t------\t\t-------------------------\n";
    cout << "Enter (1) to: Add a user to your contact\n";
    cout << "Enter (2) to: Send a message to a contact\n";
    cout << "Enter (3) to: Undo the last sent message\n";
    cout << "Enter (4) to: Search for a contact\n";
    cout << "Enter (5) to: View all contacts\n";
    cout << "Enter (6) to: View all sent messages from latest to oldest\n";
    cout << "Enter (7) to: View all recieved messages from a contact\n";
    cout << "Enter (8) to: Put a message in favorites\n";
    cout << "Enter (9) to: Remove oldest message from favorites\n";
    cout << "Enter (10) to: View all favorite messages\n";
    cout << "Enter (11) to: View all users\n";
    cout << "Enter (12) to: Sign out\n";
    cout << "Enter (0) to: Exit\n";
    cout << "Your choice: ";
    getline(cin, choice, '\n');
    cout << endl;

    if (isNumber(choice))
    {
        if (choice == "0")
        {
            exit(0);
        }
        else if (choice == "1") // ADD CONTACT HAMDY :)
        {
            string number;
            bool found = false;

            cout << "Enter (0) at any point to return\n\n";
            cout << "Enter the phone number: ";
            getline(cin, number, '\n');

            if (number != "0")
            {
                for (int i = 0; i < users.size(); i++)
                {
                    if (number == users.at(userIndex).getNumber())
                    {
                        break;
                    }

                    bool exists = false;

                    if (users.at(i).getNumber() == number)
                    {
                        found = true;

                        for (int j = 0; j < users.at(userIndex).contacts.size(); j++)
                        {
                            if (users.at(i).getNumber() == users.at(j).getNumber())
                            {
                                exists = true;

                                break;
                            }
                        }

                        if (exists)
                        {
                            cout << "This contact is already added\n\n";
                        }
                        else
                        {
                            string name;

                            cout << "Enter a name for your contact: ";
                            getline(cin, name, '\n');
                            cout << endl;

                            users.at(userIndex).contacts.push_back(contact(name, users.at(i).getNumber()));

                            cout << "Contact added successfully\n\n";
                            
                            break;
                        }
                    }
                }

                if (!found)
                {
                    cout << "Wrong number\n\n";
                }
            }
        }
        else if (choice == "2") // SEND MESSAGE AMR
        {
            users.at(userIndex).sendMessage();
        }
        else if (choice == "3") // UNDO LAST SENT MESSAGE OMAR MOHAMED
        {
            users.at(userIndex).undoMessage();
        }
        else if (choice == "4") // SEARCH CONTACT HAMDY :)
        {
            users.at(userIndex).searchContact();
        }
        else if (choice == "5") // VIEW CONTACTS HAMDY :)
        {
            users.at(userIndex).viewContacts();
        }
        else if (choice == "6") // VIEW SENT MESSAGES OMAR MOHAMED
        {
            users.at(userIndex).viewSentMessages();
        }
        else if (choice == "7") // VIEW RECIEVED MESSAGES MOHAMED
        {
            users.at(userIndex).viewRecievedMessages();
        }
        else if (choice == "8") // ADD TO FAVORITES KAREEM
        {
            users.at(userIndex).addToFavorites();
        }
        else if (choice == "9") // REMOVE OLDEST FAVORITE MOHAMED
        {
            users.at(userIndex).removeOldestFavorite();
        }
        else if (choice == "10") // VIEW FAVORITES OMAR MOSTAFA
        {
            users.at(userIndex).viewFavorites();
        }
        else if (choice == "11") // VIEW ALL USERS AMR
        {
            viewAllUsers();
        }
        else if (choice == "12")
        {
            main();
        }
        else
        {
            cout << "Please enter only one of the specified values\n\n";
        }
    }
    else
    {
        cout << "Please enter only a number\n\n";
    }

    showMenu();
}

void viewAllUsers()
{
    if (!users.empty())
    {
        cout << "Users:" << endl;

        for (int i = 0; i < users.size(); i++)
        {
            cout << "\t" << users.at(i).getUsername() << endl;
            cout << "\t" << users.at(i).getNumber() << endl << endl;
        }
    }
    else
    {
        cout << "There are no users\n\n";
    }
}
