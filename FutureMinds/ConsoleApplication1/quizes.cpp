#include "quizes.h"

void quizes()
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    if (!IsWindowReady()) {
        InitWindow(screenWidth, screenHeight, "Quiz Menu");
    }

    const char* subjects[] = { "Математика", "История", "Програмиране", "География" };
    int count = 4;
    int dropdownSelected = -1;
    bool dropdownEditMode = false;
    Rectangle dropdownBounds = { screenWidth / 2 - 100, 150, 200, 40 };

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            if (CheckCollisionPointRec(GetMousePosition(), dropdownBounds))
            {
                dropdownEditMode = !dropdownEditMode;
            }
            else if (dropdownEditMode)
            {
                for (int i = 0; i < count; i++)
                {
                    Rectangle itemBounds = { dropdownBounds.x, dropdownBounds.y + (i + 1) * dropdownBounds.height, dropdownBounds.width, dropdownBounds.height };
                    if (CheckCollisionPointRec(GetMousePosition(), itemBounds))
                    {
                        dropdownSelected = i;
                        dropdownEditMode = false;
                        break;
                    }
                }
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Изберете предмет за куиз:", screenWidth / 2 - 120, 100, 20, DARKGRAY);

        DrawRectangleRec(dropdownBounds, WHITE);
        DrawRectangleLinesEx(dropdownBounds, 2, LIGHTGRAY);

        if (dropdownSelected == -1) {
            DrawText("Избери...", dropdownBounds.x + 10, dropdownBounds.y + 10, 20, GRAY);
        }
        else {
            DrawText(subjects[dropdownSelected], dropdownBounds.x + 10, dropdownBounds.y + 10, 20, BLACK);
        }

        if (dropdownEditMode)
        {
            for (int i = 0; i < count; i++)
            {
                Rectangle itemBounds = { dropdownBounds.x, dropdownBounds.y + (i + 1) * dropdownBounds.height, dropdownBounds.width, dropdownBounds.height };

                DrawRectangleRec(itemBounds, WHITE);
                DrawRectangleLinesEx(itemBounds, 1, LIGHTGRAY);

                if (CheckCollisionPointRec(GetMousePosition(), itemBounds)) {
                    DrawRectangleRec(itemBounds, Fade(LIGHTGRAY, 0.3f));
                }

                DrawText(subjects[i], itemBounds.x + 10, itemBounds.y + 10, 20, BLACK);
            }
        }

        if (dropdownSelected != -1 && !dropdownEditMode) {
            DrawText(TextFormat("Избран предмет: %s", subjects[dropdownSelected]),
                screenWidth / 2 - 100, 300, 20, DARKBLUE);
        }

        EndDrawing();

        if (dropdownSelected != -1 && !dropdownEditMode && IsKeyPressed(KEY_ENTER)) break;
    }
}