#ifndef VECTOR2_INCLUDE
#define VECTOR2_INCLUDE

#include "../SDL2/SDL.h"
#include <cmath>

class Vector2
{
    public:
        float x, y;
        Vector2();
        Vector2(float x, float y);
        friend float distance(Vector2 a, Vector2 b);
        bool equals(const Vector2 &b) const;
        friend bool operator==(const Vector2 &a, const Vector2 &b);
        Vector2 operator+(const Vector2 &b) const;
        Vector2 operator-(const Vector2 &b) const;
        Vector2 operator*(const float &a) const;
        Vector2 operator/(const float &a) const;
        Vector2& operator=(const Vector2 &b);
        Vector2& operator+=(const Vector2 &b);
        Vector2& operator-=(const Vector2 &b);
        Vector2& operator*=(const float &a);
        Vector2& operator/=(const float &a);
        operator Vector2Int();
};

class Vector2Int
{
    public:
        int x, y;
        Vector2Int();
        Vector2Int(int x, int y);
        Vector2Int(float x, float y);
        Vector2Int(double x, double y);
        friend float distance(Vector2Int a, Vector2Int b);
        bool equals(const Vector2Int &b) const;
        friend bool operator==(const Vector2Int &a, const Vector2Int &b);
        Vector2Int operator+(const Vector2Int &b) const;
        Vector2Int operator-(const Vector2Int &b) const;
        Vector2Int operator*(const float &a) const;
        Vector2Int operator/(const float &a) const;
        Vector2Int& operator=(const Vector2Int &b);
        Vector2Int& operator+=(const Vector2Int &b);
        Vector2Int& operator-=(const Vector2Int &b);
        Vector2Int& operator*=(const float &a);
        Vector2Int& operator/=(const float &a);
        operator Vector2();
};

#endif