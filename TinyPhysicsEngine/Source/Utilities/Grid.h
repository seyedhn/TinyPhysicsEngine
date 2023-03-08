#pragma once
#include "Vector2d.h"
#include "LinkedList.h"

class Shape;
class Circle;

class Grid
{
public:
  Grid();
  Grid(Vector2f minBound, Vector2f maxBound);
  void UpdateGrid();                           //ADD DEF
  void InsertCollider(const Shape& collider);  //ADD DEF
  void RemoveCollider();                       //ADD DEF
  void GetList();                              //ADD DEF
  bool ContainsColliderAABB(const Shape& collider) const;

  List<Circle> list;

private:
  Vector2f min_bound;
  Vector2f max_bound;

};

