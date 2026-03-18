#include "dashboards.h"
#include "accessData.h"
#include "auth.h"
#include "settings.h"
#include "quizes.h"

void drawUsername(string user)
{
    ifstream file("../data/accounts.csv");
    string line,storedUsername,storedPassword,storedRole;
    string username;
    string greeting = "Welcome back, ";
    while (getline(file, line))
    {
        istringstream iss(line);
        if (getline(iss, storedUsername, ',') && getline(iss, storedPassword, ',') && getline(iss, storedRole))
        {
            if (storedUsername == currentUser)
            {
                username = storedUsername;
            }
        }
    }
    string finalUsername = greeting + username;
    DrawText(finalUsername.c_str(), GetScreenWidth() / 2 - 525, GetScreenHeight() / 2 - 467, 45, BLACK);
    
}

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
        DrawText("1,248", 370, 220, 45, BLACK);
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


void studentDashboard()
{
    const int screenWidth = 1000;
    const int screenHeight = 700;

    if (!IsWindowReady()) {
        InitWindow(screenWidth, screenHeight, "Student Dashboard - English");
    }

    bool isDropdownOpen = false;
    bool itemHovered = false;
    Rectangle dropdownHeader = { 350, 300, 300, 50 };
    Rectangle startButton = { 400, 500, 200, 50 };
    
    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        Vector2 mouse = GetMousePosition();
        bool overHeader = CheckCollisionPointRec(mouse, dropdownHeader);
        bool overStart = CheckCollisionPointRec(mouse, startButton);

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            if (overHeader) isDropdownOpen = !isDropdownOpen;
            else if (isDropdownOpen) {
                Rectangle itemRect = { dropdownHeader.x, dropdownHeader.y + 50, dropdownHeader.width, 50 };
                if (CheckCollisionPointRec(mouse, itemRect)) {
                    isDropdownOpen = false;
                } else {
                    isDropdownOpen = false;
                }
            }
        }

        BeginDrawing();
        ClearBackground(GetColor(0xF5F7FAFF)); 

        DrawRectangle(0, 0, screenWidth, 100, WHITE);
        DrawText("LEARNER PORTAL", 40, 35, 28, GetColor(0x2D3436FF));
        DrawCircle(920, 50, 20, LIGHTGRAY);
        DrawText("JD", 912, 42, 15, DARKGRAY);

        DrawText("Welcome back, Student!", 380, 180, 24, DARKGRAY);
        DrawText("Select your current course to begin the assessment", 310, 220, 16, GRAY);

        DrawRectangleRounded(dropdownHeader, 0.2f, 8, WHITE);
        DrawRectangleRoundedLines(dropdownHeader, 0.2f, 8, 2, isDropdownOpen ? SKYBLUE : LIGHTGRAY);
        DrawText("English Language", dropdownHeader.x + 20, dropdownHeader.y + 15, 20, DARKGRAY);
        DrawText(isDropdownOpen ? "▲" : "▼", dropdownHeader.x + 260, dropdownHeader.y + 15, 18, GRAY);

        if (isDropdownOpen) {
            Rectangle itemRect = { dropdownHeader.x, dropdownHeader.y + 55, dropdownHeader.width, 50 };
            itemHovered = CheckCollisionPointRec(mouse, itemRect);
            
            DrawRectangleRounded(itemRect, 0.2f, 8, itemHovered ? GetColor(0xF0F9FFFF) : WHITE);
            DrawRectangleRoundedLines(itemRect, 0.2f, 8, 1, SKYBLUE);
            DrawText("English Language", itemRect.x + 20, itemRect.y + 15, 20, itemHovered ? SKYBLUE : DARKGRAY);
        }

        if (!isDropdownOpen) {
            DrawRectangleRounded(startButton, 0.3f, 8, overStart ? GetColor(0x0984E3FF) : SKYBLUE);
            DrawText("START QUIZ", startButton.x + 45, startButton.y + 15, 20, WHITE);
            
            if (overStart && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                break; 
            }
        }

        EndDrawing();
    }
}