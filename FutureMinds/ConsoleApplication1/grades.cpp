#include "settings.h"
#include "accessData.h"
#include "quizes.h"
#include "auth.h"
#include "dashboards.h"
#include "grades.h"

// Helper function to draw menu items without using auto/lambdas
void DrawMenuOption(Rectangle rect, const char* text, int index, Vector2 mouse, Color accentColor, Color borderColor, Color textColor, Color bgWhite) {
    bool hover = CheckCollisionPointRec(mouse, rect);
    DrawRectangleRounded(rect, 0.15f, 10, hover ? Fade(accentColor, 0.1f) : bgWhite);
    DrawRectangleRoundedLines(rect, 0.15f, 10, 2, hover ? accentColor : borderColor);
    DrawText(TextFormat("%d. %s", index, text), (int)rect.x + 30, (int)rect.y + 25, 30, hover ? accentColor : textColor);
}

void gradesTeacher() {
    Color bgWhite = { 240, 242, 245, 255 };
    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 66, 153, 225, 255 }; // Teacher Blue
    Color textColor = { 20, 20, 20, 255 };
    Color borderColor = { 200, 200, 205, 255 };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        // Sidebar Rectangles
        Rectangle dashBtn = { 0, 150, 300, 60 };
        Rectangle studentsBtn = { 0, 220, 300, 60 };
        Rectangle gBtn = { 0, 290, 300, 60 };
        Rectangle qBtn = { 0, 360, 300, 60 };
        Rectangle sBtn = { 0, 430, 300, 60 };
        Rectangle logoutBtn = { 20, (float)GetScreenHeight() - 100, 260, 50 };

        // Main Content Rectangles
        Rectangle card = { 350, 120, 1100, 600 };
        Rectangle viewGradesRect = { card.x + 50, card.y + 150, 1000, 80 };
        Rectangle addGradeRect = { card.x + 50, card.y + 250, 1000, 80 };

        // Interaction Logic
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, dashBtn)) teacherDashboard();
            if (CheckCollisionPointRec(mouse, studentsBtn)) { /* Go to students */ }
            if (CheckCollisionPointRec(mouse, qBtn)) quizes();
            if (CheckCollisionPointRec(mouse, sBtn)) settingsTeacher();
            if (CheckCollisionPointRec(mouse, logoutBtn)) startingScreen(true);

            if (CheckCollisionPointRec(mouse, viewGradesRect)) { /* Logic */ }
            if (CheckCollisionPointRec(mouse, addGradeRect)) { /* Logic */ }
        }

        BeginDrawing();
        ClearBackground(bgWhite);

        // --- SIDEBAR ---
        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        // Sidebar Navigation Rendering
        Rectangle navBtns[] = { dashBtn, studentsBtn, gBtn, qBtn, sBtn };
        const char* navLabels[] = { "Dashboard", "Students", "Grades", "Quizzes", "Settings" };

        for (int i = 0; i < 5; i++) {
            bool hover = CheckCollisionPointRec(mouse, navBtns[i]);
            bool isActive = (i == 2); // Grades is index 2
            if (hover || isActive) {
                DrawRectangleRec(navBtns[i], Fade(accentColor, 0.3f));
                DrawRectangle(navBtns[i].x, navBtns[i].y, 5, navBtns[i].height, accentColor);
            }
            DrawText(navLabels[i], 60, (int)navBtns[i].y + 15, 24, WHITE);
        }

        bool logoutHover = CheckCollisionPointRec(mouse, logoutBtn);
        DrawRectangleRounded(logoutBtn, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", (int)logoutBtn.x + 85, (int)logoutBtn.y + 15, 20, WHITE);

        // --- MAIN CONTENT ---
        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);
        DrawText("TEACHER PORTAL", 330, 25, 25, sideBarColor);

        // Management Card
        DrawRectangleRounded(card, 0.02f, 10, WHITE);
        DrawRectangleRoundedLines(card, 0.02f, 10, 2, borderColor);

        DrawText("GRADE MANAGEMENT", (int)card.x + 50, (int)card.y + 40, 40, textColor);
        DrawLineEx({ card.x + 50, card.y + 95 }, { card.x + 1050, card.y + 95 }, 2, borderColor);

        // Only Two Options as requested
        DrawMenuOption(viewGradesRect, "View Student Grades", 1, mouse, accentColor, borderColor, textColor, bgWhite);
        DrawMenuOption(addGradeRect, "Add/Modify Grades", 2, mouse, accentColor, borderColor, textColor, bgWhite);

        // Footer
        DrawText("Terms of Service", 500, 1000, 20, GRAY);
        DrawText("Privacy Policy", 750, 1000, 20, GRAY);
        DrawText("Support", 1000, 1000, 20, GRAY);

        EndDrawing();
    }
}

