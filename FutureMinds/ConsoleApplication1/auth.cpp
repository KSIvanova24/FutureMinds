#include "auth.h"
#include "dashboards.h"
#include "accessData.h"
#include "validation.h"


void signup()
{

    char username[25] = "";
    char password[25] = "";
    char repeatPassword[25] = "";

    int usernameLetterCount = 0;
    int passwordLetterCount = 0;
    int repeatPasswordLetterCount = 0;

    const Rectangle usernameBox = { GetScreenWidth() / 2 - 270, GetScreenHeight() / 2 - 165 , 550, 65 };
    const Rectangle passwordBox = { GetScreenWidth() / 2 - 270, GetScreenHeight() / 2 - 15, 550, 65 };
    const Rectangle repeatPasswordBox = { GetScreenWidth() / 2 - 270, GetScreenHeight() / 2 + 135, 550, 65 };

    Rectangle inputBoxes[] = { usernameBox, passwordBox, repeatPasswordBox };

    bool mouseOnInputBox[3] = { false };

    const Rectangle signupButton = { GetScreenWidth() / 2 - 85, GetScreenHeight() / 2 + 250, 270, 90 };

    DataAccess account;
    Texture2D logoTexture = LoadTexture("../images/logo.png");
    SetTargetFPS(60);

    Texture2D background = LoadTexture("../images/login signup background.png");
    while (!WindowShouldClose())
    {
        Vector2 mousePosition = GetMousePosition();

        // Input box hover check
        for (int i = 0; i < 3; ++i) {
            mouseOnInputBox[i] = CheckCollisionPointRec(mousePosition, inputBoxes[i]);
        }

        bool anyInputBoxHovered = false;
        for (int i = 0; i < 3; ++i) {
            if (mouseOnInputBox[i]) {
                anyInputBoxHovered = true;
                break;
            }
        }

        SetMouseCursor(anyInputBoxHovered ? MOUSE_CURSOR_IBEAM : MOUSE_CURSOR_DEFAULT);
        for (int i = 0; i < 3; ++i) {
            if (mouseOnInputBox[i]) {
                int key = GetCharPressed();
                while (key > 0) {
                    if ((key >= 32) && (key <= 125)) {
                        switch (i) {
                        case 0:
                            if (usernameLetterCount < 50) {
                                username[usernameLetterCount++] = (char)key;
                                username[usernameLetterCount] = '\0';
                            }
                            break;
                        case 1:
                            if (passwordLetterCount < 50) {
                                password[passwordLetterCount++] = (char)key;
                                password[passwordLetterCount] = '\0';
                            }
                            break;
                        case 2:
                            if (repeatPasswordLetterCount < 50) {
                                repeatPassword[repeatPasswordLetterCount++] = (char)key;
                                repeatPassword[repeatPasswordLetterCount] = '\0';
                            }
                            break;
                        }
                    }

                    key = GetCharPressed();
                }

                if (IsKeyPressed(KEY_BACKSPACE))
                {
                    switch (i) {
                    case 0:
                        if (usernameLetterCount > 0) {
                            usernameLetterCount--;
                            username[usernameLetterCount] = '\0';
                        }
                        break;
                    case 1:
                        if (passwordLetterCount > 0) {
                            passwordLetterCount--;
                            password[passwordLetterCount] = '\0';
                        }
                        break;
                    case 2:
                        if (repeatPasswordLetterCount > 0) {
                            repeatPasswordLetterCount--;
                            repeatPassword[repeatPasswordLetterCount] = '\0';
                        }
                        break;
                    }
                }
            }
        }
        Validate validator;
        bool showMismatchError = false;
        bool showRequirementError = false;

        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePosition, signupButton)) {
            if (strcmp(password, repeatPassword) != 0) {
                password[0] = '\0';
                repeatPassword[0] = '\0';
                passwordLetterCount = 0;
                repeatPasswordLetterCount = 0;
                showMismatchError = true;
                showRequirementError = false;
            }
            else {

                if (validator.containsUppercase(password) && validator.containsLowercase(password) &&
                    validator.containsDigit(password) && validator.containsSpecial(password)) {
                    account.addAccount(username, password);
                    strcpy_s(currentUser, username);
                    studentDashboard();
                }
                else {

                    password[0] = '\0';
                    repeatPassword[0] = '\0';
                    passwordLetterCount = 0;
                    repeatPasswordLetterCount = 0;

                }
            }
        }


        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(logoTexture, 0, 0, WHITE);
        DrawText("Sign up from here!", GetScreenWidth() / 2 - 225, GetScreenHeight() / 2 - 380, 50, WHITE);
        DrawText("  !Note: the password must contain at least one\n     uppercase, lowercase, number and symbol", GetScreenWidth() / 2 - 365, GetScreenHeight() / 2 - 315, 30, RED);
        DrawText("Username:", GetScreenWidth() / 2 - 125, GetScreenHeight() / 2 - 215, 50, WHITE);
        DrawText("Password:", GetScreenWidth() / 2 - 125, GetScreenHeight() / 2 - 65, 50, WHITE);
        DrawText("Repeat Password:", GetScreenWidth() / 2 - 220, GetScreenHeight() / 2 + 80, 50, WHITE);

        for (int i = 0; i < 4; ++i) {
            DrawRectangleLines(inputBoxes[i].x, inputBoxes[i].y, inputBoxes[i].width, inputBoxes[i].height, (mouseOnInputBox[i] ? WHITE : GRAY));
        }

        DrawText(username, usernameBox.x + 5, usernameBox.y + 8, 40, WHITE);
        DrawText(TextFormat("%.*s", passwordLetterCount, "******************************************"), passwordBox.x + 5, passwordBox.y + 8, 40, WHITE);
        DrawText(TextFormat("%.*s", repeatPasswordLetterCount, "******************************************"), repeatPasswordBox.x + 5, repeatPasswordBox.y + 8, 40, WHITE);

        DrawText("Sign up", GetScreenWidth() / 2 - 85, GetScreenHeight() / 2 + 250,(CheckCollisionPointRec(mousePosition,signupButton) ? 60: 50), WHITE);



        EndDrawing();
    }
}
void login()
{

    bool isAnswerTrue = false;

    char username[25] = "\0";
    char password[25] = "\0";
    char role[25] = "\0";
    int usernameLetterCount = 0;
    int passwordLetterCount = 0;
    int roleLetterCount = 0;

    const Rectangle usernameBox = { GetScreenWidth() / 2 - 300, GetScreenHeight() / 2 - 175 , 550, 65 };;
    const Rectangle passwordBox = { GetScreenWidth() / 2 - 300, GetScreenHeight() / 2 - 25, 550, 65 };
    const Rectangle roleBox = { GetScreenWidth() / 2 - 300, GetScreenHeight() / 2 + 125, 550, 65 };

    bool mouseOnUsername = false;
    bool mouseOnPassword = false;
    bool mouseOnRole = false;
    Texture2D logoTexture = LoadTexture("../images/logo.png");
    const Rectangle loginButton = { GetScreenWidth() / 2 - 85, GetScreenHeight() / 2 + 250, 270, 90 };

    SetTargetFPS(60);
    Texture2D background = LoadTexture("../images/login signup background.png");

    while (!WindowShouldClose()) {
        Vector2 mousePosition = GetMousePosition();

        if (CheckCollisionPointRec(mousePosition, usernameBox)) mouseOnUsername = true;
        else mouseOnUsername = false;

        if (CheckCollisionPointRec(mousePosition, passwordBox)) mouseOnPassword = true;
        else mouseOnPassword = false;

        if (CheckCollisionPointRec(mousePosition, roleBox)) mouseOnRole = true;
        else mouseOnRole = false;

        if (mouseOnUsername || mouseOnPassword || mouseOnRole) SetMouseCursor(MOUSE_CURSOR_IBEAM);
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        if (mouseOnUsername) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (usernameLetterCount < 25)) {
                    username[usernameLetterCount] = (char)key;
                    username[usernameLetterCount + 1] = '\0';
                    usernameLetterCount++;
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                usernameLetterCount--;
                if (usernameLetterCount < 0) usernameLetterCount = 0;
                username[usernameLetterCount] = '\0';
            }
        }

        if (mouseOnPassword) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (passwordLetterCount < 25)) {
                    password[passwordLetterCount] = (char)key;
                    password[passwordLetterCount + 1] = '\0';
                    passwordLetterCount++;
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                passwordLetterCount--;
                if (passwordLetterCount < 0) passwordLetterCount = 0;
                password[passwordLetterCount] = '\0';
            }
        }
        if (mouseOnRole) {
            int key = GetCharPressed();
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (roleLetterCount < 25)) {
                    role[roleLetterCount] = (char)key;
                    role[roleLetterCount + 1] = '\0';
                    roleLetterCount++;
                }

                key = GetCharPressed();
            }

            if (IsKeyPressed(KEY_BACKSPACE)) {
                roleLetterCount--;
                if (roleLetterCount < 0) roleLetterCount = 0;
                role[roleLetterCount] = '\0';
            }
        }


        if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(mousePosition, loginButton)) || IsKeyPressed(KEY_ENTER)) {
            Validate validator;
            if (validator.doesAccountExist(username)) {
                if (validator.isPasswordCorrect(username, password, role)) {
                    strcpy_s(currentUser, username);
                    if (strcmp(role, "student") == 0) {

                        studentDashboard();
                    }
                    else if (strcmp(role, "teacher") == 0) {

                        teacherDashboard();
                    }
                }

                if (!validator.doesAccountExist(username) || !validator.isPasswordCorrect(username, password, role)) {

                    password[0] = '\0';
                    username[0] = '\0';
                    role[0] = '\0';
                    usernameLetterCount = 0;
                    passwordLetterCount = 0;
                    roleLetterCount = 0;
                }
            }

        }

        BeginDrawing();
        
        ClearBackground(RAYWHITE);
        
        DrawTexture(background, 0, 0, WHITE);
        DrawTexture(logoTexture, 0, 0, WHITE);

        DrawText("Welcome back! Log in!", GetScreenWidth() / 2 - 289, GetScreenHeight() / 2 - 350, 50, WHITE);

        DrawRectangleLines(usernameBox.x, usernameBox.y, usernameBox.width, usernameBox.height, (mouseOnUsername ? RAYWHITE : WHITE));
        DrawText(username, usernameBox.x + 5, usernameBox.y + 8, 40, WHITE);

        DrawRectangleLines(passwordBox.x, passwordBox.y, passwordBox.width, passwordBox.height, (mouseOnPassword ? RAYWHITE : WHITE));
        DrawText(TextFormat("%.*s", passwordLetterCount, "**************************"), passwordBox.x + 5, passwordBox.y + 8, 40, WHITE);

        DrawRectangleLines(roleBox.x, roleBox.y, roleBox.width, roleBox.height, (mouseOnRole ? RAYWHITE : WHITE));
        DrawText(role, roleBox.x + 5, roleBox.y + 8, 40, WHITE);

        bool isMouseOverButtonLogin = CheckCollisionPointRec(mousePosition, loginButton);
        DrawText("Login", GetScreenWidth() / 2 - 85, GetScreenHeight() / 2 + 250, (CheckCollisionPointRec(mousePosition, loginButton) ? 60 : 50), WHITE);
        DrawText("Username:", GetScreenWidth() / 2 - 155, GetScreenHeight() / 2 - 225, 50, WHITE);
        DrawText("Password:", GetScreenWidth() / 2 - 155, GetScreenHeight() / 2 - 75, 50, WHITE);
        DrawText("Role:", GetScreenWidth() / 2 - 100, GetScreenHeight() / 2 + 70, 50, WHITE);


        EndDrawing();

    }

}

