#include "quizes.h"
#include "grades.h"
#include "settings.h"
#include "auth.h"
#include "accessData.h"
#include "dashboards.h"
#include "students.h"

using namespace std;

void DrawCategoryCard(Rectangle card, const char* icon, const char* title, const char* subtitle, Color themeColor, Vector2 mouse, bool* clicked) {
    bool hover = CheckCollisionPointRec(mouse, card);
    DrawRectangleRounded(card, 0.1f, 10, WHITE);
    DrawRectangleRoundedLines(card, 0.1f, 10, 4, hover ? themeColor : LIGHTGRAY);
    DrawCircle((int)card.x + 200, (int)card.y + 110, 60, Fade(themeColor, 0.1f));
    DrawText(icon, (int)card.x + 185, (int)card.y + 85, 60, themeColor);
    DrawText(title, (int)card.x + 130, (int)card.y + 190, 32, BLACK);
    DrawText(subtitle, (int)card.x + 80, (int)card.y + 230, 18, GRAY);

    Rectangle btn = { card.x + 50, card.y + 280, 300, 50 };
    bool btnHov = CheckCollisionPointRec(mouse, btn);
    DrawRectangleRounded(btn, 0.5f, 10, btnHov ? BLACK : themeColor);
    DrawText("START", (int)btn.x + 110, (int)btn.y + 15, 22, WHITE);
    if (btnHov && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) *clicked = true;
}