void gradesStudent()
{
    // Design Colors (Matching Settings/Dashboard)
    Color bgWhite = { 240, 242, 245, 255 };
    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 0, 110, 230, 255 }; // Student Blue
    Color textColor = { 20, 20, 20, 255 };
    Color borderColor = { 200, 200, 205, 255 };

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        // Sidebar Rectangles
        Rectangle dashBtn = { 0, 150, 300, 60 };
        Rectangle qBtn = { 0, 220, 300, 60 };
        Rectangle gBtn = { 0, 290, 300, 60 }; // Active Page
        Rectangle sBtn = { 0, 360, 300, 60 };
        Rectangle logoutBtn = { 20, (float)GetScreenHeight() - 100, 260, 50 };

        // Main Content Rectangles
        Rectangle card = { 350, 120, 1100, 600 };
        Rectangle viewGradesRect = { card.x + 50, card.y + 150, 1000, 80 };
        Rectangle avgGradeRect = { card.x + 50, card.y + 250, 1000, 80 };

        // Logic for Clicks
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (CheckCollisionPointRec(mouse, dashBtn)) studentDashboard();
            if (CheckCollisionPointRec(mouse, qBtn)) quizes();
            if (CheckCollisionPointRec(mouse, sBtn)) settingsStudent();
            if (CheckCollisionPointRec(mouse, logoutBtn)) startingScreen(true);

        }

        BeginDrawing();
        ClearBackground(bgWhite);

        // --- SIDEBAR RENDERING ---
        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        // Navigation Menu
        Rectangle navBtns[] = { dashBtn, qBtn, gBtn, sBtn };
        const char* navLabels[] = { "Dashboard", "Quizzes", "Grades", "Settings" };

        for (int i = 0; i < 4; i++) {
            bool hover = CheckCollisionPointRec(mouse, navBtns[i]);
            bool isActive = (i == 2); // Grades is index 2
            if (hover || isActive) {
                DrawRectangleRec(navBtns[i], Fade(accentColor, 0.3f));
                DrawRectangle(navBtns[i].x, navBtns[i].y, 5, navBtns[i].height, accentColor);
            }
            DrawText(navLabels[i], 60, (int)navBtns[i].y + 15, 24, WHITE);
        }

        bool logoutHover = CheckCollisionPointRec(mouse, logoutBtn);
        DrawRectangleRounded(logoutBtn, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", (int)logoutBtn.x + 85, (int)logoutBtn.y + 15, 20, WHITE);

        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);
        DrawText("STUDENT PORTAL", 330, 25, 25, sideBarColor);

        DrawRectangleRounded(card, 0.02f, 10, WHITE);
        DrawRectangleRoundedLines(card, 0.02f, 10, 2, borderColor);

        DrawText("GRADE MANAGEMENT", (int)card.x + 50, (int)card.y + 40, 40, textColor);
        DrawLineEx({ card.x + 50, card.y + 95 }, { card.x + 1050, card.y + 95 }, 2, borderColor);

        // Action Options
        DrawMenuOption(viewGradesRect, "View My Grades", 1, mouse, accentColor, borderColor, textColor, bgWhite);
        if (CheckCollisionPointRec(mouse, viewGradesRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            viewStudentGradesList();
        }
        DrawMenuOption(avgGradeRect, "Calculate My Average", 2, mouse, accentColor, borderColor, textColor, bgWhite);
        if (CheckCollisionPointRec(mouse, avgGradeRect) && IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            calculateAverage();
        }
        // Footer links
        DrawText("Terms of Service", 500, 1000, 20, GRAY);
        DrawText("Privacy Policy", 750, 1000, 20, GRAY);
        DrawText("Support", 1000, 1000, 20, GRAY);

        EndDrawing();
    }
}

void viewStudentGradesList() {
    Color bgWhite = { 240, 242, 245, 255 };
    Color headerCol = { 45, 55, 72, 255 };
    Color accentColor = { 0, 110, 230, 255 };

    struct GradeEntry { string name; string score; };
    vector<GradeEntry> myGrades;

    ifstream file("../data/notebook.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        getline(ss, name, ',');
        if (name == currentUser) {
            string entry;
            while (getline(ss, entry, ',')) {
                size_t lastSpace = entry.find_last_of(' ');
                if (lastSpace != string::npos) {
                    myGrades.push_back({ entry.substr(0, lastSpace), entry.substr(lastSpace + 1) });
                }
            }
            break; 
        }
    }
    file.close();

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground(bgWhite);

        DrawRectangle(0, 0, GetScreenWidth(), 100, headerCol);
        DrawText("MY PERFORMANCE", 40, 35, 30, WHITE);
        DrawText(currentUser, GetScreenWidth() - MeasureText(currentUser, 20) - 40, 40, 20, Fade(WHITE, 0.7f));

        Rectangle backBtn = { 40, 130, 120, 40 };
        bool backHover = CheckCollisionPointRec(mouse, backBtn);
        DrawRectangleRounded(backBtn, 0.5f, 10, backHover ? BLACK : DARKGRAY);
        DrawText("< BACK", (int)backBtn.x + 25, (int)backBtn.y + 12, 18, WHITE);

        if (backHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) break;

        if (myGrades.empty()) {
            DrawText("No grades recorded yet. Take a quiz!", GetScreenWidth() / 2 - 150, GetScreenHeight() / 2, 20, GRAY);
        }
        else {
            for (int i = 0; i < myGrades.size(); i++) {
                float yPos = 200 + (i * 90);
                Rectangle row = { 100, yPos, (float)GetScreenWidth() - 200, 75 };
                DrawRectangleRounded({ row.x + 2, row.y + 2, row.width, row.height }, 0.2f, 10, Fade(GRAY, 0.2f));
                DrawRectangleRounded(row, 0.2f, 10, WHITE);

                DrawRectangle(row.x, row.y, 10, row.height, accentColor);
                DrawText(myGrades[i].name.c_str(), (int)row.x + 40, (int)row.y + 25, 25, BLACK);
                int scoreVal = stoi(myGrades[i].score);
                Color scoreColor = (scoreVal >= 70) ? DARKGREEN : (scoreVal >= 40 ? ORANGE : RED);

                DrawText(TextFormat("%s XP", myGrades[i].score.c_str()), (int)row.x + row.width - 150, (int)row.y + 25, 25, scoreColor);
            }
        }
        EndDrawing();
    }
}

