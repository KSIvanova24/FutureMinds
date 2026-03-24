#pragma once

#include "pch.h"


class Validate {
public:

    bool doesAccountExist(const string& targetUsername) const {
        ifstream file("../data/accounts.csv");
        if (!file.is_open()) return false;

        string line;
        string storedUsername;

        while (getline(file, line)) {
            if (line.empty()) continue;

            istringstream iss(line);
            if (getline(iss, storedUsername, ',')) {
                if (storedUsername == targetUsername) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isPasswordCorrect(const string& targetUsername, const string& targetPassword, const string& role) const {
        ifstream file("../data/accounts.csv");
        if (!file.is_open()) return false;

        string line;

        while (getline(file, line)) {
            if (line.empty()) continue;

            istringstream iss(line);
            string storedUsername, storedPassword, storedRole;

            if (getline(iss, storedUsername, ',') &&
                getline(iss, storedPassword, ',') &&
                getline(iss, storedRole, ',')) {

                if (storedUsername == targetUsername && storedPassword == targetPassword && storedRole == role) {
                    return true;
                }
            }
        }
        return false;
    }

    bool isPasswordStrong(const string& password) const {
        return containsUppercase(password) &&
            containsLowercase(password) &&
            containsDigit(password) &&
            containsSpecial(password);
    }

private:

    bool containsUppercase(const string& password) const {
        for (size_t i = 0; i < password.length(); ++i) {
            if (password[i] >= 'A' && password[i] <= 'Z') return true;
        }
        return false;
    }

    bool containsLowercase(const string& password) const {
        for (size_t i = 0; i < password.length(); ++i) {
            if (password[i] >= 'a' && password[i] <= 'z') return true;
        }
        return false;
    }

    bool containsDigit(const string& password) const {
        for (size_t i = 0; i < password.length(); ++i) {
            if (password[i] >= '0' && password[i] <= '9') return true;
        }
        return false;
    }

    bool containsSpecial(const string& password) const {
        for (size_t i = 0; i < password.length(); ++i) {
            if (!isalnum((unsigned char)password[i])) return true;
        }
        return false;
    }
};