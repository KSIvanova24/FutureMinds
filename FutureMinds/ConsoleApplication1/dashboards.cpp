#include "dashboards.h"
#include "accessData.h"
#include "auth.h"
#include "settings.h"
#include "quizes.h"
#include "grades.h"
#include "students.h"

void saveBadgeToCSV(string studentName, string badgeType) {
    ifstream file("../data/badges.csv");
    vector<string> fileLines;
    string line;
    bool studentFound = false;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string fUser, idioms, grammar, vocabulary, reading;

        getline(ss, fUser, ',');
        getline(ss, idioms, ',');
        getline(ss, grammar, ',');
        getline(ss, vocabulary, ',');
        getline(ss, reading, ',');

        if (fUser == studentName) {
            studentFound = true;
            if (badgeType == "Idioms") idioms = "1";
            if (badgeType == "Grammar") grammar = "1";
            if (badgeType == "Vocabulary") vocabulary = "1";
            if (badgeType == "Reading") reading = "1";

            fileLines.push_back(fUser + "," + idioms + "," + grammar + "," + vocabulary + "," + reading);
        }
        else {
            fileLines.push_back(line);
        }
    }
    file.close();

    if (!studentFound) {
        string i = (badgeType == "Idioms") ? "1" : "0";
        string g = (badgeType == "Grammar") ? "1" : "0";
        string v = (badgeType == "Vocabulary") ? "1" : "0";
        string r = (badgeType == "Reading") ? "1" : "0";
        fileLines.push_back(studentName + "," + i + "," + g + "," + v + "," + r);
    }

    ofstream outFile("../data/badges.csv", ios::trunc);
    for (const auto& l : fileLines) outFile << l << "\n";
    outFile.close();
}

