#include "Ball.hpp"
#include <raylib.h>
#include <string>
#include <cmath>

Ball::Ball() 
    : x(GetScreenWidth() / 2.0f)
    , y(GetScreenHeight() / 2.0f)
    , speedX(500.0f)
    , speedY(500.0f)
    , radius(15.0f) 
{
    Pop = LoadSound("assets/Pop.wav");
    Hit = LoadSound("assets/Paddle Hit.mp3");
    Smash = LoadSound("assets/Smash.mp3");
}

Ball::~Ball()
{
    UnloadSound(Pop);
    UnloadSound(Hit);
    UnloadSound(Smash);
}

void Ball::Update(const Paddle& Paddles)
{
    float dt = GetFrameTime();

    if (OneCoolDown > 0.0f) OneCoolDown -= dt;
    if (TwoCoolDown > 0.0f) TwoCoolDown -= dt;

    if (CntDown > 0) {
        CntDown -= dt;
        return;
    }

    x += speedX * dt;
    y += speedY * dt;

    const float screenHeight = GetScreenHeight();
    Rectangle p1 = Paddles.GetP_One();
    Rectangle p2 = Paddles.GetP_Two();

    if (CheckCollisionCircleRec({ x, y }, radius, p1)) {
        bool smashedThisFrame = false;

        if (IsOneSmashing) {
            speedX *= 2.5f;
            speedY *= 2.5f;
            IsOneSmashing = false;
            smashedThisFrame = true;
        } else if (IsOneBeingCaught) {
            speedX = 500.0f;
            speedY = 500.0f;
            IsOneBeingCaught = false;
        }

        if (speedX < 0) {
            speedX *= -1;
            if (smashedThisFrame) {
                PlaySound(Smash);
            } else {
                PlaySound(Hit);
            }
        }
    }

    if (CheckCollisionCircleRec({ x, y }, radius, p2)) {
        bool smashedThisFrame = false;

        if (IsTwoSmashing) {
            speedX *= 2.5f;
            speedY *= 2.5f;
            IsTwoSmashing = false;
            smashedThisFrame = true;
        } else if (IsTwoBeingCaught) {
            speedX = 500.0f;
            speedY = 500.0f;
            IsTwoBeingCaught = false;
        }

        if (speedX > 0) {
            speedX *= -1;
            if (smashedThisFrame) {
                PlaySound(Smash);
            } else {
                PlaySound(Hit);
            }
        }
    }

    if (y + radius >= screenHeight || y - radius <= 0) {
        PlaySound(Pop);
        speedY *= -1;
    }
}

void Ball::Draw() const
{
    DrawCircle(x, y, radius, WHITE);
}

void Ball::Reset()
{
    x = GetScreenWidth() / 2.0f;
    y = GetScreenHeight() / 2.0f;
    speedX = 500.0f;
    speedY = 500.0f;
    CntDown = 3.0f;
    
    IsOneSmashing = false;
    IsTwoSmashing = false;
}

void Ball::ActivateAbility(int PlrNum)
{
    if (PlrNum == 1 && OneCoolDown <= 0.0f && !IsOneSmashing) {
        IsOneSmashing = true;
        IsOneBeingCaught = true;
        OneCoolDown = 5.0f;
    } 
    else if (PlrNum == 2 && TwoCoolDown <= 0.0f && !IsTwoSmashing) {
        IsTwoSmashing = true;
        IsTwoBeingCaught = true;
        TwoCoolDown = 5.0f;
    }
}

float Ball::GetCooldownTimer(int PlrNum) 
{
    if (PlrNum == 1) {
        return roundf(OneCoolDown);
    } else {
        return roundf(TwoCoolDown);
    }
}

std::string Ball::WLog() {
    if (x < 0) return "P2";
    else if (x + radius > GetScreenWidth()) return "P1";
    else return "Nil";
}