void startingScreen(bool hasInit) {
    const int screenWidth = 1920;
    const int screenHeight = 1080;

    if (!hasInit) {
        SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT);
        InitWindow(screenWidth, screenHeight, "FutureMinds - The Future of Learning");
        SetTargetFPS(60);
    }

    Texture2D logo = LoadTexture("../images/logo.png");

    Color accentColor = { 66, 153, 225, 255 };
    Color signupBtnColor = { 48, 140, 230, 255 };
    Color loginBtnColor = { 255, 161, 0, 255 };

    float timer = 0.0f;

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();
        timer += GetFrameTime();

        BeginDrawing();

        ClearBackground(WHITE);
        DrawRectangleGradientV(0, 0, screenWidth, screenHeight, WHITE, { 230, 240, 255, 255 });
        DrawCircleGradient(screenWidth / 2, screenHeight / 2, 800, Fade(accentColor, 0.05f), BLANK);

        DrawTexturePro(logo,
            { 0, 0, (float)logo.width, (float)logo.height },
            { 0, 0, (float)screenWidth, (float)screenHeight },
            { 0, 0 }, 0, Fade(WHITE, 0.15f));

        DrawRectangleRec({ 0, 0, (float)screenWidth, 100 }, Fade(WHITE, 0.9f));
        DrawLineEx({ 0, 100 }, { (float)screenWidth, 100 }, 1, Fade(LIGHTGRAY, 0.5f));

        DrawTextureEx(logo, { 27, 22 }, 0, 110.0f / logo.height, WHITE);
        DrawText("FutureMinds", 130, 50, 32, { 40, 40, 50, 255 });

        Rectangle loginBtnRec = { 1720, 40, 150, 50 };
        bool loginHover = CheckCollisionPointRec(mouse, loginBtnRec);
        DrawRectangleRoundedLines(loginBtnRec, 0.5f, 10, 2, loginHover ? BLACK : loginBtnColor);
        DrawText("LOG IN", loginBtnRec.x + 35, loginBtnRec.y + 15, 20, loginHover ? BLACK : loginBtnColor);

        if (loginHover && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            login();
        }

        float titleY = 350 + (sinf(timer * 2.0f) * 10.0f);

        DrawText("FUTUREMINDS", screenWidth / 2 - MeasureText("FUTUREMINDS", 120) / 2, (int)titleY, 120, { 30, 30, 45, 255 });

        float lineGrow = 300 + (sinf(timer * 1.5f) * 50.0f);
        DrawRectangleV({ (float)screenWidth / 2 - lineGrow / 2, titleY + 130 }, { lineGrow, 4 }, accentColor);

        DrawText("Master English through the power of our app.", screenWidth / 2 - MeasureText("Master English through the power of our app.", 28) / 2, (int)titleY + 160, 28, GRAY);

        Rectangle signupBtnRec = { screenWidth / 2 - 150, 650, 300, 80 };
        bool signupHover = CheckCollisionPointRec(mouse, signupBtnRec);

        if (signupHover) {
            DrawRectangleRounded({ signupBtnRec.x - 5, signupBtnRec.y - 5, signupBtnRec.width + 10, signupBtnRec.height + 10 }, 0.5f, 10, Fade(accentColor, 0.3f));
        }

        DrawRectangleRounded(signupBtnRec, 0.5f, 10, signupHover ? BLACK : signupBtnColor);
        DrawText("GET STARTED", signupBtnRec.x + 60, signupBtnRec.y + 25, 26, WHITE);

        if (signupHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            signup();
        }

        DrawRectangle(0, 955, screenWidth, 125, Fade(WHITE, 0.8f));
        DrawLine(0, 955, screenWidth, 955, Fade(LIGHTGRAY, 0.5f));

        DrawText("Crafted for Excellence", 50, 985, 18, DARKGRAY);
        DrawText("© 2026 FutureMinds Inc. All Rights Reserved.", 50, 1015, 16, GRAY);

        DrawText("Terms of Service", 450, 1000, 16, accentColor);
        DrawText("Privacy Policy", 600, 1000, 16, accentColor);
        DrawText("Support", 750, 1000, 16, accentColor);


        Rectangle exitBtnRec = { 1780, 980, 100, 40 };
        bool exitHover = CheckCollisionPointRec(mouse, exitBtnRec);
        DrawRectangleRounded(exitBtnRec, 0.3f, 10, exitHover ? RED : Fade(RED, 0.1f));
        DrawRectangleRoundedLines(exitBtnRec, 0.3f, 10, 1, RED);
        DrawText("EXIT", exitBtnRec.x + 30, exitBtnRec.y + 12, 18, exitHover ? WHITE : RED);

        if (exitHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            UnloadTexture(logo);
            CloseWindow();
            return;
        }

        EndDrawing();
    }

    UnloadTexture(logo);
    CloseWindow();
}