void teacherDashboard()
{
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    SetTargetFPS(60);

    Color bgDark = { 240, 244, 248, 255 };
    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 66, 153, 225, 255 };
    Color textColor = { 45, 55, 72, 255 };
    Color borderColor = { 226, 232, 240, 255 };

    // --- 1. DATA PARSING ---
    float grammarSum = 0, vocabSum = 0, readingSum = 0, idiomsSum = 0;
    int gCount = 0, vCount = 0, rCount = 0, iCount = 0;
    int totalQuizzes = 0;

    ifstream file("../data/notebook.csv");
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string name;
        getline(ss, name, ',');

        string entry;
        while (getline(ss, entry, ',')) {
            size_t lastSpace = entry.find_last_of(' ');
            if (lastSpace != string::npos) {
                string quizName = entry.substr(0, lastSpace);
                int score = stoi(entry.substr(lastSpace + 1));
                totalQuizzes++;

                if (quizName.find("Grammar") != string::npos) { grammarSum += score; gCount++; }
                else if (quizName.find("Vocabulary") != string::npos || quizName.find("Vocab") != string::npos) { vocabSum += score; vCount++; }
                else if (quizName.find("Reading") != string::npos) { readingSum += score; rCount++; }
                else if (quizName.find("Idioms") != string::npos) { idiomsSum += score; iCount++; }
            }
        }
    }
    file.close();

    float avgGrammar = gCount > 0 ? grammarSum / gCount : 0.0f;
    float avgVocab = vCount > 0 ? vocabSum / vCount : 0.0f;
    float avgReading = rCount > 0 ? readingSum / rCount : 0.0f;
    float avgIdioms = iCount > 0 ? idiomsSum / iCount : 0.0f;
    float globalAvg = (avgGrammar + avgVocab + avgReading + avgIdioms) / 4.0f;

    vector<string> studentList;
    ifstream userFile("../data/accounts.csv");
    while (getline(userFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string u, p, r;
        getline(ss, u, ',');
        getline(ss, p, ',');
        getline(ss, r, ',');
        if (r == "student") studentList.push_back(u);
    }
    userFile.close();

    // Student selection tracker
    int selectedStudentIdx = 0;

    // Badge selection tracker (0 = none, 1 = Grammar, 2 = Vocab, 3 = Reading, 4 = Idioms)
    int selectedBadge = 0;

    Texture2D bGrammarTex = LoadTexture("../images/grammar.png");
    Texture2D bVocabTex = LoadTexture("../images/vocab.png");
    Texture2D bReadingTex = LoadTexture("../images/reading.png");
    Texture2D bIdiomsTex = LoadTexture("../images/idioms.png");

    string notificationText = "";
    float notificationTimer = 0.0f;

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        float dt = GetFrameTime();
        if (notificationTimer > 0) notificationTimer -= dt;

        BeginDrawing();
        ClearBackground(bgDark);

        // Sidebar
        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        Rectangle navDash = { 0, 150, 300, 60 };
        DrawRectangleRec(navDash, Fade(accentColor, 0.3f));
        DrawRectangle(0, 150, 5, 60, accentColor);
        DrawText("Dashboard", 60, 165, 24, WHITE);

        Rectangle studentsBtn = { 0, 220, 300, 60 };
        if (CheckCollisionPointRec(mouse, studentsBtn)) { DrawRectangleRec(studentsBtn, Fade(accentColor, 0.2f)); if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { viewAllStudents(); return; } }
        DrawText("Students", 60, 235, 24, WHITE);

        Rectangle gBtn = { 0, 290, 300, 60 };
        if (CheckCollisionPointRec(mouse, gBtn)) { DrawRectangleRec(gBtn, Fade(accentColor, 0.2f)); if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { gradesTeacher(); return; } }
        DrawText("Grades", 60, 305, 24, WHITE);

        Rectangle quizBtn = { 0, 360, 300, 60 };
        if (CheckCollisionPointRec(mouse, quizBtn)) { DrawRectangleRec(quizBtn, Fade(accentColor, 0.2f)); if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { quizes(); return; } }
        DrawText("Quizzes", 60, 375, 24, WHITE);

        Rectangle setBtn = { 0, 430, 300, 60 };
        if (CheckCollisionPointRec(mouse, setBtn)) { DrawRectangleRec(setBtn, Fade(accentColor, 0.2f)); if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { settingsTeacher(); return; } }
        DrawText("Settings", 60, 445, 24, WHITE);

        Rectangle logoutButton = { 20, (float)GetScreenHeight() - 100, 260, 50 };
        if (CheckCollisionPointRec(mouse, logoutButton)) { DrawRectangleRounded(logoutButton, 0.2f, 10, RED); if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) { startingScreen(true); return; } }
        else { DrawRectangleRounded(logoutButton, 0.2f, 10, DARKGRAY); }
        DrawText("Logout", logoutButton.x + 80, logoutButton.y + 15, 20, WHITE);

        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);
        drawUsername(currentUser);

        // Stats Card Metric Placements
        float cardWidth = 350;
        float spacing = (GetScreenWidth() - 300 - (cardWidth * 3)) / 4;
        float startX = 300 + spacing;

        DrawRectangleRounded({ startX, 120, cardWidth, 180 }, 0.05f, 10, WHITE);
        DrawRectangleRoundedLines({ startX, 120, cardWidth, 180 }, 0.05f, 10, 1, borderColor);
        DrawText("ACTIVE STUDENTS", startX + 25, 145, 18, GRAY);
        drawStudentsCount();
        DrawRectangle(startX + 25, 260, cardWidth - 50, 8, Fade(accentColor, 0.3f));
        DrawRectangle(startX + 25, 260, (cardWidth - 50) * 0.7f, 8, accentColor);

        float midX = startX + cardWidth + spacing;
        DrawRectangleRounded({ midX, 120, cardWidth, 180 }, 0.05f, 10, WHITE);
        DrawRectangleRoundedLines({ midX, 120, cardWidth, 180 }, 0.05f, 10, 1, borderColor);
        DrawText("Average grade for the app", midX + 25, 145, 18, GRAY);
        DrawText(TextFormat("%.1f%%", globalAvg), midX + 25, 180, 45, textColor);
        DrawRectangle(midX + 25, 260, cardWidth - 50, 8, Fade(GREEN, 0.3f));
        DrawRectangle(midX + 25, 260, (cardWidth - 50) * (globalAvg / 100.0f), 8, GREEN);

        float endX = startX + (cardWidth + spacing) * 2;
        DrawRectangleRounded({ endX, 120, cardWidth, 180 }, 0.05f, 10, WHITE);
        DrawRectangleRoundedLines({ endX, 120, cardWidth, 180 }, 0.05f, 10, 1, borderColor);
        DrawText("QUIZZES COMPLETED", endX + 25, 145, 18, GRAY);
        DrawText(TextFormat("%i", totalQuizzes), endX + 25, 180, 45, textColor);
        DrawRectangle(endX + 25, 260, cardWidth - 50, 8, Fade(ORANGE, 0.3f));
        DrawRectangle(endX + 25, 260, (cardWidth - 50) * 0.9f, 8, ORANGE);

        // --- ACCREDIT BADGES AREA ---
        Rectangle badgeArea = { startX, 340, GetScreenWidth() - startX - spacing, 600 };
        DrawRectangleRounded(badgeArea, 0.02f, 10, WHITE);
        DrawRectangleRoundedLines(badgeArea, 0.02f, 10, 1, borderColor);

        DrawText("ACCREDIT STUDENT BADGES", badgeArea.x + 40, badgeArea.y + 30, 25, textColor);
        DrawLineEx({ badgeArea.x + 40, badgeArea.y + 70 }, { badgeArea.x + badgeArea.width - 40, badgeArea.y + 70 }, 1, borderColor);

        // --- NEW NO-DROPDOWN STUDENT PICKER ---
        DrawText("Selected Student:", badgeArea.x + 40, badgeArea.y + 100, 18, GRAY);
        Rectangle cycleBox = { badgeArea.x + 40, badgeArea.y + 130, 350, 45 };
        bool cycleHover = CheckCollisionPointRec(mouse, cycleBox);

        DrawRectangleRounded(cycleBox, 0.15f, 10, cycleHover ? Fade(accentColor, 0.1f) : bgDark);
        DrawRectangleRoundedLines(cycleBox, 0.15f, 10, 1, cycleHover ? accentColor : borderColor);

        string displayUser = studentList.empty() ? "No students" : studentList[selectedStudentIdx];
        DrawText(displayUser.c_str(), cycleBox.x + 15, cycleBox.y + 12, 20, textColor);
        DrawText("Click to cycle >", cycleBox.x + cycleBox.width - 150, cycleBox.y + 14, 16, GRAY);

        if (cycleHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !studentList.empty()) {
            selectedStudentIdx = (selectedStudentIdx + 1) % studentList.size(); // Loops infinitely through students
        }

        // --- BADGES RENDER + HOVER EFFECTS ---
        float bWidth = 220;
        float bHeight = 100;
        float bSpacing = (badgeArea.width - 80 - (bWidth * 4)) / 3;
        float badgeStartX = badgeArea.x + 40;
        float badgeStartY = badgeArea.y + 220;

        // 1. Grammar
        Rectangle bGrammar = { badgeStartX, badgeStartY, bWidth, bHeight };
        bool hGrammar = CheckCollisionPointRec(mouse, bGrammar);

        // If selected: thick border. If hovered: slight background color.
        DrawRectangleRounded(bGrammar, 0.15f, 10, (selectedBadge == 1) ? Fade(accentColor, 0.2f) : (hGrammar ? Fade(bgDark, 0.5f) : WHITE));
        DrawRectangleRoundedLines(bGrammar, 0.15f, 10, (selectedBadge == 1) ? 4 : 1, (selectedBadge == 1 || hGrammar) ? accentColor : borderColor);

        if (bGrammarTex.id > 0) DrawTexturePro(bGrammarTex, { 0, 0, (float)bGrammarTex.width, (float)bGrammarTex.height }, { bGrammar.x + 10, bGrammar.y + 10, bGrammar.width - 20, bGrammar.height - 20 }, { 0,0 }, 0.0f, WHITE);

        if (hGrammar && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) selectedBadge = 1;

        // 2. Vocabulary
        Rectangle bVocab = { badgeStartX + bWidth + bSpacing, badgeStartY, bWidth, bHeight };
        bool hVocab = CheckCollisionPointRec(mouse, bVocab);

        DrawRectangleRounded(bVocab, 0.15f, 10, (selectedBadge == 2) ? Fade(GREEN, 0.2f) : (hVocab ? Fade(bgDark, 0.5f) : WHITE));
        DrawRectangleRoundedLines(bVocab, 0.15f, 10, (selectedBadge == 2) ? 4 : 1, (selectedBadge == 2 || hVocab) ? GREEN : borderColor);

        if (bVocabTex.id > 0) DrawTexturePro(bVocabTex, { 0, 0, (float)bVocabTex.width, (float)bVocabTex.height }, { bVocab.x + 10, bVocab.y + 10, bVocab.width - 20, bVocab.height - 20 }, { 0,0 }, 0.0f, WHITE);

        if (hVocab && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) selectedBadge = 2;

        // 3. Reading
        Rectangle bRead = { badgeStartX + (bWidth + bSpacing) * 2, badgeStartY, bWidth, bHeight };
        bool hRead = CheckCollisionPointRec(mouse, bRead);

        DrawRectangleRounded(bRead, 0.15f, 10, (selectedBadge == 3) ? Fade(ORANGE, 0.2f) : (hRead ? Fade(bgDark, 0.5f) : WHITE));
        DrawRectangleRoundedLines(bRead, 0.15f, 10, (selectedBadge == 3) ? 4 : 1, (selectedBadge == 3 || hRead) ? ORANGE : borderColor);

        if (bReadingTex.id > 0) DrawTexturePro(bReadingTex, { 0, 0, (float)bReadingTex.width, (float)bReadingTex.height }, { bRead.x + 10, bRead.y + 10, bRead.width - 20, bRead.height - 20 }, { 0,0 }, 0.0f, WHITE);

        if (hRead && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) selectedBadge = 3;

        // 4. Idioms
        Rectangle bIdioms = { badgeStartX + (bWidth + bSpacing) * 3, badgeStartY, bWidth, bHeight };
        bool hIdioms = CheckCollisionPointRec(mouse, bIdioms);

        DrawRectangleRounded(bIdioms, 0.15f, 10, (selectedBadge == 4) ? Fade(PURPLE, 0.2f) : (hIdioms ? Fade(bgDark, 0.5f) : WHITE));
        DrawRectangleRoundedLines(bIdioms, 0.15f, 10, (selectedBadge == 4) ? 4 : 1, (selectedBadge == 4 || hIdioms) ? PURPLE : borderColor);

        if (bIdiomsTex.id > 0) DrawTexturePro(bIdiomsTex, { 0, 0, (float)bIdiomsTex.width, (float)bIdiomsTex.height }, { bIdioms.x + 10, bIdioms.y + 10, bIdioms.width - 20, bIdioms.height - 20 }, { 0,0 }, 0.0f, WHITE);

        if (hIdioms && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) selectedBadge = 4;


        // --- NEW ACCREDIT SUBMIT BUTTON ---
        Rectangle accreditBtn = { badgeArea.x + 40, badgeStartY + bHeight + 60, 200, 50 };
        bool accreditHover = CheckCollisionPointRec(mouse, accreditBtn);

        // Render disabled button if no badge is clicked yet
        Color btnColor = (selectedBadge == 0) ? LIGHTGRAY : (accreditHover ? BLACK : accentColor);

        DrawRectangleRounded(accreditBtn, 0.2f, 10, btnColor);
        DrawText("Accredit Badge", accreditBtn.x + 25, accreditBtn.y + 15, 20, WHITE);

        if (selectedBadge > 0 && accreditHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            string badgeName = "";
            if (selectedBadge == 1) badgeName = "Grammar";
            if (selectedBadge == 2) badgeName = "Vocabulary";
            if (selectedBadge == 3) badgeName = "Reading";
            if (selectedBadge == 4) badgeName = "Idioms";

            notificationText = TextFormat("Accredited %s badge to %s!", badgeName.c_str(), studentList[selectedStudentIdx].c_str());
            notificationTimer = 3.0f;

            saveBadgeToCSV(studentList[selectedStudentIdx], badgeName);
            selectedBadge = 0; // Reset selected badge
        }


        // Global Notifications
        if (notificationTimer > 0) {
            Rectangle popup = { GetScreenWidth() / 2 - 250, 30, 500, 60 };
            DrawRectangleRounded(popup, 0.5f, 10, GREEN);
            DrawText(notificationText.c_str(), popup.x + (500 - MeasureText(notificationText.c_str(), 20)) / 2, popup.y + 20, 20, WHITE);
        }

        EndDrawing();
    }

    UnloadTexture(bGrammarTex);
    UnloadTexture(bVocabTex);
    UnloadTexture(bReadingTex);
    UnloadTexture(bIdiomsTex);
}


