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

            // Grade Actions
            if (CheckCollisionPointRec(mouse, viewGradesRect)) { /* Show grade list logic */ }
            if (CheckCollisionPointRec(mouse, avgGradeRect)) { /* Show GPA logic */ }
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

        // --- MAIN CONTENT ---
        DrawRectangle(300, 0, GetScreenWidth() - 300, 80, WHITE);
        DrawText("STUDENT PORTAL", 330, 25, 25, sideBarColor);

        // Grades Card
        DrawRectangleRounded(card, 0.02f, 10, WHITE);
        DrawRectangleRoundedLines(card, 0.02f, 10, 2, borderColor);

        DrawText("GRADE MANAGEMENT", (int)card.x + 50, (int)card.y + 40, 40, textColor);
        DrawLineEx({ card.x + 50, card.y + 95 }, { card.x + 1050, card.y + 95 }, 2, borderColor);

        // Action Options
        DrawMenuOption(viewGradesRect, "View My Grades", 1, mouse, accentColor, borderColor, textColor, bgWhite);
        DrawMenuOption(avgGradeRect, "Calculate My Average", 2, mouse, accentColor, borderColor, textColor, bgWhite);

        // Footer links
        DrawText("Terms of Service", 500, 1000, 20, GRAY);
        DrawText("Privacy Policy", 750, 1000, 20, GRAY);
        DrawText("Support", 1000, 1000, 20, GRAY);

        EndDrawing();
    }
}