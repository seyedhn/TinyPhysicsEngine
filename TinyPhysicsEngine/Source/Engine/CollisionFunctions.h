#pragma once
#include "Source/Colliders/Circle.h"
#include "Source/Colliders/AABB.h"
#include "PhysicsWorld.h"

namespace CollisionFunctions
{

  void CheckPairwiseCollisions(PhysicsWorld& ColMan, const std::vector<Shape*>& objects, int begin, int end);

  bool CircleCircleCollisionCheck(const Circle& circ_A, const Circle& circ_B);
  bool CircleBoxCollisionCheck(const Circle& circ, const AABB& box);
  bool BoxBoxCollisionCheck(const AABB& box_A, const AABB& box_B);

  Vector2f CircleCircleImpactNormal(const Circle& circ_A, const Circle& circ_B);
  Vector2f CircleAABBImpactNormal(const Circle& circ, const AABB& box);
 
  Vector2f CircleCircleImpulse(const Circle& circ_A, const Circle& circ_B, float epsilon);
  Vector2f CircleAABBImpulse(const Circle& circ, const AABB& box, float epsilon);

}