#pragma once
#pragma pack(push, 1)
template <typename T>
class Vector2
{
public:
    T x;
    T y;
    Vector2();
    Vector2(T x, T y);

    void normalize();
    T distance(const Vector2<T>& right);

    Vector2<T>& operator =(const Vector2<T>& right);
    Vector2<T>& operator +=(const Vector2<T>& right);
    Vector2<T>& operator -=(const Vector2<T>& right);

    Vector2<T>& operator *=(const T& right);
    Vector2<T>& operator /=(const T& right);
};
#pragma pack(pop)

template <typename T>
Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T> operator *(const Vector2<T>& left, const T& right);

template <typename T>
Vector2<T> operator /(const Vector2<T>& left, const T& right);

template <typename T>
bool operator ==(const Vector2<T>& left, const Vector2<T>& right);

#include "Vector2.inl"
