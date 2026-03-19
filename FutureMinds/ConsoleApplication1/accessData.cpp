#include "accessData.h"

char currentUser[25] = "";

void DataAccess::addAccount(const string& username, const string& password)const {

    ofstream file("../data/accounts.csv", ios_base::app);
    // Add user's information
    file << username << ',' << password << "," << "student" << "\n";
    file.close();
}

void drawUsername(string user)
{
    ifstream file("../data/accounts.csv");
    string line, storedUsername, storedPassword, storedRole;
    string username;
    string greeting = "Welcome back, ";
    while (getline(file, line))
    {
        istringstream iss(line);
        if (getline(iss, storedUsername, ',') && getline(iss, storedPassword, ',') && getline(iss, storedRole))
        {
            if (storedUsername == currentUser)
            {
                username = storedUsername;
            }
        }
    }
    string finalUsername = greeting + username;
    DrawText(finalUsername.c_str(), GetScreenWidth() / 2 - 525, GetScreenHeight() / 2 - 467, 45, BLACK);

}

void drawStudentsCount()
{
    ifstream file("../data/accounts.csv");
    string line, storedUsername, storedPassword, storedRole;
    int count = 0;

    while (getline(file, line))
    {
        istringstream iss(line);
        if (getline(iss, storedUsername, ',') && getline(iss, storedPassword, ',') && getline(iss, storedRole))
        {
            if (storedRole == "student")
            {
                count++;
            }

        }
    }
    string countFinal = to_string(count);
    DrawText(countFinal.c_str(), 370, 220, 45, BLACK);
}
