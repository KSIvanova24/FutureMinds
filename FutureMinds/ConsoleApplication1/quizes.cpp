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

        Rectangle logoutBtn = { 20, (float)GetScreenHeight() - 100, 260, 50 };
        bool logoutHover = CheckCollisionPointRec(mouse, logoutBtn);
        DrawRectangleRounded(logoutBtn, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", logoutBtn.x + 85, logoutBtn.y + 15, 20, WHITE);

        if (logoutHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            startingScreen(true);
            break; 
        }

        DrawText("SELECT A CATEGORY", 350, 100, 25, GRAY);

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
        "Quick", "Slow", "Steady", "Tiny", "Large", "Wide", "Big", "Small", "Tiny",
        "Very old", "New", "Broken", "Sad", "Joyful", "Angry", "Easy", "Hard", "Rough",
        "Strong wind", "Light wind", "Rain", "Watch", "Ignore", "Sleep", "Dull", "Shiny", "Light",
        "Trip", "Station", "Home"
    };
    int answers[] = { 0, 0, 0, 0, 1, 0, 1, 0, 0, 0 };
    int userChoices[10];
    int score = 0;
    int totalQ = 10;

    Color primaryColor = { 128, 90, 213, 255 };
    Color bgColor = { 249, 250, 251, 255 };
    Color qTextColor = { 31, 41, 55, 255 };
    Color shadowColor = { 0, 0, 0, 20 };

    for (int q = 0; q < totalQ; q++) {
        bool answered = false;


        while (!WindowShouldClose() && !answered) {
            Vector2 mouse = GetMousePosition();
            BeginDrawing();
            ClearBackground(bgColor);

            DrawRectangle(0, 0, GetScreenWidth(), 8, { 229, 231, 235, 255 });
            DrawRectangle(0, 0, (int)((GetScreenWidth() / (float)totalQ) * (q + 1)), 8, primaryColor);

            Rectangle card = { (float)GetScreenWidth() / 2 - 450, 100, 900, 600 };
            DrawRectangleRounded(Rectangle( { card.x + 4, card.y + 4, card.width, card.height }), 0.05f, 10, shadowColor);
            DrawRectangleRounded(card, 0.05f, 10, WHITE);

            DrawText(TextFormat("VOCABULARY • %d/%d", q + 1, totalQ), (int)card.x + 50, (int)card.y + 40, 16, Fade(primaryColor, 0.8f));

            int textWidth = MeasureText(qText[q], 32);
            DrawText(qText[q], (int)(card.x + (card.width / 2 - textWidth / 2)), (int)card.y + 100, 32, qTextColor);

            for (int i = 0; i < 3; i++) {
                float baseYa = card.y + 180 + (float)(i * 105);
                Rectangle optRect = { card.x + 60, baseYa, 780, 80 };

                bool hover = CheckCollisionPointRec(mouse, optRect);

                float xOffset = hover ? 12.0f : 0.0f;
                Rectangle drawRect = { optRect.x + xOffset, optRect.y, optRect.width, optRect.height };

                Color btnBg = hover ? Fade(primaryColor, 0.05f) : WHITE;
                DrawRectangleRounded(drawRect, 0.2f, 10, btnBg);
                DrawRectangleRoundedLines(drawRect, 0.2f, 10, 2, hover ? primaryColor : Color({ 209, 213, 219, 255 }));

                DrawCircle((int)drawRect.x + 40, (int)drawRect.y + 40, 18, hover ? primaryColor : Color({ 243, 244, 246, 255 }));
                const char* labels[] = { "A", "B", "C" };
                DrawText(labels[i], (int)drawRect.x + 33, (int)drawRect.y + 30, 20, hover ? WHITE : GRAY);

                DrawText(opts[q * 3 + i], (int)drawRect.x + 85, (int)drawRect.y + 26, 24, qTextColor);

                if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    userChoices[q] = i;
                    if (i == answers[q]) score += 10;
                    answered = true;
                }
            }
            EndDrawing();
        }
    }
    showDetailedResults("Vocabulary Quiz", score, qText, opts, answers, userChoices, totalQ);
}
void showDetailedResults(const char* title, int totalScore, const char* questions[], const char* options[], int correctAnswers[], int userChoices[], int count) {
    Color bgCol = { 240, 244, 248, 255 };
    Color headCol = { 45, 55, 72, 255 };
    Color blueBtn = { 66, 153, 225, 255 };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground(bgCol);

        DrawRectangle(0, 0, GetScreenWidth(), 80, headCol);
        DrawText("REVIEW YOUR ANSWERS", 40, 35, 30, WHITE);
        DrawText(TextFormat("Total Score: %d XP", totalScore), GetScreenWidth() - 250, 35, 20, GREEN);

        for (int i = 0; i < count; i++) {
            float yPos = 105.0f + (i * 85.0f);
            Rectangle row = { 50.0f, yPos, (float)GetScreenWidth() - 100.0f, 80.0f };
            DrawRectangleRounded(row, 0.1f, 10, WHITE);

            bool isCorrect = (userChoices[i] == correctAnswers[i]);

            DrawText(TextFormat("%d.", i + 1), (int)row.x + 20, (int)row.y + 25, 20, DARKGRAY);
            DrawText(questions[i], (int)row.x + 60, (int)row.y + 20, 22, BLACK);

            if (isCorrect) {
                DrawText("CORRECT", (int)(row.x + row.width - 150), (int)row.y + 30, 18, DARKGREEN);
            }
            else {
                DrawText("WRONG", (int)(row.x + row.width - 150), (int)row.y + 15, 18, RED);
                const char* cText = options[i * 3 + correctAnswers[i]];
                DrawText(TextFormat("Correct: %s", cText), (int)row.x + 60, (int)row.y + 50, 16, MAROON);
            }
        }

        Rectangle finishBtn = { (float)GetScreenWidth() / 2 - 100, (float)GetScreenHeight() - 100, 200, 50 };
        bool hov = CheckCollisionPointRec(mouse, finishBtn);

        Color finalBtnColor = hov ? BLACK : blueBtn;
        DrawRectangleRounded(finishBtn, 0.5f, 10, finalBtnColor);
        DrawText("BACK TO MENU", (int)finishBtn.x + 35, (int)finishBtn.y + 15, 18, WHITE);

        if (hov && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) break;
        EndDrawing();
    }
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
void englishGrammarQuiz() {
    const char* qText[] = {
        "I ___ to the gym every day.", "She ___ lunch right now.", "We ___ seen that movie yet.",
        "If it rains, I ___ stay home.", "He is taller ___ his brother.", "They ___ playing football yesterday.",
        "I have been living here ___ 2010.", "___ you ever been to Paris?", "This is the ___ book I've read.", "Look! The birds ___."
    };
    const char* opts[] = {
        "go", "goes", "going",              "is having", "has", "have",       "haven't", "hasn't", "not",
        "will", "would", "am",              "than", "then", "from",           "were", "was", "are",
        "since", "for", "in",               "Have", "Has", "Did",             "best", "better", "good",
        "are flying", "flies", "fly"
    };
    int answers[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int userChoices[10];
    int score = 0;
    int totalQ = 10;

    Color primaryColor = { 79, 70, 229, 255 };   
    Color bgColor = { 249, 250, 251, 255 };      
    Color qTextColor = { 31, 41, 55, 255 };      
    Color shadowColor = { 0, 0, 0, 20 };

    for (int q = 0; q < totalQ; q++) {
        bool answered = false;

        while (!WindowShouldClose() && !answered) {
            Vector2 mouse = GetMousePosition();
            BeginDrawing();
            ClearBackground(bgColor);

            DrawRectangle(0, 0, GetScreenWidth(), 8, { 229, 231, 235, 255 });
            DrawRectangle(0, 0, (int)((GetScreenWidth() / (float)totalQ) * (q + 1)), 8, primaryColor);

            Rectangle card = { (float)GetScreenWidth() / 2 - 450, 100, 900, 600 };
            DrawRectangleRounded(Rectangle( { card.x + 4, card.y + 4, card.width, card.height }), 0.05f, 10, shadowColor);
            DrawRectangleRounded(card, 0.05f, 10, WHITE);

            DrawText(TextFormat("QUESTION %d OF %d", q + 1, totalQ), (int)card.x + 50, (int)card.y + 40, 16, Fade(primaryColor, 0.7f));

            int fontSize = 32;
            int textWidth = MeasureText(qText[q], fontSize);
            DrawText(qText[q], (int)(card.x + (card.width / 2 - textWidth / 2)), (int)card.y + 100, fontSize, qTextColor);

            for (int i = 0; i < 3; i++) {
                float baseYa = card.y + 180 + (float)(i * 105);
                Rectangle optRect = { card.x + 60, baseYa, 780, 80 };

                bool hover = CheckCollisionPointRec(mouse, optRect);

                float xOffset = hover ? 10.0f : 0.0f;
                Rectangle drawRect = { optRect.x + xOffset, optRect.y, optRect.width, optRect.height };

                Color btnBg = hover ? Fade(primaryColor, 0.05f) : WHITE;
                DrawRectangleRounded(drawRect, 0.2f, 10, btnBg);
                DrawRectangleRoundedLines(drawRect, 0.2f, 10, 2, hover ? primaryColor : Color({ 209, 213, 219, 255 }));

                DrawCircle((int)drawRect.x + 40, (int)drawRect.y + 40, 18, hover ? primaryColor : Color({ 243, 244, 246, 255 }));
                const char* labels[] = { "A", "B", "C" };
                DrawText(labels[i], (int)drawRect.x + 33, (int)drawRect.y + 30, 20, hover ? WHITE : GRAY);

                DrawText(opts[q * 3 + i], (int)drawRect.x + 85, (int)drawRect.y + 26, 24, qTextColor);

                if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    userChoices[q] = i;
                    if (i == answers[q]) score += 10;
                    answered = true;
                }
            }
            EndDrawing();
        }
    }
    showDetailedResults("Grammar Quiz", score, qText, opts, answers, userChoices, totalQ);
}