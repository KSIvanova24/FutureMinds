#include "settings.h"
void settings()
{
    std::string username = "Ivan_Pro_99";
    std::string password = "password123";
    int level = 42;
    int rank = 1;

    int activeField = 0; // 0 = none, 1 = name, 2 = pass
    const int MAX_CHARS = 15;

    Color bgWhite = { 240, 242, 245, 255 };
    Color cardColor = WHITE;
    Color accentColor = { 0, 110, 230, 255 }; // Малко по-тъмно синьо за по-добра четимост
    Color textColor = { 20, 20, 20, 255 };    // Почти черно за максимален контраст
    Color inputBg = { 240, 240, 243, 255 };
    Color borderColor = { 200, 200, 205, 255 };

    while (!WindowShouldClose())
    {
        // 1. ЛОГИКА
        Vector2 mouse = GetMousePosition();

        // По-големи и добре позиционирани зони
        Rectangle card = { 460, 80, 1000, 800 };
        Rectangle nameBtn = { 510, 350, 900, 80 }; // По-широки и високи полета
        Rectangle passBtn = { 510, 520, 900, 80 };
        Rectangle exitBtn = { 510, 750, 900, 80 };

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, nameBtn)) activeField = 1;
            else if (CheckCollisionPointRec(mouse, passBtn)) activeField = 2;
            else activeField = 0;

            if (CheckCollisionPointRec(mouse, exitBtn)) break;
        }

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

        // 2. РИСУВАНЕ
        BeginDrawing();
        ClearBackground(bgWhite);

        // Основна карта
        DrawRectangleRounded(card, 0.02f, 10, cardColor);
        DrawRectangleRoundedLines(card, 0.02f, 10, 2, borderColor);

        // Заглавие
        DrawText("ACCOUNT SETTINGS", card.x + 50, card.y + 40, 40, textColor);
        DrawLineEx({ card.x + 50, card.y + 95 }, { card.x + 950, card.y + 95 }, 2, borderColor);

        // Статистики - Преместени нагоре, за да не пречат
        DrawRectangleRounded({ card.x + 50, card.y + 120, 300, 60 }, 0.5f, 10, inputBg);
        DrawText(TextFormat("LEVEL: %i", level), card.x + 80, card.y + 138, 25, accentColor);

        DrawRectangleRounded({ card.x + 380, card.y + 120, 300, 60 }, 0.5f, 10, inputBg);
        DrawText(TextFormat("RANK: #%i", rank), card.x + 410, card.y + 138, 25, GOLD);

        // --- СЕКЦИЯ ИМЕ ---
        DrawText("DISPLAY NAME", nameBtn.x + 5, nameBtn.y - 35, 20, GRAY);
        DrawRectangleRounded(nameBtn, 0.15f, 10, (activeField == 1) ? WHITE : inputBg);
        DrawRectangleRoundedLines(nameBtn, 0.15f, 10, 2, (activeField == 1) ? accentColor : borderColor);

        // По-ясно изписване на името (черен цвят и малко по-голям шрифт)
        DrawText(username.c_str(), nameBtn.x + 25, nameBtn.y + 22, 35, textColor);

        if (activeField == 1 && ((int)(GetTime() * 2) % 2 == 0)) {
            DrawRectangle(nameBtn.x + 30 + MeasureText(username.c_str(), 35), nameBtn.y + 20, 3, 40, accentColor);
        }

        // --- СЕКЦИЯ ПАРОЛА ---
        DrawText("SECURITY PASSWORD", passBtn.x + 5, passBtn.y - 35, 20, GRAY);
        DrawRectangleRounded(passBtn, 0.15f, 10, (activeField == 2) ? WHITE : inputBg);
        DrawRectangleRoundedLines(passBtn, 0.15f, 10, 2, (activeField == 2) ? accentColor : borderColor);

        std::string stars(password.length(), '*');
        DrawText(stars.c_str(), passBtn.x + 25, passBtn.y + 28, 45, textColor);

        if (activeField == 2 && ((int)(GetTime() * 2) % 2 == 0)) {
            DrawRectangle(passBtn.x + 30 + MeasureText(stars.c_str(), 45), passBtn.y + 20, 3, 40, accentColor);
        }

        // Бутон SAVE
        bool hoverExit = CheckCollisionPointRec(mouse, exitBtn);
        DrawRectangleRounded(exitBtn, 0.15f, 10, hoverExit ? accentColor : textColor);
        // Центриран текст на бутона
        int textWidth = MeasureText("SAVE CHANGES", 30);
        DrawText("SAVE CHANGES", exitBtn.x + (exitBtn.width / 2 - textWidth / 2), exitBtn.y + 25, 30, WHITE);

        EndDrawing();
    }
}