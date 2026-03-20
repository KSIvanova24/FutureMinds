#include "auth.h"
#include "dashboards.h"
#include "accessData.h"
#include "validation.h"

void DrawModernInput(Rectangle box, const char* label, const char* text, bool isHovered, bool isPassword, int fontSize) {
    DrawText(label, box.x, box.y - 30, 20, DARKGRAY);
    DrawRectangleRounded(box, 0.2f, 10, WHITE);

    Color borderColor = isHovered ? Color ({ 66, 153, 225, 255 }) : LIGHTGRAY;
    DrawRectangleRoundedLines(box, 0.2f, 10, 2, borderColor);

    if (isPassword) {
        std::string dots(strlen(text), '*');
        DrawText(dots.c_str(), box.x + 15, box.y + (box.height / 2 - fontSize / 2), fontSize, BLACK);
    }
    else {
        DrawText(text, box.x + 15, box.y + (box.height / 2 - fontSize / 2), fontSize, BLACK);
    }
}

void signup() {
    char username[25] = "";
    char password[25] = "";
    char repeatPassword[25] = "";
    int usernameLetterCount = 0;
    int passwordLetterCount = 0;
    int repeatPasswordLetterCount = 0;

    Color fmBlue = { 66, 153, 225, 255 };
    Color fmPurple = { 128, 90, 213, 255 };
    Color bgLight = { 240, 244, 248, 255 };

    Rectangle mainPanel = { GetScreenWidth() / 2 - 350, GetScreenHeight() / 2 - 400, 700, 800 };

    DataAccess account;
    Validate validator;
    Texture2D logo = LoadTexture("../images/logo.png");

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        Rectangle userBox = { mainPanel.x + 75, mainPanel.y + 250, 550, 60 };
        Rectangle passBox = { mainPanel.x + 75, mainPanel.y + 360, 550, 60 };
        Rectangle repPassBox = { mainPanel.x + 75, mainPanel.y + 470, 550, 60 };
        Rectangle signupButton = { mainPanel.x + 75, mainPanel.y + 580, 550, 75 };

        bool hoverUser = CheckCollisionPointRec(mouse, userBox);
        bool hoverPass = CheckCollisionPointRec(mouse, passBox);
        bool hoverRep = CheckCollisionPointRec(mouse, repPassBox);
        bool hoverBtn = CheckCollisionPointRec(mouse, signupButton);

        if (hoverUser || hoverPass || hoverRep) SetMouseCursor(MOUSE_CURSOR_IBEAM);
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        // --- PRESERVED BACKEND INPUT LOGIC ---
        int key = GetCharPressed();
        if (hoverUser) {
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (usernameLetterCount < 24)) {
                    username[usernameLetterCount++] = (char)key;
                    username[usernameLetterCount] = '\0';
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && usernameLetterCount > 0) username[--usernameLetterCount] = '\0';
        }
        if (hoverPass) {
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (passwordLetterCount < 24)) {
                    password[passwordLetterCount++] = (char)key;
                    password[passwordLetterCount] = '\0';
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && passwordLetterCount > 0) password[--passwordLetterCount] = '\0';
        }
        if (hoverRep) {
            while (key > 0) {
                if ((key >= 32) && (key <= 125) && (repeatPasswordLetterCount < 24)) {
                    repeatPassword[repeatPasswordLetterCount++] = (char)key;
                    repeatPassword[repeatPasswordLetterCount] = '\0';
                }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && repeatPasswordLetterCount > 0) repeatPassword[--repeatPasswordLetterCount] = '\0';
        }

        // --- PRESERVED SIGNUP VALIDATION ---
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoverBtn) {
            if (strcmp(password, repeatPassword) != 0) {
                password[0] = '\0'; repeatPassword[0] = '\0';
                passwordLetterCount = 0; repeatPasswordLetterCount = 0;
            }
            else {
                if (validator.containsUppercase(password) && validator.containsLowercase(password) &&
                    validator.containsDigit(password) && validator.containsSpecial(password)) {
                    account.addAccount(username, password);
                    strcpy_s(currentUser, username);
                    studentDashboard();
                }
                else {
                    password[0] = '\0'; repeatPassword[0] = '\0';
                    passwordLetterCount = 0; repeatPasswordLetterCount = 0;
                }
            }
        }

        BeginDrawing();
        ClearBackground(bgLight);
        DrawRectangleGradientH(0, 0, GetScreenWidth() / 2, GetScreenHeight(), fmBlue, bgLight);

        DrawRectangleRounded(mainPanel, 0.05f, 10, WHITE);
        DrawRectangleRoundedLines(mainPanel, 0.05f, 10, 1, Fade(LIGHTGRAY, 0.5f));

        DrawTextureEx(logo, { mainPanel.x + mainPanel.width / 2 - 50, mainPanel.y + 40 }, 0, 100.0f / logo.height, WHITE);
        DrawText("Create your Account", mainPanel.x + 190, mainPanel.y + 160, 32, { 45, 55, 72, 255 });
        DrawText("Password must contain: Upper, Lower, Digit, Special", mainPanel.x + 135, mainPanel.y + 200, 18, RED);

        DrawModernInput(userBox, "Username", username, hoverUser, false, 25);
        DrawModernInput(passBox, "Password", password, hoverPass, true, 25);
        DrawModernInput(repPassBox, "Repeat Password", repeatPassword, hoverRep, true, 25);

        DrawRectangleRounded(signupButton, 0.2f, 10, hoverBtn ? fmPurple : fmBlue);
        DrawText("SIGN UP", signupButton.x + (signupButton.width / 2 - MeasureText("SIGN UP", 25) / 2), signupButton.y + 25, 25, WHITE);

        EndDrawing();
    }
    UnloadTexture(logo);
}

