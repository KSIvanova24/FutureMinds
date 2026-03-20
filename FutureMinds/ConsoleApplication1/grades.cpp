#include "settings.h"
#include "accessData.h"
#include "quizes.h"
#include "auth.h"
#include "dashboards.h"
#include "grades.h"

void gradesTeacher()
{
    // Menu Settings
    const int startX = 400;
    const int startY = 300;
    const int fontSize = 40;
    const int spacing = 80;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Header
        DrawText("GRADE MANAGEMENT", startX, startY - 100, 50, BLACK);

        // Menu Options
        DrawText("1. View Grades", startX, startY, fontSize, DARKGRAY);
        DrawText("2. Add New Grade", startX, startY + spacing, fontSize, DARKGRAY);
        DrawText("3. Calculate Average", startX, startY + (spacing * 2), fontSize, DARKGRAY);
        DrawText("4. Back to Main Menu", startX, startY + (spacing * 3), fontSize, RED);

        // Footer links (Larger as requested)
        DrawText("Terms of Service", 450, 1000, 24, GRAY);
        DrawText("Privacy Policy", 700, 1000, 24, GRAY);
        DrawText("Support", 950, 1000, 24, GRAY);

        EndDrawing();
    }
    
}
void gradesStudent()
{
    // Menu Settings
    const int startX = 400;
    const int startY = 300;
    const int fontSize = 40;
    const int spacing = 80;
    while (!WindowShouldClose())
    {
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // Header
        DrawText("GRADE MANAGEMENT", startX, startY - 100, 50, BLACK);

        // Menu Options
        DrawText("1. View Grades", startX, startY, fontSize, DARKGRAY);
        DrawText("2. Add New Grade", startX, startY + spacing, fontSize, DARKGRAY);
        DrawText("3. Calculate Average", startX, startY + (spacing * 2), fontSize, DARKGRAY);


        // Footer links (Larger as requested)
        DrawText("Terms of Service", 450, 1000, 24, GRAY);
        DrawText("Privacy Policy", 700, 1000, 24, GRAY);
        DrawText("Support", 950, 1000, 24, GRAY);

        EndDrawing();
    }

}