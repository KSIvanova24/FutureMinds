#include "accessData.h"

char currentUser[25] = "";

void DataAccess::addAccount(const string& username, const string& password)const {

    ofstream file("../data/accounts.csv", ios_base::app);
    // Add user's information
    file << username << ',' << password << "," << "student" << "\n";
    file.close();
}
