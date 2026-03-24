#include "settings.h"
#include "accessData.h"
#include "quizes.h"
#include "auth.h"
#include "dashboards.h"
#include "grades.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

void viewAllStudents() {
    Color bgWhite = { 240, 242, 245, 255 };
    Color sidebarColor = { 45, 55, 72, 255 };
    Color accentColor = { 66, 153, 225, 255 };
    Color textColor = { 20, 20, 20, 255 };
    Color borderColor = { 200, 200, 205, 255 };

    vector<string> students;

    ifstream file("../data/accounts.csv");
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string fUser, fPass, fRole;

        getline(ss, fUser, ',');
        getline(ss, fPass, ',');
        getline(ss, fRole, ',');

        if (fRole == "student") {
            students.push_back(fUser);
        }
    }
    file.close();

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(bgWhite);

        DrawRectangle(0, 0, 300, GetScreenHeight(), sidebarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        Rectangle navs[] = { {0, 150, 300, 60}, {0, 220, 300, 60}, {0, 290, 300, 60}, {0, 360, 300, 60}, {0, 430, 300, 60} };
        const char* labels[] = { "Dashboard", "Students", "Grades", "Quizzes", "Settings" };

        for (int i = 0; i < 5; i++) {
            bool hover = CheckCollisionPointRec(mouse, navs[i]);
            if (i == 1 || hover) { 
                DrawRectangleRec(navs[i], Fade(accentColor, 0.3f));
                DrawRectangle(0, (int)navs[i].y, 5, 60, accentColor);
            }
            DrawText(labels[i], 60, (int)navs[i].y + 15, 24, WHITE);

            if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (i == 0) teacherDashboard();
                if (i == 2) gradesTeacher();
                if (i == 3) quizes();
                if (i == 4) settingsTeacher();
            }
        }

        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);
        DrawText("STUDENTS LIST", 330, 40, 25, sidebarColor);

        Rectangle backBtn = { 330, 100, 150, 40 };
        bool backHover = CheckCollisionPointRec(mouse, backBtn);

        if (students.empty()) {
            DrawText("No students found.", 500, GetScreenHeight() / 2, 25, GRAY);
        }
        else {
            for (size_t i = 0; i < students.size(); i++) {
                float yPos = 160.0f + (i * 90);
                Rectangle row = { 330, yPos, 1000, 80 };

                DrawRectangleRounded(row, 0.15f, 10, WHITE);
                DrawRectangleRoundedLines(row, 0.15f, 10, 2, borderColor);

                float badgeX = row.x + 40;
                float badgeY = row.y + 40;
                DrawCircle((int)badgeX, (int)badgeY, 25, Fade(accentColor, 0.2f));

                string firstLetter = students[i].substr(0, 1);
                int letterW = MeasureText(firstLetter.c_str(), 24);
                DrawText(firstLetter.c_str(), (int)badgeX - (letterW / 2), (int)badgeY - 10, 24, accentColor);

                DrawText(students[i].c_str(), (int)row.x + 90, (int)row.y + 28, 24, textColor);
            }
        }
        Rectangle logoutBtn = { 20, (float)GetScreenHeight() - 95, 260, 50 };
        bool logoutHover = CheckCollisionPointRec(mouse, logoutBtn);
        DrawRectangleRounded(logoutBtn, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", logoutBtn.x + 85, logoutBtn.y + 15, 20, WHITE);

        if (logoutHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            startingScreen(true);
            break;
        }
        EndDrawing();
    }
}