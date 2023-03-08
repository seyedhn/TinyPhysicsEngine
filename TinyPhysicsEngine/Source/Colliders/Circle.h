#pragma once
#include "Shape.h"

class Circle : public Shape
{

public:

  Circle(float radius, Vector2f _r1, Vector2f _r2);

  void UpdateRenderPosition(const Vector2f& new_pos) override;
  void DrawToWindow(sf::RenderWindow& window) const override;
  void ChangeColour(const sf::Color& colour) override;
 
  float GetRadius() const;
  AABB GetAABB() const override;
  void OnCollision(const Shape& other) override;

  bool IsColliding(const Shape& other) const override;
  bool IsCollidingWithCircle(const Circle& other) const override;
  bool IsCollidingWithBox(const AABB& other) const override;


private:
  float radius;
  sf::CircleShape RenderCircleShape;
};

