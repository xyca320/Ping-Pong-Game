#include <raylib.h>
#include <unistd.h>
#include "Ball.hpp"
#include "Paddle.hpp"
#include "ScoreCount.hpp"

using namespace std;

int main() 
{   
    constexpr int screenWidth = 2560;
    constexpr int screenHeight = 1440;

    InitWindow(screenWidth, screenHeight, "Ping Pong Game");
    SetTargetFPS(144);
    InitAudioDevice();
    
    Ball ball;
    Paddle Paddles;
    score Scores;

    Font ScoreTextFont = LoadFont("assets/Arcade.ttf");

    Sound Goal = LoadSound("assets/roblox-congrats.mp3"), Win = LoadSound("assets/aplausos_2.mp3");

    string P_OneAbilityText = "[D] - P1 ABILITY", P_TwoAbilityText = "[LEFT] - P1 ABILITY";
    
    while (!WindowShouldClose())
    {
        if (ball.WLog() == "P1") {
            PlaySound(Goal);
            Scores.IncreaseCounter(1);
            ball.Reset();
        } else if (ball.WLog() == "P2") {
            PlaySound(Goal);
            Scores.IncreaseCounter(2);
            ball.Reset();
        }

        if (Scores.GetScore(1) >= 5) {
            PlaySound(Win);
            Scores.ResetCounter();
            BeginDrawing();
                const char* WinText = "P1 is the winner winner chicken dinner!!!";
                Vector2 TextDimensions = MeasureTextEx(ScoreTextFont, WinText, 50, 2);

                DrawTextEx(ScoreTextFont, WinText, {screenWidth / 2 - TextDimensions.x / 2, screenHeight / 2 - TextDimensions.y / 2}, 50, 2, WHITE);
            EndDrawing();

            sleep(5);
        } else if (Scores.GetScore(2) >= 5) {
            sleep(2);
            PlaySound(Win);
            Scores.ResetCounter();
            BeginDrawing();
                const char* WinText = "P2 is the winner winner chicken dinner!!!";
                Vector2 TextDimensions = MeasureTextEx(ScoreTextFont, WinText, 50, 2);

                DrawTextEx(ScoreTextFont, WinText, {screenWidth / 2 - TextDimensions.x / 2, screenHeight / 2 - TextDimensions.y / 2}, 50, 2, WHITE);
            EndDrawing();

            sleep(5);
        }

        if (IsKeyDown(KEY_D)) {
            ball.ActivateAbility(1);
        }
        if (IsKeyDown(KEY_LEFT)) {
            ball.ActivateAbility(2);
        }

        if (ball.GetCooldownTimer(1) > 0.0f) {
            P_OneAbilityText = "Ability on Cooldown - " + to_string(ball.GetCooldownTimer(1)) + "s";
        } else {
            P_OneAbilityText = "[D] - P1 ABILITY";
        }

        if (ball.GetCooldownTimer(2) > 0.0f) {
            P_TwoAbilityText = "Ability on Cooldown - " + to_string(ball.GetCooldownTimer(2)) + "s";
        } else {
            P_TwoAbilityText = "[LEFT] - P2 ABILITY";
        }

        ball.Update(Paddles);
        Paddles.Update();

        string P_OneText = "P1 - " + to_string(Scores.GetScore(1));
        string P_TwoText = "P2 - " + to_string(Scores.GetScore(2));
        
        BeginDrawing();
            ClearBackground(BLACK);
            DrawTextEx(ScoreTextFont, P_OneText.c_str(), {screenWidth * 0.3, screenHeight - screenHeight * 0.05}, 30, 2, WHITE);
            DrawTextEx(ScoreTextFont, P_TwoText.c_str(), {screenWidth - screenWidth * 0.3, screenHeight - screenHeight * 0.05}, 30, 2, WHITE);

            DrawTextEx(ScoreTextFont, P_OneAbilityText.c_str(), {screenWidth * 0.05, screenHeight - screenHeight * 0.05}, 30, 2, WHITE);
            DrawTextEx(ScoreTextFont, P_TwoAbilityText.c_str(), {screenWidth - screenWidth * 0.15, screenHeight - screenHeight * 0.05}, 30, 2, WHITE);

            ball.Draw();
            Paddles.Draw();
        EndDrawing();
    }

    CloseAudioDevice();
    UnloadFont(ScoreTextFont);
    UnloadSound(Goal);
    
    CloseWindow();
}