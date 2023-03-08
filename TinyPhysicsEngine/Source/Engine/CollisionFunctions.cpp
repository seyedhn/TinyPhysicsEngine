#include "CollisionFunctions.h"
#include <iostream>


void CollisionFunctions::CheckPairwiseCollisions(PhysicsWorld& ColMan, const std::vector<Shape*>& objects, int begin, int end)
{
  int size = int(objects.size());

  for (int i = begin; i < end; i++)
  {
    for (int j = i + 1; j < size; j++)
    {
      if (objects[i]->IsColliding(*objects[j]))
      {
        objects[i]->OnCollision(*objects[j]);
        objects[j]->OnCollision(*objects[i]);

        //CHANGE THIS TO A HASH MAP SEARCH
        if (objects[i]->IsType<Circle>() && objects[j]->IsType<Circle>())
          ColMan.CircleCircleCollisionUpdate(objects[i], objects[j]);
        if (objects[i]->IsType<Circle>() && objects[j]->IsType<AABB>())
          ColMan.CircleAABBCollisionUpdate(objects[i], objects[j]);
        if (objects[i]->IsType<AABB>() && objects[j]->IsType<Circle>())
          ColMan.CircleAABBCollisionUpdate(objects[j], objects[i]);
      }
    }
  }
}

bool CollisionFunctions::CircleCircleCollisionCheck(const Circle& circ_A, const Circle& circ_B)
{
  float rA = circ_A.GetRadius();
  float rB = circ_B.GetRadius();
  Vector2f v = circ_A.GetPos() - circ_B.GetPos();
  return (v.x * v.x + v.y * v.y < (rA + rB) * (rA + rB));
}

bool CollisionFunctions::CircleBoxCollisionCheck(const Circle& circ, const AABB& box)
{
  //INACCURATE - ONLY CHECKS ON CIRCLE'S OUTER AABB. MISSES ON CORNER CASES. EXPAND CODE.
  return(BoxBoxCollisionCheck(circ.GetAABB(), box));
}

bool CollisionFunctions::BoxBoxCollisionCheck(const AABB& box_A, const AABB& box_B)
{
  return(!(box_A.min_x > box_B.max_x || box_A.max_x < box_B.min_x || box_A.min_y > box_B.max_y || box_A.max_y < box_B.min_y));
}

Vector2f CollisionFunctions::CircleCircleImpactNormal(const Circle& circ_A, const Circle& circ_B)
{
  Vector2f n = circ_A.GetPos() - circ_B.GetPos();
  n.Normalise();
  return n;
}

Vector2f CollisionFunctions::CircleAABBImpactNormal(const Circle& circ, const AABB& box)
{
  Vector2f p = circ.GetPos();

  if (p.x > box.max_x) { return Vector2f(-1.f, 0.f); }
  if (p.x < box.min_x) { return Vector2f(1.f, 0.f);  }
  if (p.y > box.max_y) { return Vector2f(0.f, -1.f); }
  if (p.y < box.min_y) { return Vector2f(0.f, 1.f);  }

  //THROW EXCEPTION HERE
  return Vector2f(0.f, 0.f); 
}

Vector2f CollisionFunctions::CircleCircleImpulse(const Circle& circ_A, const Circle& circ_B, float epsilon)
{
  Vector2f n = CircleCircleImpactNormal(circ_A, circ_B);
  return (epsilon + 1) / (1 / circ_A.GetMass() + 1 / circ_B.GetMass()) * (circ_B.GetVel() * n - circ_A.GetVel() * n) * n;
}

Vector2f CollisionFunctions::CircleAABBImpulse(const Circle& circ, const AABB& box, float epsilon)
{
  Vector2f n = CircleAABBImpactNormal(circ, box);
     
  if (!box.GetSimulatePhysics())  {  return -1 * (epsilon + 1) * circ.GetMass() * (circ.GetVel() * n) * n; }
  if (box.GetSimulatePhysics()) {  /*ADD CODE HERE*/ }
}
 