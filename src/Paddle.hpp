#ifndef PADDLE_HPP
#define PADDLE_HPP
#include <raylib.h>

class Paddle 
{
    public:
    Paddle();
    void Update();
    void Draw() const;
    Rectangle GetP_One() const;
    Rectangle GetP_Two() const;

    private:
    float x_first, y_first, x_second, y_second;
    float Speed;
    float w, h;
    Rectangle P_One, P_Two;
};

#endif