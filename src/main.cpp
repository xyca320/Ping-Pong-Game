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
    SetTargetFPS(GetMonitorRefreshRate(GetCurrentMonitor()));
    InitAudioDevice();
    
    Ball ball;
    Paddle Paddles;
    score Scores;

    Font ScoreTextFont = LoadFont("assets/Arcade.ttf");

    Sound Goal = LoadSound("assets/roblox-congrats.mp3"), Win = LoadSound("assets/aplausos_2.mp3");
    Music BGM = LoadMusicStream("assets/Color 4.mp3");

    string P_OneAbilityText = "[D] - P1 ABILITY", P_TwoAbilityText = "[LEFT] - P1 ABILITY";

    int CurrentBGMTrack = 1;

    PlayMusicStream(BGM);
    
    while (!WindowShouldClose())
    {
        UpdateMusicStream(BGM);

        if (GetMusicTimePlayed(BGM) >= GetMusicTimeLength(BGM)) {
            UnloadMusicStream(BGM); 

            if (CurrentBGMTrack == 1) {
                CurrentBGMTrack = 2;
                BGM = LoadMusicStream("assets/Color 2.mp3");
            } else if (CurrentBGMTrack == 2) {
                CurrentBGMTrack = 3;
                BGM = LoadMusicStream("assets/Color 3.mp3");
            } else if (CurrentBGMTrack == 3) {
                CurrentBGMTrack = 4;
                BGM = LoadMusicStream("assets/Color 4.mp3");
            } else {
                CurrentBGMTrack = 1;
                BGM = LoadMusicStream("assets/Color 1.mp3");
            }

            PlayMusicStream(BGM);
        }

        if (ball.WLog() == "P1") {
            PlaySound(Goal);
            Scores.IncreaseCounter(1);
            ball.Reset();
        } else if (ball.WLog() == "P2") {
            PlaySound(Goal);
            Scores.IncreaseCounter(2);
            ball.Reset();
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
    UnloadSound(Win);
    UnloadMusicStream(BGM);
    
    CloseWindow();
}