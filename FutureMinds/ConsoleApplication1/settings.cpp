#include "settings.h"
#include "accessData.h"
#include "quizes.h"
#include "auth.h"
#include "dashboards.h"
#include "grades.h"

void settingsStudent()
{
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    string username = currentUser;
    string password = "password123";
    int level = 42;
    int rank = 1;

    int activeField = 0;
    const int MAX_CHARS = 15;

    Color bgWhite = { 240, 242, 245, 255 };
    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 0, 110, 230, 255 };
    Color textColor = { 20, 20, 20, 255 };
    Color inputBg = { 240, 240, 243, 255 };
    Color borderColor = { 200, 200, 205, 255 };

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        Rectangle card = { 400, 120, 1000, 800 };
        Rectangle nameBtn = { card.x + 50, 400, 900, 80 };
        Rectangle passBtn = { card.x + 50, 570, 900, 80 };
        Rectangle saveBtn = { card.x + 50, 800, 900, 80 };

        Rectangle qBtn = { 0, 220, 300, 60 };
        Rectangle gBtn = { 0, 290, 300, 60 };
        Rectangle sBtn = { 0, 360, 300, 60 };
        Rectangle logoutBtn = { 20, (float)GetScreenHeight() -100, 260, 50 };

        Vector2 dashPosition = { 0, 150 };
        Rectangle dashButton = { dashPosition.x, dashPosition.y, 300, 60 };
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, nameBtn)) activeField = 1;
            else if (CheckCollisionPointRec(mouse, passBtn)) activeField = 2;
            else activeField = 0;

            if (CheckCollisionPointRec(mouse, qBtn)) quizes();
            if (CheckCollisionPointRec(mouse, gBtn)) { ; } 
            if (CheckCollisionPointRec(mouse, saveBtn)) break; 
            if (CheckCollisionPointRec(mouse, logoutBtn)) { startingScreen(true);  }
        }

        string* currentStr = (activeField == 1) ? &username : (activeField == 2 ? &password : nullptr);
        if (currentStr != nullptr) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (currentStr->length() < MAX_CHARS)) {
                    *currentStr += (char)key;
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && currentStr->length() > 0) currentStr->pop_back();
            if (IsKeyPressed(KEY_ENTER)) activeField = 0;
        }

        BeginDrawing();
        ClearBackground(bgWhite);

        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        bool dashHover = CheckCollisionPointRec(mouse, dashButton);
        if (dashHover)
        {
            DrawRectangleRec(dashButton, Fade(accentColor, 0.3f));
            DrawRectangle(dashButton.x, dashButton.y, 5, dashButton.height, accentColor);
            if (dashHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                studentDashboard();

            }
        }
        DrawText("Dashboard", dashPosition.x + 60, dashPosition.y + 15, 24, WHITE);
        if (CheckCollisionPointRec(mouse, qBtn)) {
            DrawRectangleRec(qBtn, Fade(accentColor, 0.3f));
            DrawRectangle(qBtn.x, qBtn.y, 5, qBtn.height, accentColor);
        }
        DrawText("Quizzes", 60, 235, 24, WHITE);

        if (CheckCollisionPointRec(mouse, gBtn)) {
            DrawRectangleRec(gBtn, Fade(accentColor, 0.3f));
            DrawRectangle(gBtn.x, gBtn.y, 5, gBtn.height, accentColor);
            if (CheckCollisionPointRec(mouse,gBtn) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                gradesStudent();

            }
        }
        DrawText("Grades", 60, 305, 24, WHITE);

        DrawRectangleRec(sBtn, Fade(accentColor, 0.3f));
        DrawRectangle(sBtn.x, sBtn.y, 5, sBtn.height, accentColor);
        DrawText("Settings", 60, 375, 24, WHITE);

        bool logoutHover = CheckCollisionPointRec(mouse, logoutBtn);
        DrawRectangleRounded(logoutBtn, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", logoutBtn.x + 85, logoutBtn.y + 15, 20, WHITE);

        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);


        DrawRectangleRounded(card, 0.02f, 10, WHITE);
        DrawRectangleRoundedLines(card, 0.02f, 10, 2, borderColor);

        DrawText("ACCOUNT SETTINGS", card.x + 50, card.y + 40, 40, textColor);
        DrawLineEx({ card.x + 50, card.y + 95 }, { card.x + 950, card.y + 95 }, 2, borderColor);

                DrawRectangleRounded({ card.x + 50, card.y + 120, 300, 60 }, 0.5f, 10, inputBg);
        DrawText(TextFormat("LEVEL: %i", level), card.x + 80, card.y + 138, 25, accentColor);

        DrawRectangleRounded({ card.x + 380, card.y + 120, 300, 60 }, 0.5f, 10, inputBg);
        DrawText(TextFormat("RANK: #%i", rank), card.x + 410, card.y + 138, 25, GOLD);

        DrawText("DISPLAY NAME", nameBtn.x + 5, nameBtn.y - 35, 20, GRAY);
        DrawRectangleRounded(nameBtn, 0.15f, 10, (activeField == 1) ? WHITE : inputBg);
        DrawRectangleRoundedLines(nameBtn, 0.15f, 10, 2, (activeField == 1) ? accentColor : borderColor);
        DrawText(username.c_str(), nameBtn.x + 25, nameBtn.y + 22, 35, textColor);

        DrawText("SECURITY PASSWORD", passBtn.x + 5, passBtn.y - 35, 20, GRAY);
        DrawRectangleRounded(passBtn, 0.15f, 10, (activeField == 2) ? WHITE : inputBg);
        DrawRectangleRoundedLines(passBtn, 0.15f, 10, 2, (activeField == 2) ? accentColor : borderColor);
        string stars(password.length(), '*');
        DrawText(stars.c_str(), passBtn.x + 25, passBtn.y + 28, 45, textColor);

        if (activeField > 0 && ((int)(GetTime() * 2) % 2 == 0)) {
            Rectangle targetRec = (activeField == 1) ? nameBtn : passBtn;
            int offset = (activeField == 1) ? MeasureText(username.c_str(), 35) : MeasureText(stars.c_str(), 45);
            DrawRectangle(targetRec.x + 30 + offset, targetRec.y + 20, 3, 40, accentColor);
        }

        bool hoverSave = CheckCollisionPointRec(mouse, saveBtn);
        DrawRectangleRounded(saveBtn, 0.15f, 10, hoverSave ? accentColor : textColor);
        int textWidth = MeasureText("SAVE CHANGES", 30);
        DrawText("SAVE CHANGES", saveBtn.x + (saveBtn.width / 2 - textWidth / 2), saveBtn.y + 25, 30, WHITE);

        EndDrawing();
    }
}
void settingsTeacher()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();

    string username = currentUser; 
    string password = "password123";
    int activeField = 0; 
    const int MAX_CHARS = 15;

    Color bgWhite = { 240, 242, 245, 255 };
    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 66, 153, 225, 255 };
    Color textColor = { 20, 20, 20, 255 };
    Color inputBg = { 240, 240, 243, 255 };
    Color borderColor = { 200, 200, 205, 255 };

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        Rectangle card = { 400, 120, 1000, 800 };
        Rectangle nameBtn = { card.x + 50, 300, 900, 80 };  
        Rectangle passBtn = { card.x + 50, 470, 900, 80 };
        Rectangle saveBtn = { card.x + 50, 750, 900, 80 };

        Rectangle logoutBtn = { 20, (float)GetScreenHeight() - 100, 260, 50 };

        Rectangle dashBtn = { 0, 150, 300, 60 };
        Rectangle studentsBtn = { 0, 220, 300, 60 };
        Rectangle gBtn = { 0, 290, 300, 60 };
        Rectangle quizBtn = { 0, 360, 300, 60 };
        Rectangle setBtn = { 0, 430, 300, 60 };

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, nameBtn)) activeField = 1;
            else if (CheckCollisionPointRec(mouse, passBtn)) activeField = 2;
            else activeField = 0;

            if (CheckCollisionPointRec(mouse, dashBtn)) teacherDashboard(); 
            if (CheckCollisionPointRec(mouse, gBtn)) gradesTeacher();
            if (CheckCollisionPointRec(mouse, quizBtn)) quizes();
            if (CheckCollisionPointRec(mouse, logoutBtn)) startingScreen(true);
            if (CheckCollisionPointRec(mouse, saveBtn)) {
                activeField = 0;
            }
        }

        string* currentStr = (activeField == 1) ? &username : (activeField == 2 ? &password : nullptr);
        if (currentStr != nullptr) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (currentStr->length() < MAX_CHARS)) {
                    *currentStr += (char)key;
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && currentStr->length() > 0) currentStr->pop_back();
            if (IsKeyPressed(KEY_ENTER)) activeField = 0;
        }

        BeginDrawing();
        ClearBackground(bgWhite);

        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        auto DrawSidebarOption = [&](Rectangle rect, const char* label, bool active) {
            if (CheckCollisionPointRec(mouse, rect) || active) {
                DrawRectangleRec(rect, Fade(accentColor, 0.3f));
                DrawRectangle(rect.x, rect.y, 5, rect.height, accentColor);
            }
            DrawText(label, 60, rect.y + 15, 24, WHITE);
            };

        DrawSidebarOption(dashBtn, "Dashboard", false);
        DrawSidebarOption(studentsBtn, "Students", false);
        DrawSidebarOption(gBtn, "Grades", false);
        DrawSidebarOption(quizBtn, "Quizzes", false);
        DrawSidebarOption(setBtn, "Settings", true); // Current page

        bool logoutHover = CheckCollisionPointRec(mouse, logoutBtn);
        DrawRectangleRounded(logoutBtn, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", logoutBtn.x + 85, logoutBtn.y + 15, 20, WHITE);

        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);
        DrawText("TEACHER PORTAL", 330, 25, 25, sideBarColor);

        DrawRectangleRounded(card, 0.02f, 10, WHITE);
        DrawRectangleRoundedLines(card, 0.02f, 10, 2, borderColor);

        DrawText("TEACHER SETTINGS", card.x + 50, card.y + 40, 40, textColor);
        DrawLineEx({ card.x + 50, card.y + 95 }, { card.x + 950, card.y + 95 }, 2, borderColor);

        DrawText("DISPLAY NAME", nameBtn.x + 5, nameBtn.y - 35, 20, GRAY);
        DrawRectangleRounded(nameBtn, 0.15f, 10, (activeField == 1) ? WHITE : inputBg);
        DrawRectangleRoundedLines(nameBtn, 0.15f, 10, 2, (activeField == 1) ? accentColor : borderColor);
        DrawText(username.c_str(), nameBtn.x + 25, nameBtn.y + 22, 35, textColor);

        DrawText("SECURITY PASSWORD", passBtn.x + 5, passBtn.y - 35, 20, GRAY);
        DrawRectangleRounded(passBtn, 0.15f, 10, (activeField == 2) ? WHITE : inputBg);
        DrawRectangleRoundedLines(passBtn, 0.15f, 10, 2, (activeField == 2) ? accentColor : borderColor);
        string stars(password.length(), '*');
        DrawText(stars.c_str(), passBtn.x + 25, passBtn.y + 28, 45, textColor);

        if (activeField > 0 && ((int)(GetTime() * 2) % 2 == 0)) {
            Rectangle targetRec = (activeField == 1) ? nameBtn : passBtn;
            int offset = (activeField == 1) ? MeasureText(username.c_str(), 35) : MeasureText(stars.c_str(), 45);
            DrawRectangle(targetRec.x + 30 + offset, targetRec.y + 20, 3, 40, accentColor);
        }

        bool hoverSave = CheckCollisionPointRec(mouse, saveBtn);
        DrawRectangleRounded(saveBtn, 0.15f, 10, hoverSave ? accentColor : textColor);
        int sw = MeasureText("SAVE CHANGES", 30);
        DrawText("SAVE CHANGES", saveBtn.x + (saveBtn.width / 2 - sw / 2), saveBtn.y + 25, 30, WHITE);

        EndDrawing();
    }
}
