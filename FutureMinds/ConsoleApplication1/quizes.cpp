#include "quizes.h"
#include "grades.h"
#include "settings.h"
#include "auth.h"

void quizes() {
    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 66, 153, 225, 255 };
    Color grammarColor = { 66, 153, 225, 255 };
    Color vocabColor = { 128, 90, 213, 255 };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground({ 240, 244, 248, 255 });

        // --- SIDEBAR ---
        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        Rectangle navs[] = { { 0, 150, 300, 60 }, { 0, 220, 300, 60 }, { 0, 290, 300, 60 }, { 0, 360, 300, 60 } };
        const char* labels[] = { "Dashboard", "Quizzes", "Grades", "Settings" };

        for (int i = 0; i < 4; i++) {
            bool hover = CheckCollisionPointRec(mouse, navs[i]);
            if (i == 1 || hover) {
                DrawRectangleRec(navs[i], Fade(accentColor, 0.3f));
                DrawRectangle(0, navs[i].y, 5, 60, accentColor);
            }
            DrawText(labels[i], 60, navs[i].y + 15, 24, WHITE);
            if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (i == 0) return;
                if (i == 2) gradesStudent();
                if (i == 3) settings();
            }
        }

        // --- LOGOUT BUTTON ---
        Rectangle logoutBtn = { 20, (float)GetScreenHeight() - 100, 260, 50 };
        bool logoutHover = CheckCollisionPointRec(mouse, logoutBtn);
        DrawRectangleRounded(logoutBtn, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", logoutBtn.x + 85, logoutBtn.y + 15, 20, WHITE);

        if (logoutHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            startingScreen(true);
            break; // Exit the quizes loop
        }

        // --- MAIN CONTENT ---
        DrawText("SELECT A CATEGORY", 350, 100, 25, GRAY);

        // Grammar Card
        Rectangle card1 = { 400, 200, 400, 500 };
        bool hov1 = CheckCollisionPointRec(mouse, card1);
        DrawRectangleRounded(card1, 0.1f, 10, WHITE);
        DrawRectangleRoundedLines(card1, 0.1f, 10, 4, hov1 ? grammarColor : LIGHTGRAY);
        DrawCircle(600, 330, 60, Fade(grammarColor, 0.1f));
        DrawText("G", 585, 305, 60, grammarColor);
        DrawText("Grammar", 530, 420, 35, BLACK);
        DrawText("Master tenses & structure", 480, 470, 20, GRAY);

        Rectangle btn1 = { 450, 580, 300, 60 };
        bool btnHov1 = CheckCollisionPointRec(mouse, btn1);
        DrawRectangleRounded(btn1, 0.5f, 10, btnHov1 ? BLACK : grammarColor);
        DrawText("START", btn1.x + 110, btn1.y + 18, 22, WHITE);
        if (btnHov1 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) englishGrammarQuiz();

        // Vocab Card
        Rectangle card2 = { 850, 200, 400, 500 };
        bool hov2 = CheckCollisionPointRec(mouse, card2);
        DrawRectangleRounded(card2, 0.1f, 10, WHITE);
        DrawRectangleRoundedLines(card2, 0.1f, 10, 4, hov2 ? vocabColor : LIGHTGRAY);
        DrawCircle(1050, 330, 60, Fade(vocabColor, 0.1f));
        DrawText("V", 1035, 305, 60, vocabColor);
        DrawText("Vocabulary", 960, 420, 35, BLACK);
        DrawText("Expand your dictionary", 940, 470, 20, GRAY);

        Rectangle btn2 = { 900, 580, 300, 60 };
        bool btnHov2 = CheckCollisionPointRec(mouse, btn2);
        DrawRectangleRounded(btn2, 0.5f, 10, btnHov2 ? BLACK : vocabColor);
        DrawText("START", btn2.x + 110, btn2.y + 18, 22, WHITE);
        if (btnHov2 && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) englishVocabQuiz();

        EndDrawing();
    }
}

