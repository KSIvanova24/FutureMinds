#include "dashboards.h"
#include "accessData.h"
#include "auth.h"
#include "settings.h"
#include "quizes.h"
#include "grades.h"

void teacherDashboard()
{
    // Use dynamic sizing for full-screen consistency
    const int screenWidth = GetScreenWidth();
    const int screenHeight = GetScreenHeight();
    SetTargetFPS(60);

    Color bgDark = { 240, 244, 248, 255 };
    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 66, 153, 225, 255 };

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        // Dynamic Footer Positions
        Rectangle logoutButton = { 20, (float)GetScreenHeight() - 100, 260, 50 };
        Rectangle actionButton = { (float)GetScreenWidth() - 400, (float)GetScreenHeight() - 150, 320, 80 };

        BeginDrawing();
        ClearBackground(bgDark);

        // --- SIDEBAR ---
        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        // DASHBOARD
        Rectangle dashBtn = { 0, 150, 300, 60 };
        if (CheckCollisionPointRec(mouse, dashBtn)) {
            DrawRectangleRec(dashBtn, Fade(accentColor, 0.3f));
            DrawRectangle(0, 150, 5, 60, accentColor);
        }
        DrawText("Dashboard", 60, 165, 24, WHITE);

        // STUDENTS
        Rectangle studentsBtn = { 0, 220, 300, 60 };
        if (CheckCollisionPointRec(mouse, studentsBtn)) {
            DrawRectangleRec(studentsBtn, Fade(accentColor, 0.3f));
            DrawRectangle(0, 220, 5, 60, accentColor);
        }
        DrawText("Students", 60, 235, 24, WHITE);

        // GRADES
        Rectangle gBtn = { 0, 290, 300, 60 };
        if (CheckCollisionPointRec(mouse, gBtn)) {
            DrawRectangleRec(gBtn, Fade(accentColor, 0.3f));
            DrawRectangle(0, 290, 5, 60, accentColor);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) gradesTeacher();
        }
        DrawText("Grades", 60, 305, 24, WHITE);

        // QUIZZES
        Rectangle quizBtn = { 0, 360, 300, 60 };
        if (CheckCollisionPointRec(mouse, quizBtn)) {
            DrawRectangleRec(quizBtn, Fade(accentColor, 0.3f));
            DrawRectangle(0, 360, 5, 60, accentColor);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) quizes();
        }
        DrawText("Quizzes", 60, 375, 24, WHITE);

        // SETTINGS
        Rectangle setBtn = { 0, 430, 300, 60 };
        if (CheckCollisionPointRec(mouse, setBtn)) {
            DrawRectangleRec(setBtn, Fade(accentColor, 0.3f));
            DrawRectangle(0, 430, 5, 60, accentColor);
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) settings();
        }
        DrawText("Settings", 60, 445, 24, WHITE);

        // --- TOP BAR ---
        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);
        drawUsername(currentUser);

        // --- CARDS (Distributed across screen) ---
        float cardWidth = 350;
        float spacing = (GetScreenWidth() - 300 - (cardWidth * 3)) / 4;

        // Card 1
        DrawRectangle(300 + spacing, 150, cardWidth, 180, WHITE);
        DrawText("ACTIVE STUDENTS", 300 + spacing + 20, 180, 20, GRAY);
        drawStudentsCount(); // Ensure this handles internal positioning
        DrawRectangle(300 + spacing + 20, 290, 300, 8, Fade(accentColor, 0.3f));
        DrawRectangle(300 + spacing + 20, 290, 220, 8, accentColor);

        // Card 2
        DrawRectangle(300 + spacing * 2 + cardWidth, 150, cardWidth, 180, WHITE);
        DrawText("QUIZZES COMPLETED", 300 + spacing * 2 + cardWidth + 20, 180, 20, GRAY);
        DrawText("85%", 300 + spacing * 2 + cardWidth + 20, 220, 45, BLACK);
        DrawRectangle(300 + spacing * 2 + cardWidth + 20, 290, 300, 8, Fade(GREEN, 0.3f));
        DrawRectangle(300 + spacing * 2 + cardWidth + 20, 290, 255, 8, GREEN);

        // Card 3
        DrawRectangle(300 + spacing * 3 + cardWidth * 2, 150, cardWidth, 180, WHITE);
        DrawText("AVG. SCORE", 300 + spacing * 3 + cardWidth * 2 + 20, 180, 20, GRAY);
        DrawText("76.4", 300 + spacing * 3 + cardWidth * 2 + 20, 220, 45, BLACK);
        DrawRectangle(300 + spacing * 3 + cardWidth * 2 + 20, 290, 300, 8, Fade(ORANGE, 0.3f));
        DrawRectangle(300 + spacing * 3 + cardWidth * 2 + 20, 290, 200, 8, ORANGE);

        // ACTION BUTTON
        bool actionHover = CheckCollisionPointRec(mouse, actionButton);
        DrawRectangleRounded(actionButton, 0.5f, 10, actionHover ? DARKBLUE : accentColor);
        DrawText("+ Create New Quiz", actionButton.x + 45, actionButton.y + 25, 25, WHITE);

        // LOGOUT
        bool logoutHover = CheckCollisionPointRec(mouse, logoutButton);
        DrawRectangleRounded(logoutButton, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", logoutButton.x + 80, logoutButton.y + 15, 20, WHITE);

        if (logoutHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) startingScreen(true);

        EndDrawing();
    }
}

void studentDashboard() {
    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 66, 153, 225, 255 };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground({ 240, 244, 248, 255 });

        // Sidebar
        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        // Navigation (Using dynamic Y)
        Rectangle navs[] = {
            { 0, 150, 300, 60 }, // Dash
            { 0, 220, 300, 60 }, // Quizzes
            { 0, 290, 300, 60 }, // Grades
            { 0, 360, 300, 60 }  // Settings
        };
        const char* labels[] = { "Dashboard", "Quizzes", "Grades", "Settings" };

        for (int i = 0; i < 4; i++) {
            if (CheckCollisionPointRec(mouse, navs[i])) {
                DrawRectangleRec(navs[i], Fade(accentColor, 0.3f));
                DrawRectangle(0, navs[i].y, 5, 60, accentColor);
                if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                    if (i == 1) quizes();
                    if (i == 2) gradesStudent();
                    if (i == 3) settings();
                }
            }
            DrawText(labels[i], 60, navs[i].y + 15, 24, WHITE);
        }

        // Logout
        Rectangle logoutBtn = { 20, (float)GetScreenHeight() - 95, 260, 50 };
        bool logoutHover = CheckCollisionPointRec(mouse, logoutBtn);
        DrawRectangleRounded(logoutBtn, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", logoutBtn.x + 85, logoutBtn.y + 15, 20, WHITE);

        if (logoutHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            startingScreen(true);
            break;
        }

        // Top Bar
        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);
        drawUsername(currentUser);

        // Content
        DrawRectangleRounded({ 350, 150, 400, 200 }, 0.1f, 10, WHITE);
        DrawText("MY TOTAL XP", 370, 180, 20, GRAY);
        DrawText("2,400", 370, 230, 50, BLACK);

        EndDrawing();
    }
}