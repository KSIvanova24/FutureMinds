#include "pch.h"

void gradesTeacher();
void gradesStudent();
void viewStudentGradesList();
void calculateAverage();
void DrawStudentsProgressTable();

struct TabStudentGrade {
    string name;
    int totalXP = 0;
    int quizzesCount = 0;
    float averagePercentage = 0.0f;
};
