#pragma once

#include "pch.h"



extern char currentUser[25];

void addAccount(const string& username, const string& password);
void saveQuizResult(const string& username, const string& quizType, int score);
void drawStudentsCount();
void drawUsername(string user);