void englishGrammarQuiz() {
    const char* qText[] = {
        "I ___ to the gym every day.", "She ___ lunch right now.", "We ___ seen that movie yet.",
        "If it rains, I ___ stay home.", "He is taller ___ his brother.", "They ___ playing football yesterday.",
        "I have been living here ___ 2010.", "___ you ever been to Paris?", "This is the ___ book I've read.", "Look! The birds ___."
    };
    const char* opts[] = {
        "go", "goes", "going", "is having", "has", "have", "haven't", "hasn't", "not",
        "will", "would", "am", "than", "then", "from", "were", "was", "are",
        "since", "for", "in", "Have", "Has", "Did", "best", "better", "good",
        "are flying", "flies", "fly"
    };
    int answers[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
    int userChoices[10], score = 0, totalQ = 10;
    Color primaryColor = { 79, 70, 229, 255 };

    for (int q = 0; q < totalQ; q++) {
        bool answered = false;

        while (!WindowShouldClose() && !answered) {
            Vector2 mouse = GetMousePosition();
            BeginDrawing();
            ClearBackground({ 249, 250, 251, 255 });

            DrawRectangle(0, 0, GetScreenWidth(), 8, LIGHTGRAY);
            DrawRectangle(0, 0, (int)((GetScreenWidth() / (float)totalQ) * (q + 1)), 8, primaryColor);

            Rectangle card = { (float)GetScreenWidth() / 2 - 450, 100, 900, 600 };
            DrawRectangleRounded(card, 0.05f, 10, WHITE);
            DrawText(qText[q], (int)card.x + 50, (int)card.y + 100, 30, BLACK);

            for (int i = 0; i < 3; i++) {
                Rectangle opt = { card.x + 60, card.y + 200 + (i * 100), 780, 80 };
                bool hov = CheckCollisionPointRec(mouse, opt);
                DrawRectangleRounded(opt, 0.2f, 10, hov ? Fade(primaryColor, 0.1f) : WHITE);
                DrawRectangleRoundedLines(opt, 0.2f, 10, 2, hov ? primaryColor : LIGHTGRAY);
                DrawText(opts[q * 3 + i], (int)opt.x + 50, (int)opt.y + 25, 24, BLACK);

                if (hov && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    userChoices[q] = i;
                    if (i == answers[q]) score += 10;
                    answered = true;
                }
            }
            EndDrawing();
        }
    }
    saveQuizResult(currentUser, "Grammar", score);
    showDetailedResults("Grammar Quiz", score, qText, opts, answers, userChoices, totalQ);
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
    int userChoices[10], score = 0, totalQ = 10;
    Color primaryColor = { 128, 90, 213, 255 };

    for (int q = 0; q < totalQ; q++) {
        bool answered = false;

        while (!WindowShouldClose() && !answered) {
            Vector2 mouse = GetMousePosition();
            BeginDrawing();
            ClearBackground({ 249, 250, 251, 255 });

            Rectangle card = { (float)GetScreenWidth() / 2 - 450, 100, 900, 600 };
            DrawRectangleRounded(card, 0.05f, 10, WHITE);
            DrawText(qText[q], (int)card.x + 50, (int)card.y + 100, 32, BLACK);

            for (int i = 0; i < 3; i++) {
                Rectangle opt = { card.x + 60, card.y + 200 + (i * 100), 780, 80 };
                bool hov = CheckCollisionPointRec(mouse, opt);
                DrawRectangleRounded(opt, 0.2f, 10, hov ? Fade(primaryColor, 0.1f) : WHITE);
                DrawRectangleRoundedLines(opt, 0.2f, 10, 2, hov ? primaryColor : LIGHTGRAY);
                DrawText(opts[q * 3 + i], (int)opt.x + 50, (int)opt.y + 25, 24, BLACK);

                if (hov && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    userChoices[q] = i;
                    if (i == answers[q]) score += 10;
                    answered = true;
                }
            }
            EndDrawing();
        }
    }

    saveQuizResult(currentUser, "Vocabulary", score);
    showDetailedResults("Vocabulary Quiz", score, qText, opts, answers, userChoices, totalQ);
}

void readingQuiz() {
    const char* qText[] = {
        "John loves reading. He reads every night. When does he read?", 
        "The train leaves at 5 PM. What time does it leave?",
        "It was raining, so Maria took an umbrella. Why?",
        "The cat slept on the red rug. Where was the cat?",
        "They went to Italy last summer. When did they go?",
        "The cake smells delicious. How is the cake?",
        "He forgot his keys at home. What did he forget?",
        "The movie starts in 10 minutes. How soon does it start?",
        "The library is closed on Sundays. Can you go Sunday?",
        "The dog barked at the mailman. Who did it bark at?"
    };
    const char* opts[] = {
        "Morning", "Night", "Afternoon",
        "5 PM", "6 PM", "4 PM",
        "It was sunny", "It was raining", "She was cold",
        "Chair", "Red rug", "Garden",
        "Last winter", "Last summer", "Yesterday",
        "Bad", "Good (Delicious)", "Ugly",
        "Wallet", "Keys", "Phone",
        "10 mins", "1 hour", "Tomorrow",
        "Yes", "No", "Maybe",
        "Mailman", "Cat", "Car"
    };
    int answers[] = { 1, 0, 1, 1, 1, 1, 1, 0, 1, 0 };
    int userChoices[10], score = 0, totalQ = 10;
    Color primaryColor = { 56, 178, 172, 255 };

    for (int q = 0; q < totalQ; q++) {
        bool answered = false;

        while (!WindowShouldClose() && !answered) {
            Vector2 mouse = GetMousePosition();
            BeginDrawing();
            ClearBackground({ 249, 250, 251, 255 });

            Rectangle card = { (float)GetScreenWidth() / 2 - 450, 100, 900, 600 };
            DrawRectangleRounded(card, 0.05f, 10, WHITE);
            DrawText(qText[q], (int)card.x + 50, (int)card.y + 100, 24, BLACK);

            for (int i = 0; i < 3; i++) {
                Rectangle opt = { card.x + 60, card.y + 200 + (i * 100), 780, 80 };
                bool hov = CheckCollisionPointRec(mouse, opt);
                DrawRectangleRounded(opt, 0.2f, 10, hov ? Fade(primaryColor, 0.1f) : WHITE);
                DrawRectangleRoundedLines(opt, 0.2f, 10, 2, hov ? primaryColor : LIGHTGRAY);
                DrawText(opts[q * 3 + i], (int)opt.x + 50, (int)opt.y + 25, 24, BLACK);

                if (hov && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    userChoices[q] = i;
                    if (i == answers[q]) score += 10;
                    answered = true;
                }
            }
            EndDrawing();
        }
    }
    saveQuizResult(currentUser, "Reading", score);
    showDetailedResults("Reading Quiz", score, qText, opts, answers, userChoices, totalQ);
}

void idiomsQuiz() {
    const char* qText[] = {
        "What does 'Piece of cake' mean?", "What does 'Bite the bullet' mean?", 
        "What does 'Break a leg' mean?", "What does 'Under the weather' mean?",
        "What does 'Spill the beans' mean?", "Complete: 'Once in a blue ___'",
        "Complete: 'Cry over spilled ___'", "What does 'Hit the sack' mean?",
        "What does 'Costs an arm and a leg' mean?", "Complete: 'Burn the midnight ___'"
    };
    const char* opts[] = {
        "Hard", "Very Easy", "Sweet",
        "Face hard times", "Eat candy", "Run",
        "Good luck", "Bad luck", "Accident",
        "Sunny", "Sick", "Rich",
        "Secret reveal", "Cook", "Clean",
        "Moon", "Sun", "Sky",
        "Water", "Juice", "Milk",
        "Sleep", "Punch", "Run",
        "Cheap", "Expensive", "Free",
        "Oil", "Candle", "Gas"
    };
    int answers[] = { 1, 0, 0, 1, 0, 0, 2, 0, 1, 0 };
    int userChoices[10], score = 0, totalQ = 10;
    Color primaryColor = { 237, 137, 54, 255 };

    for (int q = 0; q < totalQ; q++) {
        bool answered = false;

        while (!WindowShouldClose() && !answered) {
            Vector2 mouse = GetMousePosition();
            BeginDrawing();
            ClearBackground({ 249, 250, 251, 255 });

            Rectangle card = { (float)GetScreenWidth() / 2 - 450, 100, 900, 600 };
            DrawRectangleRounded(card, 0.05f, 10, WHITE);
            DrawText(qText[q], (int)card.x + 50, (int)card.y + 100, 30, BLACK);

            for (int i = 0; i < 3; i++) {
                Rectangle opt = { card.x + 60, card.y + 200 + (i * 100), 780, 80 };
                bool hov = CheckCollisionPointRec(mouse, opt);
                DrawRectangleRounded(opt, 0.2f, 10, hov ? Fade(primaryColor, 0.1f) : WHITE);
                DrawRectangleRoundedLines(opt, 0.2f, 10, 2, hov ? primaryColor : LIGHTGRAY);
                DrawText(opts[q * 3 + i], (int)opt.x + 50, (int)opt.y + 25, 24, BLACK);

                if (hov && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    userChoices[q] = i;
                    if (i == answers[q]) score += 10;
                    answered = true;
                }
            }
            EndDrawing();
        }
    }
    saveQuizResult(currentUser, "Idioms", score);
    showDetailedResults("Idioms Quiz", score, qText, opts, answers, userChoices, totalQ);
}


void showDetailedResults(const char* title, int totalScore, const char* questions[], const char* options[], int correctAnswers[], int userChoices[], int count) {
    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground({ 240, 244, 248, 255 });
        DrawRectangle(0, 0, GetScreenWidth(), 80, { 45, 55, 72, 255 });
        DrawText(TextFormat("REVIEW: %s", title), 40, 40, 30, WHITE);
        DrawText(TextFormat("SCORE: %d XP", totalScore), GetScreenWidth() - 200, 40, 22, GREEN);

        for (int i = 0; i < count; i++) {
            Rectangle row = { 50, 105.0f + (i * 85), (float)GetScreenWidth() - 100, 80 };
            DrawRectangleRounded(row, 0.1f, 10, WHITE);
            bool correct = (userChoices[i] == correctAnswers[i]);

            DrawText(questions[i], (int)row.x + 20, (int)row.y + 20, 20, BLACK);
            if (correct) {
                DrawText("CORRECT", (int)row.x + 800, (int)row.y + 30, 18, DARKGREEN);
            }
            else {
                DrawText("WRONG", (int)row.x + 800, (int)row.y + 15, 18, RED);
                DrawText(TextFormat("Correct: %s", options[i * 3 + correctAnswers[i]]), (int)row.x + 20, (int)row.y + 50, 16, MAROON);
            }
        }

        Rectangle btn = { (float)GetScreenWidth() / 2 - 100, (float)GetScreenHeight() - 100, 200, 50 };
        bool hov = CheckCollisionPointRec(mouse, btn);
        DrawRectangleRounded(btn, 0.5f, 10, hov ? BLACK : Color{ 66, 153, 225, 255 });
        DrawText("BACK TO MENU", (int)btn.x + 35, (int)btn.y + 15, 18, WHITE);

        if (hov && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) break;
        EndDrawing();
    }
}

