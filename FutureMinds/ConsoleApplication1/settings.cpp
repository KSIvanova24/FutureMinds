#include "settings.h"
#include "accessData.h"
#include "quizes.h"
#include "auth.h"

void settings()
{
    // Using the same screen constants for alignment
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    string username = currentUser;
    std::string password = "password123";
    int level = 42;
    int rank = 1;

    int activeField = 0;
    const int MAX_CHARS = 15;

    // UI Colors
    Color bgWhite = { 240, 242, 245, 255 };
    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 0, 110, 230, 255 };
    Color textColor = { 20, 20, 20, 255 };
    Color inputBg = { 240, 240, 243, 255 };
    Color borderColor = { 200, 200, 205, 255 };

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        // --- 1. SETTINGS CARD POSITIONING (Shifted X to 350 to clear Sidebar) ---
        Rectangle card = { 400, 120, 1000, 800 };
        Rectangle nameBtn = { card.x + 50, 400, 900, 80 };
        Rectangle passBtn = { card.x + 50, 570, 900, 80 };
        Rectangle saveBtn = { card.x + 50, 800, 900, 80 };

        // Sidebar Button Rectangles
        Rectangle qBtn = { 0, 150, 300, 60 };
        Rectangle gBtn = { 0, 220, 300, 60 };
        Rectangle sBtn = { 0, 290, 300, 60 };
        Rectangle logoutBtn = { 20, (float)GetScreenHeight() - 80, 260, 50 };

        // --- 2. LOGIC ---
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, nameBtn)) activeField = 1;
            else if (CheckCollisionPointRec(mouse, passBtn)) activeField = 2;
            else activeField = 0;

            // Navigation from Settings Sidebar
            if (CheckCollisionPointRec(mouse, qBtn)) quizes();
            if (CheckCollisionPointRec(mouse, gBtn)) { ; } // Grades placeholder
            if (CheckCollisionPointRec(mouse, saveBtn)) break; // "Save Changes" exits back to dashboard
            if (CheckCollisionPointRec(mouse, logoutBtn)) { startingScreen(true);  }
        }

        // Typing Logic
        std::string* currentStr = (activeField == 1) ? &username : (activeField == 2 ? &password : nullptr);
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

        // --- 3. DRAWING ---
        BeginDrawing();
        ClearBackground(bgWhite);

        // A. DRAW SIDEBAR
        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        // Quizzes Sidebar Button
        if (CheckCollisionPointRec(mouse, qBtn)) {
            DrawRectangleRec(qBtn, Fade(accentColor, 0.3f));
            DrawRectangle(qBtn.x, qBtn.y, 5, qBtn.height, accentColor);
        }
        DrawText("Quizzes", 60, 165, 24, WHITE);

        // Grades Sidebar Button
        if (CheckCollisionPointRec(mouse, gBtn)) {
            DrawRectangleRec(gBtn, Fade(accentColor, 0.3f));
            DrawRectangle(gBtn.x, gBtn.y, 5, gBtn.height, accentColor);
        }
        DrawText("Grades", 60, 235, 24, WHITE);

        // Settings Sidebar Button (Active State)
        DrawRectangleRec(sBtn, Fade(accentColor, 0.3f));
        DrawRectangle(sBtn.x, sBtn.y, 5, sBtn.height, accentColor);
        DrawText("Settings", 60, 305, 24, WHITE);

        // Logout Button
        bool logoutHover = CheckCollisionPointRec(mouse, logoutBtn);
        DrawRectangleRounded(logoutBtn, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", logoutBtn.x + 85, logoutBtn.y + 15, 20, WHITE);

        // B. DRAW TOP BAR
        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);
        drawUsername(currentUser);

        // C. DRAW SETTINGS CARD
        DrawRectangleRounded(card, 0.02f, 10, WHITE);
        DrawRectangleRoundedLines(card, 0.02f, 10, 2, borderColor);

        DrawText("ACCOUNT SETTINGS", card.x + 50, card.y + 40, 40, textColor);
        DrawLineEx({ card.x + 50, card.y + 95 }, { card.x + 950, card.y + 95 }, 2, borderColor);

        // Stats
        DrawRectangleRounded({ card.x + 50, card.y + 120, 300, 60 }, 0.5f, 10, inputBg);
        DrawText(TextFormat("LEVEL: %i", level), card.x + 80, card.y + 138, 25, accentColor);

        DrawRectangleRounded({ card.x + 380, card.y + 120, 300, 60 }, 0.5f, 10, inputBg);
        DrawText(TextFormat("RANK: #%i", rank), card.x + 410, card.y + 138, 25, GOLD);

        // Display Name Input
        DrawText("DISPLAY NAME", nameBtn.x + 5, nameBtn.y - 35, 20, GRAY);
        DrawRectangleRounded(nameBtn, 0.15f, 10, (activeField == 1) ? WHITE : inputBg);
        DrawRectangleRoundedLines(nameBtn, 0.15f, 10, 2, (activeField == 1) ? accentColor : borderColor);
        DrawText(username.c_str(), nameBtn.x + 25, nameBtn.y + 22, 35, textColor);

        // Password Input
        DrawText("SECURITY PASSWORD", passBtn.x + 5, passBtn.y - 35, 20, GRAY);
        DrawRectangleRounded(passBtn, 0.15f, 10, (activeField == 2) ? WHITE : inputBg);
        DrawRectangleRoundedLines(passBtn, 0.15f, 10, 2, (activeField == 2) ? accentColor : borderColor);
        std::string stars(password.length(), '*');
        DrawText(stars.c_str(), passBtn.x + 25, passBtn.y + 28, 45, textColor);

        // Cursor blink
        if (activeField > 0 && ((int)(GetTime() * 2) % 2 == 0)) {
            Rectangle targetRec = (activeField == 1) ? nameBtn : passBtn;
            int offset = (activeField == 1) ? MeasureText(username.c_str(), 35) : MeasureText(stars.c_str(), 45);
            DrawRectangle(targetRec.x + 30 + offset, targetRec.y + 20, 3, 40, accentColor);
        }

        // Save Button
        bool hoverSave = CheckCollisionPointRec(mouse, saveBtn);
        DrawRectangleRounded(saveBtn, 0.15f, 10, hoverSave ? accentColor : textColor);
        int textWidth = MeasureText("SAVE CHANGES", 30);
        DrawText("SAVE CHANGES", saveBtn.x + (saveBtn.width / 2 - textWidth / 2), saveBtn.y + 25, 30, WHITE);

        EndDrawing();
    }
}