void studentDashboard() {
    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 66, 153, 225, 255 };

    int totalXP = 0;
    ifstream file("../data/notebook.csv");
    string line;

    while (getline(file, line)) {
        stringstream ss(line);
        string name;
        getline(ss, name, ','); // Get username

        if (name == currentUser) {
            string entry;
            // Parse all "QuizName Score" pairs in the row
            while (getline(ss, entry, ',')) {
                size_t lastSpace = entry.find_last_of(' ');
                if (lastSpace != string::npos) {
                    // Extract the score part after the last space and add to total
                    totalXP += stoi(entry.substr(lastSpace + 1));
                }
            }
            break; // Found our user, no need to keep reading
        }
    }
    file.close();

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground({ 240, 244, 248, 255 });

        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        Rectangle navs[] = {
            { 0, 150, 300, 60 },
            { 0, 220, 300, 60 },
            { 0, 290, 300, 60 },
            { 0, 360, 300, 60 }
        };
        const char* labels[] = { "Dashboard", "Quizzes", "Grades", "Settings" };

        for (int i = 0; i < 4; i++) {
            bool hover = CheckCollisionPointRec(mouse, navs[i]);
            if (i == 0 || hover) { // Dashboard is active
                DrawRectangleRec(navs[i], Fade(accentColor, 0.3f));
                DrawRectangle(0, navs[i].y, 5, 60, accentColor);
            }
            DrawText(labels[i], 60, navs[i].y + 15, 24, WHITE);

            if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (i == 1) quizes();
                if (i == 2) gradesStudent();
                if (i == 3) settingsStudent();
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

        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);
        drawUsername(currentUser);

        DrawRectangleRounded({ 350, 150, 400, 200 }, 0.1f, 10, WHITE);
        DrawText("MY TOTAL XP", 370, 180, 20, GRAY);

        const char* xpText = TextFormat("%d", totalXP);
        DrawText(xpText, 370, 230, 50, BLACK);

        EndDrawing();
    }
}