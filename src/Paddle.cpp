#include "Paddle.hpp"
#include <raylib.h>

Paddle::Paddle() 
    : x_first(0)
    , y_first(0)
    , w(GetScreenWidth())
    , h(GetScreenHeight())
    , y_second(0)
    , Speed(750)
{
}

void Paddle::Update()
{
    x_second = w - w * 0.03;

    float dt = GetFrameTime();

    if (IsKeyDown(KEY_W) && y_first > 0) {
        y_first -= Speed * dt;
    }
    if (IsKeyDown(KEY_S) && y_first < h - h * 0.4) {
        y_first += Speed * dt;
    }
    if (IsKeyDown(KEY_UP) && y_second > 0) {
        y_second -= Speed * dt;
    }
    if (IsKeyDown(KEY_DOWN) && y_second < h - h * 0.4) {
        y_second += Speed * dt;
    }

    P_One = {x_first, y_first, w * 0.03f, h * 0.4f};
    P_Two = {x_second, y_second, w* 0.03f, h * 0.4f};
}

void Paddle::Draw() const
{
    DrawRectangleRec(P_One, WHITE);
    DrawRectangleRec(P_Two, WHITE);
}

Rectangle Paddle::GetP_One() const
{
    return P_One;
}

Rectangle Paddle::GetP_Two() const
{
    return P_Two;
}