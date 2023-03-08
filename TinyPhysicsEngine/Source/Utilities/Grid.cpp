#include "Source/Utilities/Grid.h"
#include "Source/Colliders/Box.h"

Grid::Grid() : min_bound(0.f, 0.f), max_bound(0.f, 0.f) {}

Grid::Grid(Vector2f minBound, Vector2f maxBound) : min_bound(minBound), max_bound(maxBound) {}

bool Grid::ContainsColliderAABB(const Shape& collider) const
{
  AABB AABB = collider.GetAABB();

  if (AABB.min_x > max_bound.x || AABB.max_x < min_bound.x || AABB.min_y > max_bound.y || AABB.max_y < min_bound.y)
  {
    return true;
  }
  return false;
}
