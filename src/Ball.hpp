#pragma once
#include <raylib.h>
#include <string>
#include "Paddle.hpp"

class Ball
{
public:
    Ball();
    ~Ball();
    void Update(const Paddle& Paddles);
    void Draw() const;
    void Reset();
    void ActivateAbility(int PlrNum);
    float GetCooldownTimer(int PlrNum);
    std::string WLog();

private:
    float x;
    float y;
    float speedX;
    float speedY;
    float radius;

    float CntDown = 0.0f, OneCoolDown = 0.0f, TwoCoolDown = 0.0f;

    bool IsOneSmashing = false, IsTwoSmashing = false, IsOneBeingCaught = false, IsTwoBeingCaught = false;

    Sound Pop, Hit, Smash;
};