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
    DrawText(countFinal.c_str(), 460, 220, 45, BLACK);
}

void DataAccess::saveQuizResult(const string& username, const string& quizType, int score) const {
    ifstream inFile("../data/notebook.csv");
    vector<string> lines;
    string line;
    bool studentFound = false;

    if (inFile.is_open()) {
        while (getline(inFile, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string storedName;
            getline(ss, storedName, ',');

            if (storedName == username) {
                line += "," + quizType + " " + to_string(score);
                studentFound = true;
            }
            lines.push_back(line);
        }
        inFile.close();
    }

    if (!studentFound) {
        string newLine = username + "," + quizType + " " + to_string(score);
        lines.push_back(newLine);
    }

    ofstream outFile("../data/notebook.csv");
    for (const auto& l : lines) {
        outFile << l << "\n";
    }
    outFile.close();
}
