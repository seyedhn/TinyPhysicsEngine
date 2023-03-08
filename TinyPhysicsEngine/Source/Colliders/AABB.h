#pragma once
#include "Shape.h"

class AABB : public Shape
{

public:

  AABB(float minx, float miny, float maxx, float maxy);

  void UpdateRenderPosition(const Vector2f& new_pos) override;
  void DrawToWindow(sf::RenderWindow& window) const override;
  void ChangeColour(const sf::Color& colour) override;

  const float GetLength() const;
  const float GetHeight() const;
  AABB GetAABB() const override;
  void OnCollision(const Shape& other) override;
  
  bool IsColliding(const Shape& other) const override;
  bool IsCollidingWithBox(const AABB& other) const override;
  bool IsCollidingWithCircle(const Circle& other) const override;

  float min_x;
  float min_y;
  float max_x;
  float max_y;

protected:
  sf::RectangleShape RenderBoxShape;
  float length;
  float height;


};

