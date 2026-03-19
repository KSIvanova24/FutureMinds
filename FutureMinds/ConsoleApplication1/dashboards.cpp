#include "dashboards.h"
#include "accessData.h"
#include "auth.h"
#include "settings.h"
#include "quizes.h"


void teacherDashboard()
{
    const int screenWidth = 1920;
    const int screenHeight = 975;
    SetTargetFPS(60);

    // Colors
    Color bgDark = { 240, 244, 248, 255 };
    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 66, 153, 225, 255 };

    // Sidebar button positions
    Vector2 dashPosition = { 0, 150 };
    Vector2 studentsPosition = { 0, 220 };
    Vector2 quizPosition = { 0, 290 };
    Vector2 settingsPosition = { 0, 360 };

    // Sidebar rectangles
    Rectangle dashButton = { dashPosition.x, dashPosition.y, 300, 60 };
    Rectangle studentsButton = { studentsPosition.x, studentsPosition.y, 300, 60 };
    Rectangle quizButton = { quizPosition.x, quizPosition.y, 300, 60 };
    Rectangle settingsButton = { settingsPosition.x, settingsPosition.y, 300, 60 };

    // Action button
    Vector2 actionPosition = { screenWidth - 400, screenHeight - 150 };
    Rectangle actionButton = { actionPosition.x, actionPosition.y, 320, 80 };

    // Logout button
    Vector2 logoutPosition = { 20, screenHeight - 70 };
    Rectangle logoutButton = { logoutPosition.x, logoutPosition.y, 260, 50 };

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground(bgDark);

        // Sidebar
        DrawRectangle(0, 0, 300, screenHeight, sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);

        // Divider line (from original)
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        // DASHBOARD BUTTON
        bool dashHover = CheckCollisionPointRec(mouse, dashButton);
        if (dashHover)
        {
            DrawRectangleRec(dashButton, Fade(accentColor, 0.3f));
            DrawRectangle(dashButton.x, dashButton.y, 5, dashButton.height, accentColor);
        }
        DrawText("Dashboard", dashPosition.x + 60, dashPosition.y + 15, 24, WHITE);

        // STUDENTS BUTTON
        bool studentsHover = CheckCollisionPointRec(mouse, studentsButton);
        if (studentsHover)
        {
            DrawRectangleRec(studentsButton, Fade(accentColor, 0.3f));
            DrawRectangle(studentsButton.x, studentsButton.y, 5, studentsButton.height, accentColor);
        }
        DrawText("Students", studentsPosition.x + 60, studentsPosition.y + 15, 24, WHITE);

        // QUIZ BUTTON
        bool quizHover = CheckCollisionPointRec(mouse, quizButton);
        if (quizHover)
        {
            DrawRectangleRec(quizButton, Fade(accentColor, 0.3f));
            DrawRectangle(quizButton.x, quizButton.y, 5, quizButton.height, accentColor);
        }
        DrawText("Quizzes", quizPosition.x + 60, quizPosition.y + 15, 24, WHITE);

        // SETTINGS BUTTON
        bool settingsHover = CheckCollisionPointRec(mouse, settingsButton);
        if (settingsHover)
        {
            DrawRectangleRec(settingsButton, Fade(accentColor, 0.3f));
            DrawRectangle(settingsButton.x, settingsButton.y, 5, settingsButton.height, accentColor);
        }
        DrawText("Settings", settingsPosition.x + 60, settingsPosition.y + 15, 24, WHITE);

        // Top bar
        DrawRectangle(300, 0, screenWidth - 300, 80, WHITE);
        drawUsername(currentUser);

        // Cards with progress bars (from original)

        // Card 1
        DrawRectangle(350, 150, 350, 180, WHITE);
        DrawText("ACTIVE STUDENTS", 370, 180, 20, GRAY);
        drawStudentsCount();
        DrawRectangle(370, 290, 300, 8, Fade(accentColor, 0.3f));
        DrawRectangle(370, 290, 220, 8, accentColor);

        // Card 2
        DrawRectangle(750, 150, 350, 180, WHITE);
        DrawText("QUIZZES COMPLETED", 770, 180, 20, GRAY);
        DrawText("85%", 770, 220, 45, BLACK);
        DrawRectangle(770, 290, 300, 8, Fade(GREEN, 0.3f));
        DrawRectangle(770, 290, 255, 8, GREEN);

        // Card 3
        DrawRectangle(1150, 150, 350, 180, WHITE);
        DrawText("AVG. SCORE", 1170, 180, 20, GRAY);
        DrawText("76.4", 1170, 220, 45, BLACK);
        DrawRectangle(1170, 290, 300, 8, Fade(ORANGE, 0.3f));
        DrawRectangle(1170, 290, 200, 8, ORANGE);

        // ACTION BUTTON
        bool actionHover = CheckCollisionPointRec(mouse, actionButton);
        DrawRectangleRounded(actionButton, 0.5f, 10, actionHover ? DARKBLUE : accentColor);
        DrawText("+ Create New Quiz", actionPosition.x + 45, actionPosition.y + 25, 25, WHITE);

        // LOGOUT BUTTON
        bool logoutHover = CheckCollisionPointRec(mouse, logoutButton);
        DrawRectangleRounded(logoutButton, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", logoutPosition.x + 80, logoutPosition.y + 15, 20, WHITE);

        if (logoutHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            startingScreen(true);
        }

        if (settingsHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            settings();
        }
        if (quizHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            quizes();
        }
        EndDrawing();
    }

    CloseWindow();
}

