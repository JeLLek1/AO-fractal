#pragma once
#include "Vector2.h"
#include <cmath>

template <typename T>
inline Vector2<T>::Vector2() {
    this->x = this->y = 0;
}

template <typename T>
inline Vector2<T>::Vector2(T x, T y) {
    this->x = x;
    this->y = y;
}

template<typename T>
inline void Vector2<T>::normalize() {
    (*this) /= std::sqrt(this->x * this->x + this->y * this->y);
}

template<typename T>
inline T Vector2<T>::distance(const Vector2<T>& right) {
    return std::sqrt((this->x - right.x) * (this->x - right.x)
        + (this->y - right.y) * (this->y - right.y));
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator=(const Vector2<T>& right) {
    this->x = right.x;
    this->y = right.y;
    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator+=(const Vector2<T>& right) {
    this->x += right.x;
    this->y += right.y;

    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator-=(const Vector2<T>& right) {
    this->x -= right.x;
    this->y -= right.y;

    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator*=(const T& right) {
    this->x *= right;
    this->y *= right;

    return *this;
}

template<typename T>
inline Vector2<T>& Vector2<T>::operator/=(const T& right) {
    this->x /= right;
    this->y /= right;

    return *this;
}

template<typename T>
inline Vector2<T> operator +(const Vector2<T>& left, const Vector2<T>& right) {
    return Vector2<T>(left.x + right.x, left.y + right.y);
}

template<typename T>
inline Vector2<T> operator -(const Vector2<T>& left, const Vector2<T>& right) {
    return Vector2<T>(left.x - right.x, left.y - right.y);
}

template<typename T>
inline Vector2<T> operator *(const Vector2<T>& left, const T& right) {
    return Vector2<T>(left.x * right, left.y * right);
}

template<typename T>
inline Vector2<T> operator /(const Vector2<T>& left, const T& right) {
    return Vector2<T>(left.x / right, left.y / right);
}

template <typename T>
inline bool operator ==(const Vector2<T>& left, const Vector2<T>& right) {
    if (left.x == right.x && left.y == right.y) {
        return true;
    }
    return false;
}
