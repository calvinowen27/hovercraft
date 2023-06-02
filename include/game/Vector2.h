#ifndef VECTOR2_INCLUDE
#define VECTOR2_INCLUDE

#include "../SDL2/SDL.h"
#include <cmath>

class Vector2Int;

class Vector2
{
    public:
        float x, y;
        Vector2();
        Vector2(float x, float y);
        Vector2(const Vector2 &b);
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
        explicit operator Vector2Int() const;
};

class Vector2Int
{
    public:
        int x, y;
        Vector2Int();
        Vector2Int(int x, int y);
        Vector2Int(float x, float y);
        Vector2Int(double x, double y);
        Vector2Int(const Vector2Int &b);
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
        explicit operator Vector2() const;
};

#endif