void calculateAverage() {
    Color bgWhite = { 240, 242, 245, 255 };
    Color headerCol = { 45, 55, 72, 255 };
    Color grammarColor = { 66, 153, 225, 255 };
    Color vocabColor = { 128, 90, 213, 255 };

    float grammarSum = 0, vocabSum = 0;
    int grammarCount = 0, vocabCount = 0;

    ifstream file("../data/notebook.csv");
    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        getline(ss, name, ',');

        if (name == currentUser) {
            string entry;
            while (getline(ss, entry, ',')) {
                size_t lastSpace = entry.find_last_of(' ');
                if (lastSpace != string::npos) {
                    string quizName = entry.substr(0, lastSpace);
                    int score = stoi(entry.substr(lastSpace + 1));

                    if (quizName.find("Grammar") != string::npos) {
                        grammarSum += score;
                        grammarCount++;
                    }
                    else if (quizName.find("Vocabulary") != string::npos || quizName.find("Vocab") != string::npos) {
                        vocabSum += score;
                        vocabCount++;
                    }
                }
            }
            break;
        }
    }
    file.close();

    int avgGrammar = (grammarCount > 0) ? (int)(grammarSum / grammarCount) : 0;
    int avgVocab = (vocabCount > 0) ? (int)(vocabSum / vocabCount) : 0;

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        BeginDrawing();
        ClearBackground(bgWhite);

        DrawRectangle(0, 0, GetScreenWidth(), 100, headerCol);
        DrawText("AVERAGE PERFORMANCE", 40, 35, 30, WHITE);

 
        Rectangle backBtn = { 40, 130, 120, 40 };
        bool backHover = CheckCollisionPointRec(mouse, backBtn);
        DrawRectangleRounded(backBtn, 0.5f, 10, backHover ? BLACK : DARKGRAY);
        DrawText("< BACK", (int)backBtn.x + 25, (int)backBtn.y + 12, 18, WHITE);
        if (backHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) break;

        Rectangle cardGrammar = { (float)GetScreenWidth() / 2 - 450, 250, 400, 300 };
        Rectangle cardVocab = { (float)GetScreenWidth() / 2 + 50, 250, 400, 300 };


        DrawRectangleRounded(cardGrammar, 0.1f, 10, WHITE);
        DrawRectangleRoundedLines(cardGrammar, 0.1f, 10, 3, grammarColor);
        DrawText("GRAMMAR", (int)cardGrammar.x + 100, (int)cardGrammar.y + 40, 30, DARKGRAY);
        DrawLineEx({ cardGrammar.x + 50, cardGrammar.y + 90 }, { cardGrammar.x + 350, cardGrammar.y + 90 }, 2, LIGHTGRAY);

        const char* gScoreText = TextFormat("%d%%", avgGrammar);
        DrawText(gScoreText, (int)cardGrammar.x + 200 - MeasureText(gScoreText, 80) / 2, (int)cardGrammar.y + 150, 80, grammarColor);

 
        DrawRectangleRounded(cardVocab, 0.1f, 10, WHITE);
        DrawRectangleRoundedLines(cardVocab, 0.1f, 10, 3, vocabColor);
        DrawText("VOCABULARY", (int)cardVocab.x + 85, (int)cardVocab.y + 40, 30, DARKGRAY);
        DrawLineEx({ cardVocab.x + 50, cardVocab.y + 90 }, { cardVocab.x + 350, cardVocab.y + 90 }, 2, LIGHTGRAY);

        const char* vScoreText = TextFormat("%d%%", avgVocab);
        DrawText(vScoreText, (int)cardVocab.x + 200 - MeasureText(vScoreText, 80) / 2, (int)cardVocab.y + 150, 80, vocabColor);

        DrawText("Overall Progress is calculated based on completed quiz sessions.",
            GetScreenWidth() / 2 - MeasureText("Overall Progress is calculated based on completed quiz sessions.", 20) / 2,
            650, 20, GRAY);

        EndDrawing();
    }
}