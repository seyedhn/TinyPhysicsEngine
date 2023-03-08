#include "Circle.h"
#include "Source/Engine/CollisionFunctions.h"
#include <iostream>

Circle::Circle(float _radius, Vector2f _r, Vector2f _v)
  : radius(_radius), RenderCircleShape(_radius)
{
  RenderCircleShape.setFillColor(sf::Color::Green);
  r0 = _r;
  r = _r;
  v = _v;
  m = 0.1f;
  SimulatePhysics = true;
}

void Circle::UpdateRenderPosition(const Vector2f& new_pos)
{
  RenderCircleShape.setPosition(r.x - radius, r.y - radius);
}

void Circle::DrawToWindow(sf::RenderWindow& window) const
{
  window.draw(RenderCircleShape);
}

void Circle::ChangeColour(const sf::Color& colour)
{
  RenderCircleShape.setFillColor(colour);
}

float Circle::GetRadius() const
{
  return radius;
}

AABB Circle::GetAABB() const
{
  Vector2f p = GetPos();
  float r = GetRadius();

  float min_x = p.x - r;
  float min_y = p.y - r;
  float max_x = p.x + r;
  float max_y = p.y + r;

  return AABB(min_x, min_y, max_x, max_y);
}

void Circle::OnCollision(const Shape& other)
{
  ChangeColour(sf::Color::Cyan);
}

bool Circle::IsColliding(const Shape& other) const
{
  return other.IsCollidingWithCircle(*this);
}

bool Circle::IsCollidingWithCircle(const Circle& other) const
{
  return CollisionFunctions::CircleCircleCollisionCheck(*this, other);
}

bool Circle::IsCollidingWithBox(const AABB& other) const
{
  return CollisionFunctions::CircleBoxCollisionCheck(*this, other);
}