void studentDashboard() {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    Color sideBarColor = { 45, 55, 72, 255 };
    Color accentColor = { 66, 153, 225, 255 };

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        BeginDrawing();
        ClearBackground({ 240, 244, 248, 255 });

        // 1. DRAW SIDEBAR BACKGROUND
        DrawRectangle(0, 0, 300, GetScreenHeight(), sideBarColor);
        DrawText("FutureMinds", 40, 50, 35, WHITE);
        DrawLineEx({ 30, 110 }, { 270, 110 }, 2, Fade(GRAY, 0.5f));

        // --- QUIZZES BUTTON ---
        Rectangle qBtn = { 0, 150, 300, 60 };
        bool qHover = CheckCollisionPointRec(mouse, qBtn);
        if (qHover) {
            DrawRectangleRec(qBtn, Fade(accentColor, 0.3f));
            DrawRectangle(qBtn.x, qBtn.y, 5, qBtn.height, accentColor); // The indicator line
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                quizes();
            }
        }
        DrawText("Quizzes", 60, 165, 24, WHITE);

        // --- GRADES BUTTON ---
        Rectangle gBtn = { 0, 220, 300, 60 };
        bool gHover = CheckCollisionPointRec(mouse, gBtn);
        if (gHover) {
            DrawRectangleRec(gBtn, Fade(accentColor, 0.3f));
            DrawRectangle(gBtn.x, gBtn.y, 5, gBtn.height, accentColor); // The indicator line
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                ; // Placeholder for grades function
            }
        }
        DrawText("Grades", 60, 235, 24, WHITE);

        // --- SETTINGS BUTTON ---
        Rectangle sBtn = { 0, 290, 300, 60 };
        bool sHover = CheckCollisionPointRec(mouse, sBtn);
        if (sHover) {
            DrawRectangleRec(sBtn, Fade(accentColor, 0.3f));
            DrawRectangle(sBtn.x, sBtn.y, 5, sBtn.height, accentColor); // The indicator line
            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                settings();
            }
        }
        DrawText("Settings", 60, 305, 24, WHITE);

        // 3. LOGOUT BUTTON
        Rectangle logoutBtn = { 20, (float)GetScreenHeight() - 80, 260, 50 };
        bool logoutHover = CheckCollisionPointRec(mouse, logoutBtn);
        DrawRectangleRounded(logoutBtn, 0.2f, 10, logoutHover ? RED : DARKGRAY);
        DrawText("Logout", logoutBtn.x + 85, logoutBtn.y + 15, 20, WHITE);

        if (logoutHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            startingScreen(true);
            break;
        }

        // 4. TOP BAR & CONTENT
        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);
        drawUsername(currentUser);

        // Main Content Card
        DrawRectangleRounded({ 350, 150, 400, 200 }, 0.1f, 10, WHITE);
        DrawText("MY TOTAL XP", 370, 180, 20, GRAY);
        DrawText("2,400", 370, 230, 50, BLACK);

        EndDrawing();
    }
}