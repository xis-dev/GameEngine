//
// Created by Joni on 25/11/2026.
//
#pragma once

namespace AGPT_Engine {

    struct  Vector2
    {
float x, y = 0.0f;

        Vector2() = default;
        Vector2(float x, float y) : x(x), y(y) {}

        Vector2 operator+(const Vector2& rhs) const
        {
            return Vector2(x + rhs.x, y + rhs.y);
        }

        Vector2 operator-(const Vector2& rhs) const
        {
            return Vector2(x - rhs.x, y - rhs.y);
        }

        Vector2 operator*(const Vector2& rhs) const
        {
            return Vector2(x * rhs.x, y * rhs.y);
        }

        Vector2 operator/(const Vector2& rhs) const
        {

            return Vector2(x / rhs.x, y / rhs.y);
        }



    };

}


