#include "quizes.h"

void englishGrammarQuiz() {
    const char* questions[] = { "Past tense of 'Go'?", "Which is a noun?", "I ___ a student." };
    const char* options[] = { "Went", "Goed", "Gone", "Run", "Apple", "Quickly", "is", "are", "am" };
    int answers[] = { 0, 1, 2 };
    int score = 0;

    for (int q = 0; q < 3; q++) {
        bool answered = false;
        while (!WindowShouldClose() && !answered) {
            Vector2 mouse = GetMousePosition();
            BeginDrawing();
            ClearBackground({ 240, 244, 248, 255 });

            DrawText("English Grammar", 100, 50, 25, GRAY);
            DrawText(questions[q], 100, 150, 40, BLACK);

            for (int i = 0; i < 3; i++) {
                Rectangle opt = { 100, (float)300 + (i * 110), 600, 80 };
                bool hover = CheckCollisionPointRec(mouse, opt);
                DrawRectangleRounded(opt, 0.2f, 10, hover ? Color({ 66, 153, 225, 255 }) : WHITE);
                DrawRectangleRoundedLines(opt, 0.2f, 10, 2, LIGHTGRAY);
                DrawText(options[q * 3 + i], opt.x + 30, opt.y + 25, 25, hover ? WHITE : BLACK);

                if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (i == answers[q]) score += 10;
                    answered = true;
                }
            }
            EndDrawing();
        }
    }
    showResults("English Grammar", score);
}

void englishVocabQuiz() {
    const char* questions[] = { "Synonym of 'Fast'?", "Opposite of 'Big'?", "A 'huge' thing is..." };
    const char* options[] = { "Quick", "Slow", "Hard", "Small", "Large", "Thin", "Big", "Small", "Tiny" };
    int answers[] = { 0, 0, 0 };
    int score = 0;

    for (int q = 0; q < 3; q++) {
        bool answered = false;
        while (!WindowShouldClose() && !answered) {
            Vector2 mouse = GetMousePosition();
            BeginDrawing();
            ClearBackground({ 240, 244, 248, 255 });

            DrawText("English Vocabulary", 100, 50, 25, GRAY);
            DrawText(questions[q], 100, 150, 40, BLACK);

            for (int i = 0; i < 3; i++) {
                Rectangle opt = { 100, (float)300 + (i * 110), 600, 80 };
                bool hover = CheckCollisionPointRec(mouse, opt);
                DrawRectangleRounded(opt, 0.2f, 10, hover ? Color({ 255, 105, 180, 255 }) : WHITE);
                DrawRectangleRoundedLines(opt, 0.2f, 10, 2, LIGHTGRAY);
                DrawText(options[q * 3 + i], opt.x + 30, opt.y + 25, 25, hover ? WHITE : BLACK);

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


void quizes() {
    Color cardBg = { 45, 45, 65, 255 };
    Color grammarColor = { 66, 153, 225, 255 };
    Color vocabColor = { 255, 105, 180, 255 };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground({ 240, 244, 248, 255 });

        DrawText("PICK YOUR CHALLENGE", 810, 150, 30, GRAY);

        // --- Card 1: Grammar ---
        Rectangle card1 = { 450, 250, 450, 500 };
        bool hov1 = CheckCollisionPointRec(mouse, card1);
        DrawRectangleRounded(card1, 0.08f, 10, hov1 ? Fade(grammarColor, 0.1f) : WHITE);
        DrawRectangleRoundedLines(card1, 0.08f, 10, 3, hov1 ? grammarColor : LIGHTGRAY);
        DrawText("English Grammar", 550, 450, 30, BLACK);

        Rectangle btn1 = { 525, 630, 300, 60 };
        DrawRectangleRounded(btn1, 0.5f, 10, CheckCollisionPointRec(mouse, btn1) ? BLACK : grammarColor);
        DrawText("START", btn1.x + 115, btn1.y + 18, 22, WHITE);
        if (CheckCollisionPointRec(mouse, btn1) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) englishGrammarQuiz();

        // --- Card 2: Vocabulary ---
        Rectangle card2 = { 1020, 250, 450, 500 };
        bool hov2 = CheckCollisionPointRec(mouse, card2);
        DrawRectangleRounded(card2, 0.08f, 10, hov2 ? Fade(vocabColor, 0.1f) : WHITE);
        DrawRectangleRoundedLines(card2, 0.08f, 10, 3, hov2 ? vocabColor : LIGHTGRAY);
        DrawText("English Vocab", 1140, 450, 30, BLACK);

        Rectangle btn2 = { 1095, 630, 300, 60 };
        DrawRectangleRounded(btn2, 0.5f, 10, CheckCollisionPointRec(mouse, btn2) ? BLACK : vocabColor);
        DrawText("START", btn2.x + 115, btn2.y + 18, 22, WHITE);
        if (CheckCollisionPointRec(mouse, btn2) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) englishVocabQuiz();

        if (IsKeyPressed(KEY_ESCAPE)) break;
        EndDrawing();
    }
}

void showResults(const char* topicName, int score) {
    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground({ 240, 244, 248, 255 });

        Rectangle box = { 710, 300, 500, 400 };
        DrawRectangleRounded(box, 0.1f, 10, WHITE);
        DrawRectangleRoundedLines(box, 0.1f, 10, 3, { 66, 153, 225, 255 });

        DrawText("QUIZ FINISHED", 840, 350, 30, DARKGRAY);
        DrawText(topicName, 800, 400, 25, GRAY);
        DrawText(TextFormat("%d XP", score), 890, 470, 50, { 66, 153, 225, 255 });

        Rectangle btn = { 810, 580, 300, 60 };
        bool hover = CheckCollisionPointRec(mouse, btn);
        DrawRectangleRounded(btn, 0.5f, 10, hover ? BLACK : Color({ 45, 55, 72, 255 }));
        DrawText("CONTINUE", btn.x + 85, btn.y + 18, 22, WHITE);

        if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) break;

        EndDrawing();
    }
}