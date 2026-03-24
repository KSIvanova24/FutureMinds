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


struct TabStudentGrade {
    string name;
    int totalXP = 0;
    int quizzesCount = 0;
    float averagePercentage = 0.0f;
};

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

    int currentTab = 0;

    float grammarSum = 0, vocabSum = 0, readingSum = 0, idiomsSum = 0;
    int gCount = 0, vCount = 0, rCount = 0, iCount = 0;
    int totalQuizzes = 0;

    vector<TabStudentGrade> leaderboard; 

    ifstream file("../data/notebook.csv");
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string name;
        getline(ss, name, ',');

        TabStudentGrade sg;
        sg.name = name;
        int sumScores = 0;

        string entry;
        while (getline(ss, entry, ',')) {
            size_t lastSpace = entry.find_last_of(' ');
            if (lastSpace != string::npos) {
                string quizName = entry.substr(0, lastSpace);
                int score = stoi(entry.substr(lastSpace + 1));
                totalQuizzes++;
                sumScores += score;
                sg.quizzesCount++;

                if (quizName.find("Grammar") != string::npos) { grammarSum += score; gCount++; }
                else if (quizName.find("Vocabulary") != string::npos || quizName.find("Vocab") != string::npos) { vocabSum += score; vCount++; }
                else if (quizName.find("Reading") != string::npos) { readingSum += score; rCount++; }
                else if (quizName.find("Idioms") != string::npos) { idiomsSum += score; iCount++; }
            }
        }
        sg.totalXP = sumScores;
        if (sg.quizzesCount > 0) sg.averagePercentage = (float)sumScores / sg.quizzesCount;
        leaderboard.push_back(sg);
    }
    file.close();

    for (size_t i = 0; i < leaderboard.size(); i++) {
        for (size_t j = i + 1; j < leaderboard.size(); j++) {
            if (leaderboard[i].totalXP < leaderboard[j].totalXP) {
                swap(leaderboard[i], leaderboard[j]);
            }
        }
    }

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

    int selectedStudentIdx = 0;
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

        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        Rectangle navDash = { 0, 150, 300, 60 };
        if (CheckCollisionPointRec(mouse, navDash) || currentTab == 0) {
            DrawRectangleRec(navDash, Fade(accentColor, 0.3f));
            DrawRectangle(0, 150, 5, 60, accentColor);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentTab = 0;
        }
        DrawText("Dashboard", 60, 165, 24, WHITE);

        Rectangle studentsBtn = { 0, 220, 300, 60 };
        if (CheckCollisionPointRec(mouse, studentsBtn) || currentTab == 1) {
            DrawRectangleRec(studentsBtn, Fade(accentColor, 0.3f));
            DrawRectangle(0, 220, 5, 60, accentColor);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) currentTab = 1;
        }
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

        if (currentTab == 0)
        {

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

            Rectangle badgeArea = { startX, 340, GetScreenWidth() - startX - spacing, 600 };
            DrawRectangleRounded(badgeArea, 0.02f, 10, WHITE);
            DrawRectangleRoundedLines(badgeArea, 0.02f, 10, 1, borderColor);

            DrawText("ACCREDIT STUDENT BADGES", badgeArea.x + 40, badgeArea.y + 30, 25, textColor);
            DrawLineEx({ badgeArea.x + 40, badgeArea.y + 70 }, { badgeArea.x + badgeArea.width - 40, badgeArea.y + 70 }, 1, borderColor);

            DrawText("Selected Student:", badgeArea.x + 40, badgeArea.y + 100, 18, GRAY);
            Rectangle cycleBox = { badgeArea.x + 40, badgeArea.y + 130, 350, 45 };
            bool cycleHover = CheckCollisionPointRec(mouse, cycleBox);

            DrawRectangleRounded(cycleBox, 0.15f, 10, cycleHover ? Fade(accentColor, 0.1f) : bgDark);
            DrawRectangleRoundedLines(cycleBox, 0.15f, 10, 1, cycleHover ? accentColor : borderColor);

            string displayUser = studentList.empty() ? "No students" : studentList[selectedStudentIdx];
            DrawText(displayUser.c_str(), cycleBox.x + 15, cycleBox.y + 12, 20, textColor);
            DrawText("Click to cycle >", cycleBox.x + cycleBox.width - 150, cycleBox.y + 14, 16, GRAY);

            if (cycleHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && !studentList.empty()) {
                selectedStudentIdx = (selectedStudentIdx + 1) % studentList.size();
            }

            Rectangle viewGradesBtn = { cycleBox.x + cycleBox.width + 20, cycleBox.y, 160, 45 };
            bool viewGradesHover = CheckCollisionPointRec(mouse, viewGradesBtn);

            DrawRectangleRounded(viewGradesBtn, 0.15f, 10, !studentList.empty() && viewGradesHover ? BLACK : accentColor);
            DrawText("View Grades", viewGradesBtn.x + 25, viewGradesBtn.y + 12, 18, WHITE);

            if (!studentList.empty() && viewGradesHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                gradesTeacher();
                return;
            }

            float bWidth = 220;
            float bHeight = 100;
            float bSpacing = (badgeArea.width - 80 - (bWidth * 4)) / 3;
            float badgeStartX = badgeArea.x + 40;
            float badgeStartY = badgeArea.y + 220;

            Rectangle bGrammar = { badgeStartX, badgeStartY, bWidth, bHeight };
            bool hGrammar = CheckCollisionPointRec(mouse, bGrammar);
            DrawRectangleRounded(bGrammar, 0.15f, 10, (selectedBadge == 1) ? Fade(accentColor, 0.2f) : (hGrammar ? Fade(bgDark, 0.5f) : WHITE));
            DrawRectangleRoundedLines(bGrammar, 0.15f, 10, (selectedBadge == 1) ? 4 : 1, (selectedBadge == 1 || hGrammar) ? accentColor : borderColor);
            if (bGrammarTex.id > 0) DrawTexturePro(bGrammarTex, { 0, 0, (float)bGrammarTex.width, (float)bGrammarTex.height }, { bGrammar.x + 10, bGrammar.y + 10, bGrammar.width - 20, bGrammar.height - 20 }, { 0,0 }, 0.0f, WHITE);
            if (hGrammar && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) selectedBadge = 1;

            Rectangle bVocab = { badgeStartX + bWidth + bSpacing, badgeStartY, bWidth, bHeight };
            bool hVocab = CheckCollisionPointRec(mouse, bVocab);
            DrawRectangleRounded(bVocab, 0.15f, 10, (selectedBadge == 2) ? Fade(GREEN, 0.2f) : (hVocab ? Fade(bgDark, 0.5f) : WHITE));
            DrawRectangleRoundedLines(bVocab, 0.15f, 10, (selectedBadge == 2) ? 4 : 1, (selectedBadge == 2 || hVocab) ? GREEN : borderColor);
            if (bVocabTex.id > 0) DrawTexturePro(bVocabTex, { 0, 0, (float)bVocabTex.width, (float)bVocabTex.height }, { bVocab.x + 10, bVocab.y + 10, bVocab.width - 20, bVocab.height - 20 }, { 0,0 }, 0.0f, WHITE);
            if (hVocab && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) selectedBadge = 2;

            Rectangle bRead = { badgeStartX + (bWidth + bSpacing) * 2, badgeStartY, bWidth, bHeight };
            bool hRead = CheckCollisionPointRec(mouse, bRead);
            DrawRectangleRounded(bRead, 0.15f, 10, (selectedBadge == 3) ? Fade(ORANGE, 0.2f) : (hRead ? Fade(bgDark, 0.5f) : WHITE));
            DrawRectangleRoundedLines(bRead, 0.15f, 10, (selectedBadge == 3) ? 4 : 1, (selectedBadge == 3 || hRead) ? ORANGE : borderColor);
            if (bReadingTex.id > 0) DrawTexturePro(bReadingTex, { 0, 0, (float)bReadingTex.width, (float)bReadingTex.height }, { bRead.x + 10, bRead.y + 10, bRead.width - 20, bRead.height - 20 }, { 0,0 }, 0.0f, WHITE);
            if (hRead && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) selectedBadge = 3;

            Rectangle bIdioms = { badgeStartX + (bWidth + bSpacing) * 3, badgeStartY, bWidth, bHeight };
            bool hIdioms = CheckCollisionPointRec(mouse, bIdioms);
            DrawRectangleRounded(bIdioms, 0.15f, 10, (selectedBadge == 4) ? Fade(PURPLE, 0.2f) : (hIdioms ? Fade(bgDark, 0.5f) : WHITE));
            DrawRectangleRoundedLines(bIdioms, 0.15f, 10, (selectedBadge == 4) ? 4 : 1, (selectedBadge == 4 || hIdioms) ? PURPLE : borderColor);
            if (bIdiomsTex.id > 0) DrawTexturePro(bIdiomsTex, { 0, 0, (float)bIdiomsTex.width, (float)bIdiomsTex.height }, { bIdioms.x + 10, bIdioms.y + 10, bIdioms.width - 20, bIdioms.height - 20 }, { 0,0 }, 0.0f, WHITE);
            if (hIdioms && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) selectedBadge = 4;

            Rectangle accreditBtn = { badgeArea.x + 40, badgeStartY + bHeight + 60, 200, 50 };
            bool accreditHover = CheckCollisionPointRec(mouse, accreditBtn);
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
                selectedBadge = 0;
            }
        }

        else if (currentTab == 1)
        {
            Rectangle tableArea = { 350, 120, (float)GetScreenWidth() - 400, (float)GetScreenHeight() - 170 };
            DrawRectangleRounded(tableArea, 0.02f, 10, WHITE);
            DrawRectangleRoundedLines(tableArea, 0.02f, 10, 1, borderColor);

            DrawText("CLASSROOM ACADEMIC PROGRESS", tableArea.x + 40, tableArea.y + 30, 26, textColor);
            DrawLineEx({ tableArea.x + 40, tableArea.y + 70 }, { tableArea.x + tableArea.width - 40, tableArea.y + 70 }, 1, borderColor);

            float rowY = tableArea.y + 100;
            DrawText("Student Name", tableArea.x + 50, rowY, 20, GRAY);
            DrawText("Tests Count", tableArea.x + 300, rowY, 20, GRAY);
            DrawText("Total Score (XP)", tableArea.x + 500, rowY, 20, GRAY);
            DrawText("Avg success", tableArea.x + 720, rowY, 20, GRAY);
            DrawLineEx({ tableArea.x + 40, rowY + 30 }, { tableArea.x + tableArea.width - 40, rowY + 30 }, 1, borderColor);

            rowY += 50;

            if (leaderboard.empty()) {
                DrawText("No data found in notebook.csv", tableArea.x + 50, rowY + 50, 22, RED);
            }
            else {
                for (size_t i = 0; i < leaderboard.size(); i++) {
                    if (rowY > tableArea.y + tableArea.height - 40) break; // Защита от излизане от кутията

                    if (i % 2 == 0) {
                        DrawRectangle(tableArea.x + 30, rowY - 10, tableArea.width - 60, 40, { 245, 246, 250, 255 });
                    }

                    DrawText(leaderboard[i].name.c_str(), tableArea.x + 50, rowY, 18, textColor);
                    DrawText(TextFormat("%d", leaderboard[i].quizzesCount), tableArea.x + 300, rowY, 18, textColor);
                    DrawText(TextFormat("%d XP", leaderboard[i].totalXP), tableArea.x + 500, rowY, 18, textColor);
                    DrawText(TextFormat("%.1f%%", leaderboard[i].averagePercentage), tableArea.x + 720, rowY, 18, textColor);

                    rowY += 40;
                }
            }
        }

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
    Color textColor = { 45, 55, 72, 255 };
    Color borderColor = { 226, 232, 240, 255 };

    int totalXP = 0;
    ifstream file("../data/notebook.csv");
    string line;

    while (getline(file, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string name;
        getline(ss, name, ',');

        if (name == currentUser) {
            string entry;
            while (getline(ss, entry, ',')) {
                size_t lastSpace = entry.find_last_of(' ');
                if (lastSpace != string::npos) {
                    totalXP += stoi(entry.substr(lastSpace + 1));
                }
            }
            break;
        }
    }
    file.close();

    bool hasIdioms = false, hasGrammar = false, hasVocabulary = false, hasReading = false;

    ifstream badgeFile("../data/badges.csv");
    while (getline(badgeFile, line)) {
        if (line.empty()) continue;
        stringstream ss(line);
        string name, idioms, grammar, vocabulary, reading;

        getline(ss, name, ',');
        getline(ss, idioms, ',');
        getline(ss, grammar, ',');
        getline(ss, vocabulary, ',');
        getline(ss, reading, ',');

        if (name == currentUser) {
            hasIdioms = (idioms == "1");
            hasGrammar = (grammar == "1");
            hasVocabulary = (vocabulary == "1");
            hasReading = (reading == "1");
            break;
        }
    }
    badgeFile.close();

    Texture2D bGrammarTex = LoadTexture("../images/grammar.png");
    Texture2D bVocabTex = LoadTexture("../images/vocab.png");
    Texture2D bReadingTex = LoadTexture("../images/reading.png");
    Texture2D bIdiomsTex = LoadTexture("../images/idioms.png");

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
            if (i == 0 || hover) {
                DrawRectangleRec(navs[i], Fade(accentColor, 0.3f));
                DrawRectangle(0, navs[i].y, 5, 60, accentColor);
            }
            DrawText(labels[i], 60, navs[i].y + 15, 24, WHITE);

            if (hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                if (i == 1) { quizes(); return; }
                if (i == 2) { gradesStudent(); return; }
                if (i == 3) { settingsStudent(); return; }
            }
        }

        Rectangle logoutBtn = { 20, (float)GetScreenHeight() - 95, 260, 50 };
        bool logoutHover = CheckCollisionPointRec(mouse, logoutBtn);
        DrawRectangleRounded(logoutBtn, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", logoutBtn.x + 85, logoutBtn.y + 15, 20, WHITE);

        if (logoutHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            startingScreen(true);
            return;
        }

        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);
        drawUsername(currentUser);

        float startX = 350;
        DrawRectangleRounded({ startX, 120, 400, 180 }, 0.05f, 10, WHITE);
        DrawRectangleRoundedLines({ startX, 120, 400, 180 }, 0.05f, 10, 1, borderColor);
        DrawText("MY TOTAL XP", startX + 25, 145, 18, GRAY);
        DrawText(TextFormat("%d XP", totalXP), startX + 25, 180, 45, textColor);

        DrawRectangle(startX + 25, 260, 350, 8, Fade(accentColor, 0.3f));
        DrawRectangle(startX + 25, 260, 350 * 0.7f, 8, accentColor);

        Rectangle badgeArea = { startX, 330, GetScreenWidth() - startX - 50, 400 };
        DrawRectangleRounded(badgeArea, 0.02f, 10, WHITE);
        DrawRectangleRoundedLines(badgeArea, 0.02f, 10, 1, borderColor);

        DrawText("MY BADGES", badgeArea.x + 40, badgeArea.y + 30, 25, textColor);
        DrawLineEx({ badgeArea.x + 40, badgeArea.y + 70 }, { badgeArea.x + badgeArea.width - 40, badgeArea.y + 70 }, 1, borderColor);

        float bWidth = 220;
        float bHeight = 100;
        float bSpacing = (badgeArea.width - 80 - (bWidth * 4)) / 3;
        float badgeStartX = badgeArea.x + 40;
        float badgeStartY = badgeArea.y + 120;

        Rectangle bGrammar = { badgeStartX, badgeStartY, bWidth, bHeight };
        DrawRectangleRounded(bGrammar, 0.15f, 10, { 245, 246, 250, 255 });
        DrawRectangleRoundedLines(bGrammar, 0.15f, 10, 1, borderColor);
        if (hasGrammar && bGrammarTex.id > 0) {
            DrawTexturePro(bGrammarTex, { 0,0,(float)bGrammarTex.width, (float)bGrammarTex.height }, { bGrammar.x + 10, bGrammar.y + 10, bGrammar.width - 20, bGrammar.height - 20 }, { 0,0 }, 0.0f, WHITE);
        }
        else {
            DrawText("Locked", bGrammar.x + 70, bGrammar.y + 40, 20, LIGHTGRAY);
        }
        DrawText("Grammar", bGrammar.x + (bWidth - MeasureText("Grammar", 18)) / 2, bGrammar.y + bHeight + 15, 18, textColor);

        Rectangle bVocab = { badgeStartX + bWidth + bSpacing, badgeStartY, bWidth, bHeight };
        DrawRectangleRounded(bVocab, 0.15f, 10, { 245, 246, 250, 255 });
        DrawRectangleRoundedLines(bVocab, 0.15f, 10, 1, borderColor);
        if (hasVocabulary && bVocabTex.id > 0) {
            DrawTexturePro(bVocabTex, { 0,0,(float)bVocabTex.width, (float)bVocabTex.height }, { bVocab.x + 10, bVocab.y + 10, bVocab.width - 20, bVocab.height - 20 }, { 0,0 }, 0.0f, WHITE);
        }
        else {
            DrawText("Locked", bVocab.x + 70, bVocab.y + 40, 20, LIGHTGRAY);
        }
        DrawText("Vocabulary", bVocab.x + (bWidth - MeasureText("Vocabulary", 18)) / 2, bVocab.y + bHeight + 15, 18, textColor);

        Rectangle bRead = { badgeStartX + (bWidth + bSpacing) * 2, badgeStartY, bWidth, bHeight };
        DrawRectangleRounded(bRead, 0.15f, 10, { 245, 246, 250, 255 });
        DrawRectangleRoundedLines(bRead, 0.15f, 10, 1, borderColor);
        if (hasReading && bReadingTex.id > 0) {
            DrawTexturePro(bReadingTex, { 0,0,(float)bReadingTex.width, (float)bReadingTex.height }, { bRead.x + 10, bRead.y + 10, bRead.width - 20, bRead.height - 20 }, { 0,0 }, 0.0f, WHITE);
        }
        else {
            DrawText("Locked", bRead.x + 70, bRead.y + 40, 20, LIGHTGRAY);
        }
        DrawText("Reading", bRead.x + (bWidth - MeasureText("Reading", 18)) / 2, bRead.y + bHeight + 15, 18, textColor);

        Rectangle bIdioms = { badgeStartX + (bWidth + bSpacing) * 3, badgeStartY, bWidth, bHeight };
        DrawRectangleRounded(bIdioms, 0.15f, 10, { 245, 246, 250, 255 });
        DrawRectangleRoundedLines(bIdioms, 0.15f, 10, 1, borderColor);
        if (hasIdioms && bIdiomsTex.id > 0) {
            DrawTexturePro(bIdiomsTex, { 0,0,(float)bIdiomsTex.width, (float)bIdiomsTex.height }, { bIdioms.x + 10, bIdioms.y + 10, bIdioms.width - 20, bIdioms.height - 20 }, { 0,0 }, 0.0f, WHITE);
        }
        else {
            DrawText("Locked", bIdioms.x + 70, bIdioms.y + 40, 20, LIGHTGRAY);
        }
        DrawText("Idioms", bIdioms.x + (bWidth - MeasureText("Idioms", 18)) / 2, bIdioms.y + bHeight + 15, 18, textColor);

        EndDrawing();
    }

    UnloadTexture(bGrammarTex);
    UnloadTexture(bVocabTex);
    UnloadTexture(bReadingTex);
    UnloadTexture(bIdiomsTex);
}