void englishVocabQuiz() {
    const char* qText[] = {
        "Synonym of 'Fast'?", "Opposite of 'Huge'?", "A 'huge' thing is...",
        "Definition of 'Ancient'?", "Synonym of 'Happy'?", "Opposite of 'Difficult'?",
        "What is a 'Breeze'?", "Synonym of 'Observe'?", "Opposite of 'Bright'?", "A 'journey' is a..."
    };
    const char* opts[] = {
        "Quick", "Slow", "Steady",       "Tiny", "Large", "Wide",       "Big", "Small", "Tiny",
        "Very old", "New", "Broken",      "Sad", "Joyful", "Angry",     "Easy", "Hard", "Rough",
        "Strong wind", "Light wind", "Rain", "Watch", "Ignore", "Sleep", "Dull", "Shiny", "Light",
        "Trip", "Station", "Home"
    };
    int answers[] = { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 };
    int score = 0;
    int totalQ = 10;

    for (int q = 0; q < totalQ; q++) {
        bool answered = false;
        while (!WindowShouldClose() && !answered) {
            Vector2 mouse = GetMousePosition();
            BeginDrawing();
            ClearBackground({ 240, 244, 248, 255 });

            // Progress Bar
            DrawRectangle(0, 0, GetScreenWidth(), 10, WHITE);
            DrawRectangle(0, 0, (GetScreenWidth() / totalQ) * (q + 1), 10, { 128, 90, 213, 255 });

            DrawText(TextFormat("Vocabulary Question %d of %d", q + 1, totalQ), 100, 60, 20, GRAY);
            DrawText(qText[q], 100, 120, 45, BLACK);

            for (int i = 0; i < 3; i++) {
                Rectangle opt = { 100, (float)250 + (i * 100), 800, 80 };
                bool hover = CheckCollisionPointRec(mouse, opt);

                DrawRectangleRounded(opt, 0.2f, 10, hover ? Color{ 128, 90, 213, 255 } : WHITE);
                DrawRectangleRoundedLines(opt, 0.2f, 10, 2, hover ? Color{ 128, 90, 213, 255 } : LIGHTGRAY);
                DrawText(opts[q * 3 + i], opt.x + 40, opt.y + 25, 28, hover ? WHITE : DARKGRAY);

                if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (i == answers[q]) score += 10;
                    answered = true;
                }
            }
            EndDrawing();
        }
    }
    showResults("English Vocabulary", score);
}

void englishGrammarQuiz() {
    const char* qText[] = {
        "Past tense of 'Go'?", "Which is a noun?", "I ___ a student.",
        "She ___ to the park yesterday.", "They ___ playing football.",
        "He ___ a book right now.", "We ___ finished yet.", "___ you seen him?"
    };
    const char* opts[] = {
        "Went", "Goed", "Gone",          "Apple", "Run", "Quickly",      "am", "is", "are",
        "goes", "went", "go",            "were", "was", "is",            "is reading", "read", "reads",
        "haven't", "hasn't", "not",      "Have", "Has", "Did"
    };
    int answers[] = { 0, 0, 0, 1, 0, 0, 0, 0 };
    int score = 0;
    int totalQ = 8;

    for (int q = 0; q < totalQ; q++) {
        bool answered = false;
        while (!WindowShouldClose() && !answered) {
            Vector2 mouse = GetMousePosition();
            BeginDrawing();
            ClearBackground({ 240, 244, 248, 255 });

            DrawRectangle(0, 0, GetScreenWidth(), 10, WHITE);
            DrawRectangle(0, 0, (GetScreenWidth() / totalQ) * (q + 1), 10, { 66, 153, 225, 255 });

            DrawText(TextFormat("Grammar Question %d of %d", q + 1, totalQ), 100, 60, 20, GRAY);
            DrawText(qText[q], 100, 120, 45, BLACK);

            for (int i = 0; i < 3; i++) {
                Rectangle opt = { 100, (float)250 + (i * 100), 800, 80 };
                bool hover = CheckCollisionPointRec(mouse, opt);

                DrawRectangleRounded(opt, 0.2f, 10, hover ? Color{ 66, 153, 225, 255 } : WHITE);
                DrawRectangleRoundedLines(opt, 0.2f, 10, 2, hover ? Color{ 66, 153, 225, 255 } : LIGHTGRAY);
                DrawText(opts[q * 3 + i], opt.x + 40, opt.y + 25, 28, hover ? WHITE : DARKGRAY);

                if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (i == answers[q]) score += 12; // 12.5 XP per q
                    answered = true;
                }
            }
            EndDrawing();
        }
    }
    showResults("English Grammar", score);
}

void showResults(const char* topicName, int score) {
    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground({ 45, 55, 72, 255 }); // Darker background for results

        Rectangle box = { GetScreenWidth() / 2 - 250, GetScreenHeight() / 2 - 300, 500, 600 };
        DrawRectangleRounded(box, 0.1f, 10, WHITE);

        DrawText("QUIZ COMPLETE!", box.x + 130, box.y + 50, 30, BLACK);
        DrawText(topicName, box.x + 150, box.y + 100, 20, GRAY);

        // XP Circle
        DrawCircle(box.x + 250, box.y + 280, 80, { 66, 153, 225, 255 });
        DrawText(TextFormat("%d", score), box.x + 215, box.y + 250, 60, WHITE);
        DrawText("XP EARNED", box.x + 195, box.y + 370, 20, { 66, 153, 225, 255 });

        Rectangle btn = { box.x + 100, box.y + 480, 300, 60 };
        bool hover = CheckCollisionPointRec(mouse, btn);
        DrawRectangleRounded(btn, 0.5f, 10, hover ? BLACK : Color{ 66, 153, 225, 255 });
        DrawText("FINISH", btn.x + 110, btn.y + 18, 22, WHITE);

        if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) break;
        EndDrawing();
    }
}