void quizes() {
    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 66, 153, 225, 255 };
    Color grammarColor = { 66, 153, 225, 255 };
    Color vocabColor = { 128, 90, 213, 255 };
    Color readingColor = { 56, 178, 172, 255 };
    Color idiomsColor = { 237, 137, 54, 255 };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        bool isAdmin = (string(currentUser) == "admin");

        BeginDrawing();
        ClearBackground({ 240, 244, 248, 255 });

        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        if (isAdmin) {

            Rectangle dashBtn = { 0, 150, 300, 60 };
            if (CheckCollisionPointRec(mouse, dashBtn)) {
                DrawRectangleRec(dashBtn, Fade(accentColor, 0.3f));
                DrawRectangle(0, 150, 5, 60, accentColor);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { teacherDashboard(); return; }
            }
            DrawText("Dashboard", 60, 165, 24, WHITE);

            Rectangle studentsBtn = { 0, 220, 300, 60 };
            if (CheckCollisionPointRec(mouse, studentsBtn)) {
                DrawRectangleRec(studentsBtn, Fade(accentColor, 0.3f));
                DrawRectangle(0, 220, 5, 60, accentColor);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { viewAllStudents(); return; }
            }
            DrawText("Students", 60, 235, 24, WHITE);

            Rectangle gBtn = { 0, 290, 300, 60 };
            if (CheckCollisionPointRec(mouse, gBtn)) {
                DrawRectangleRec(gBtn, Fade(accentColor, 0.3f));
                DrawRectangle(0, 290, 5, 60, accentColor);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { gradesTeacher(); return; }
            }
            DrawText("Grades", 60, 305, 24, WHITE);

            Rectangle quizBtn = { 0, 360, 300, 60 };
            DrawRectangleRec(quizBtn, Fade(accentColor, 0.3f));
            DrawRectangle(0, 360, 5, 60, accentColor);
            DrawText("Quizzes", 60, 375, 24, WHITE);

            Rectangle setBtn = { 0, 430, 300, 60 };
            if (CheckCollisionPointRec(mouse, setBtn)) {
                DrawRectangleRec(setBtn, Fade(accentColor, 0.3f));
                DrawRectangle(0, 430, 5, 60, accentColor);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { settingsTeacher(); return; }
            }
            DrawText("Settings", 60, 445, 24, WHITE);
        }
        else {

            Rectangle dashBtn = { 0, 150, 300, 60 };
            if (CheckCollisionPointRec(mouse, dashBtn)) {
                DrawRectangleRec(dashBtn, Fade(accentColor, 0.3f));
                DrawRectangle(0, 150, 5, 60, accentColor);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { studentDashboard(); return; }
            }
            DrawText("Dashboard", 60, 165, 24, WHITE);

            Rectangle quizBtn = { 0, 220, 300, 60 };
            DrawRectangleRec(quizBtn, Fade(accentColor, 0.3f));
            DrawRectangle(0, 220, 5, 60, accentColor);
            DrawText("Quizzes", 60, 235, 24, WHITE);

            Rectangle gBtn = { 0, 290, 300, 60 };
            if (CheckCollisionPointRec(mouse, gBtn)) {
                DrawRectangleRec(gBtn, Fade(accentColor, 0.3f));
                DrawRectangle(0, 290, 5, 60, accentColor);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { gradesStudent(); return; }
            }
            DrawText("Grades", 60, 305, 24, WHITE);

            Rectangle setBtn = { 0, 360, 300, 60 };
            if (CheckCollisionPointRec(mouse, setBtn)) {
                DrawRectangleRec(setBtn, Fade(accentColor, 0.3f));
                DrawRectangle(0, 360, 5, 60, accentColor);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { settingsStudent(); return; }
            }
            DrawText("Settings", 60, 375, 24, WHITE);
        }

        Rectangle logoutBtn = { 20, (float)GetScreenHeight() - 100, 260, 50 };
        bool logoutHover = CheckCollisionPointRec(mouse, logoutBtn);
        DrawRectangleRounded(logoutBtn, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", (int)logoutBtn.x + 85, (int)logoutBtn.y + 15, 20, WHITE);

        if (logoutHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            startingScreen(true);
            return;
        }

        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);

        DrawText("SELECT A CATEGORY", 350, 50, 25, GRAY);

        bool startGrammar = false;
        DrawCategoryCard({ 350, 100, 400, 350 }, "G", "Grammar", "Master tenses & structure", grammarColor, mouse, &startGrammar);
        if (startGrammar) englishGrammarQuiz();

        bool startVocab = false;
        DrawCategoryCard({ 780, 100, 400, 350 }, "V", "Vocabulary", "Expand your dictionary", vocabColor, mouse, &startVocab);
        if (startVocab) englishVocabQuiz();

        bool startReading = false;
        DrawCategoryCard({ 350, 480, 400, 350 }, "R", "Reading", "Read and understand", readingColor, mouse, &startReading);
        if (startReading) readingQuiz();

        bool startIdioms = false;
        DrawCategoryCard({ 780, 480, 400, 350 }, "I", "Idioms", "Slang & expressions", idiomsColor, mouse, &startIdioms);
        if (startIdioms) idiomsQuiz();

        EndDrawing();
    }
}
