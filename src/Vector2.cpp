#include "../include/game/Vector2.h"

/* Vector2 */
Vector2::Vector2()
{
    this->x = 0;
    this->y = 0;
}

Vector2::Vector2(float x, float y)
{
    this->x = x;
    this->y = y;
}

Vector2::Vector2(const Vector2 &b)
{
    this->x = b.x;
    this->y = b.y;
}

float distance(const Vector2 &a, const Vector2 &b)
{
    return (float)(sqrt(pow(b.x-a.x, 2)+pow(b.y-a.y, 2)));
}

bool Vector2::equals(const Vector2& b) const
{
    return x == b.x && y == b.y;
}

bool operator==(const Vector2& a, const Vector2& b)
{
    return a.equals(b);
}

Vector2 Vector2::operator+(const Vector2 &b) const
{
    return Vector2(b.x+x, b.y+y);
}

Vector2 Vector2::operator-(const Vector2 &b) const
{
    return Vector2(b.x-x, b.y-y);
}

Vector2 Vector2::operator*(const float &a) const
{
    return Vector2(x*a, y*a);
}

Vector2 Vector2::operator/(const float &a) const
{
    return Vector2(x/a, y/a);
}

Vector2& Vector2::operator=(const Vector2 &b)
{
    x = b.x;
    y = b.y;

    return *this;
}

Vector2& Vector2::operator+=(const Vector2 &b)
{
    x += b.x;
    y += b.y;

    return *this;
}

Vector2& Vector2::operator-=(const Vector2 &b)
{
    x -= b.x;
    y -= b.y;

    return *this;
}

Vector2& Vector2::operator*=(const float &a)
{
    x *= a;
    y *= a;

    return *this;
}

Vector2& Vector2::operator/=(const float &a)
{
    x /= a;
    y /= a;

    return *this;
}

Vector2::operator Vector2Int() const
{
    return Vector2Int((int)x, (int)y);
}

/* Vector2Int */

Vector2Int::Vector2Int()
{
    this->x = 0;
    this->y = 0;
}

Vector2Int::Vector2Int(int x, int y)
{
    this->x = x;
    this->y = y;
}

Vector2Int::Vector2Int(float x, float y)
{
    this->x = (int)x;
    this->y = (int)y;
}

Vector2Int::Vector2Int(double x, double y)
{
    this->x = (int)x;
    this->y = (int)y;
}

Vector2Int::Vector2Int(const Vector2Int &b)
{
    this->x = b.x;
    this->y = b.y;
}

float distance(const Vector2Int &a, const Vector2Int &b)
{
    return (float)(sqrt(pow(b.x-a.x, 2)+pow(b.y-a.y, 2)));
}

bool Vector2Int::equals(const Vector2Int &b) const
{
    return x == b.x && y == b.y;
}

bool operator==(const Vector2Int &a, const Vector2Int &b)
{
    return a.equals(b);
}

Vector2Int Vector2Int::operator+(const Vector2Int &b) const
{
    return Vector2Int(b.x+x, b.y+y);
}

Vector2Int Vector2Int::operator-(const Vector2Int &b) const
{
    return Vector2Int(b.x-x, b.y-y);
}

Vector2Int Vector2Int::operator*(const float &a) const
{
    return Vector2Int((int)(x*a), (int)(y*a));
}

Vector2Int Vector2Int::operator/(const float &a) const
{
    return Vector2Int((int)(x/a), (int)(y/a));
}

Vector2Int& Vector2Int::operator=(const Vector2Int &b)
{
    x = b.x;
    x = b.y;

    return *this;
}

Vector2Int& Vector2Int::operator+=(const Vector2Int &b)
{
    x += b.x;
    y += b.y;

    return *this;
}

Vector2Int& Vector2Int::operator-=(const Vector2Int &b)
{
    x -= b.x;
    y -= b.y;

    return *this;
}

Vector2Int& Vector2Int::operator*=(const float &a)
{
    x = (int)(x*a);
    y = (int)(y*a);

    return *this;
}

Vector2Int& Vector2Int::operator/=(const float &a)
{
    x = (int)(x/a);
    y = (int)(y/a);

    return *this;
}

Vector2Int::operator Vector2() const
{
    return Vector2(x, y);
}