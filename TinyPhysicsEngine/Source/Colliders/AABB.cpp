#include "AABB.h"
#include "Source/Engine/CollisionFunctions.h"


AABB::AABB(float minx, float miny, float maxx, float maxy)
  : min_x(minx), min_y(miny), max_x(maxx), max_y(maxy), RenderBoxShape(sf::Vector2f(maxx-minx, maxy-miny))
{
  RenderBoxShape.setFillColor(sf::Color::Blue);
  length = maxx - minx;
  height = maxy - miny;
  r.x = minx;
  r.y = miny;
  m = 1;
  SimulatePhysics = false;
}

void AABB::UpdateRenderPosition(const Vector2f& new_pos)
{
  RenderBoxShape.setPosition(r.x, r.y);
}

void AABB::DrawToWindow(sf::RenderWindow& window) const
{
  window.draw(RenderBoxShape);
}

void AABB::ChangeColour(const sf::Color& colour)
{
  RenderBoxShape.setFillColor(colour);
}

const float AABB::GetLength() const
{
  return length;
}

const float AABB::GetHeight() const
{
  return height;
}

AABB AABB::GetAABB() const
{
  return *this;
}

void AABB::OnCollision(const Shape& other)
{
  //ADD CODE HERE
}

bool AABB::IsColliding(const Shape& other) const
{
  return other.IsCollidingWithBox(*this);
}

bool AABB::IsCollidingWithBox(const AABB& other) const
{
  return CollisionFunctions::BoxBoxCollisionCheck(*this, other);
}

bool AABB::IsCollidingWithCircle(const Circle& other) const
{
  return CollisionFunctions::CircleBoxCollisionCheck(other, *this);
}