void login() {
    char username[25] = "";
    char password[25] = "";
    char role[25] = "";
    int usernameLetterCount = 0, passwordLetterCount = 0, roleLetterCount = 0;

    Color fmBlue = { 66, 153, 225, 255 };
    Color bgLight = { 240, 244, 248, 255 };
    Rectangle mainPanel = { GetScreenWidth() / 2 - 350, GetScreenHeight() / 2 - 350, 700, 700 };

    Validate validator;
    Texture2D logo = LoadTexture("../images/logo.png");

    while (!WindowShouldClose()) {
        Vector2 mouse = GetMousePosition();

        Rectangle userBox = { mainPanel.x + 75, mainPanel.y + 250, 550, 60 };
        Rectangle passBox = { mainPanel.x + 75, mainPanel.y + 360, 550, 60 };
        Rectangle roleBox = { mainPanel.x + 75, mainPanel.y + 470, 550, 60 };
        Rectangle loginButton = { mainPanel.x + 75, mainPanel.y + 570, 550, 75 };

        bool hoverUser = CheckCollisionPointRec(mouse, userBox);
        bool hoverPass = CheckCollisionPointRec(mouse, passBox);
        bool hoverRole = CheckCollisionPointRec(mouse, roleBox);
        bool hoverBtn = CheckCollisionPointRec(mouse, loginButton);

        if (hoverUser || hoverPass || hoverRole) SetMouseCursor(MOUSE_CURSOR_IBEAM);
        else SetMouseCursor(MOUSE_CURSOR_DEFAULT);

        // --- PRESERVED BACKEND INPUT LOGIC ---
        int key = GetCharPressed();
        if (hoverUser) {
            while (key > 0) {
                if (usernameLetterCount < 24) { username[usernameLetterCount++] = (char)key; username[usernameLetterCount] = '\0'; }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && usernameLetterCount > 0) username[--usernameLetterCount] = '\0';
        }
        if (hoverPass) {
            while (key > 0) {
                if (passwordLetterCount < 24) { password[passwordLetterCount++] = (char)key; password[passwordLetterCount] = '\0'; }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && passwordLetterCount > 0) password[--passwordLetterCount] = '\0';
        }
        if (hoverRole) {
            while (key > 0) {
                if (roleLetterCount < 24) { role[roleLetterCount++] = (char)key; role[roleLetterCount] = '\0'; }
                key = GetCharPressed();
            }
            if (IsKeyPressed(KEY_BACKSPACE) && roleLetterCount > 0) role[--roleLetterCount] = '\0';
        }

        // --- PRESERVED LOGIN VALIDATION ---
        if ((IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && hoverBtn) || IsKeyPressed(KEY_ENTER)) {
            if (validator.doesAccountExist(username)) {
                if (validator.isPasswordCorrect(username, password, role)) {
                    strcpy_s(currentUser, username);
                    if (strcmp(role, "student") == 0) studentDashboard();
                    else if (strcmp(role, "teacher") == 0) teacherDashboard();
                }
                else {
                    username[0] = '\0'; password[0] = '\0'; role[0] = '\0';
                    usernameLetterCount = 0; passwordLetterCount = 0; roleLetterCount = 0;
                }
            }
        }

        BeginDrawing();
        ClearBackground(bgLight);
        DrawRectangleGradientV(0, 0, GetScreenWidth(), GetScreenHeight(), fmBlue, Color ({ 128, 90, 213, 255 }));

        DrawRectangleRounded(mainPanel, 0.05f, 10, WHITE);

        DrawTextureEx(logo, { mainPanel.x + 75, mainPanel.y + 50 }, 0, 80.0f / logo.height, WHITE);
        DrawText("Welcome Back!", mainPanel.x + 75, mainPanel.y + 150, 35, { 45, 55, 72, 255 });
        DrawText("Log in to continue your learning journey", mainPanel.x + 75, mainPanel.y + 195, 18, GRAY);

        DrawModernInput(userBox, "Username / Email", username, hoverUser, false, 25);
        DrawModernInput(passBox, "Password", password, hoverPass, true, 25);
        DrawModernInput(roleBox, "Role (student/teacher)", role, hoverRole, false, 25);

        DrawRectangleRounded(loginButton, 0.2f, 10, hoverBtn ? Color ({ 48, 140, 230, 255 }) : fmBlue);
        DrawText("LOG IN", loginButton.x + (loginButton.width / 2 - MeasureText("LOG IN", 25) / 2), loginButton.y + 25, 25, WHITE);

        EndDrawing();
    }
    UnloadTexture(logo);
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

        DrawText("Crafted for Excellence", 50, 985, 20, DARKGRAY);
        DrawText("© 2026 FutureMinds Inc. All Rights Reserved.", 50, 1015, 20, GRAY);

        DrawText("Terms of Service", 550, 1000, 24, accentColor);
        DrawText("Privacy Policy", 800, 1000, 24, accentColor);
        DrawText("Support", 1000, 1000, 24, accentColor);


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