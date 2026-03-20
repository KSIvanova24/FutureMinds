#pragma once
#include "pch.h"

void quizes();
void showResults(const char* topicName, int score);
void englishVocabQuiz();
void englishGrammarQuiz();
void showDetailedResults(const char* title, int totalScore, const char* questions[], const char* options[], int correctAnswers[], int userChoices[], int count);