#pragma once
#include <cstdlib>
#include <algorithm>


template<typename T>
class Vector2
{
public:

  Vector2();
  Vector2(T x, T y);
  Vector2(int lb, int ub, int lb2, int ub2);

  Vector2<T> operator+(const Vector2<T>  &vec);
  Vector2<T> operator-(const Vector2<T> &vec);
  Vector2<T> operator*(const float coef);
  T operator*(const Vector2<T>& vec);
  void operator+=(const Vector2<T>& vec);
  void operator*=(const float coef);

  void setX(const T& x);
  void setY(const T& y);
  void setVector(const float& x, const float& y);

  void Normalise();
  float length() const;

  T x;
  T y;

};

template<typename T>
Vector2<T> operator*(float coef, const Vector2<T>& vec);

using Vector2f = Vector2<float>;
using Vector2i = Vector2<int>;


//DEFINITIONS
//////////////////////////////////////////////////////////////

template<typename T>
Vector2<T>::Vector2()
  : x(0.f), y(0.f)
{
}

template<typename T>
Vector2<T>::Vector2(T _x, T _y)
  : x(_x), y(_y)
{
}

template<typename T>
Vector2<T>::Vector2(int x_lb, int x_ub, int y_lb, int y_ub)
  : x(float(rand() % (x_ub - x_lb + 1) + x_lb))
  , y(float(rand() % (y_ub - y_lb + 1) + y_lb))
{
}

template<typename T>
Vector2<T> Vector2<T>::operator+(const Vector2<T>& vec2)
{
  Vector2<T> vec1;
  vec1.x = x + vec2.x;
  vec1.y = y + vec2.y;
  return vec1;
}

template<typename T>
Vector2<T> Vector2<T>::operator-(const Vector2<T>& vec2)
{
  Vector2<T> vec1;
  vec1.x = x - vec2.x;
  vec1.y = y - vec2.y;
  return vec1;
}

template<typename T>
Vector2<T> Vector2<T>::operator*(const float coef)
{
  Vector2<T> vec;
  vec.x = coef * x;
  vec.y = coef * y;
  return vec;
}

template<typename T>
T Vector2<T>::operator*(const Vector2<T>& vec)
{
  return x * vec.x + y * vec.y;
}

template<typename T>
void Vector2<T>::operator+=(const Vector2<T>& vec)
{
  x += vec.x;
  y += vec.y;
}

template<typename T>
void Vector2<T>::operator*=(const float coef)
{
  x *= coef;
  y *= coef;
}

template<typename T>
void Vector2<T>::setX(const T& _x)
{
  x = _x;
}

template<typename T>
void Vector2<T>::setY(const T& _y)
{
  y = _y;
}

template<typename T>
void Vector2<T>::setVector(const float& _x, const float& _y)
{
  x = _x;
  y = _y;
}

template<typename T>
void Vector2<T>::Normalise()
{
  float magX = std::max(x, -x);
  float magY = std::max(y, -y);

  //CURRENTLY ONLY HANDLES FLOAT. EXPAND
  if (magX == 0.f && magY == 0.f)
    return;

  if (magX == 0.f)
  {
    y = (y > 0.f) ? 1.f : -1.f;
    return;
  }

  if (magY == 0.f)
  {
    x = (x > 0.f) ? 1.f : -1.f;
    return;
  }

  float total = sqrt(magX * magX + magY * magY);
  x /= total;
  y /= total;
}

template<typename T>
float Vector2<T>::length() const
{
  return sqrt(x * x + y * y);
}

template<typename T>
Vector2<T> operator*(float coef, const Vector2<T>& vec)
{
  Vector2<T> vec1;
  vec1.x = coef * vec.x;
  vec1.y = coef * vec.y;
  return vec1;
}
