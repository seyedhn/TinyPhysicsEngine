#pragma once
#include "Source/Colliders/Shape.h"
#include "Source/Colliders/Circle.h"
#include "Source/Colliders/AABB.h"
#include "Source/Utilities/LinkedList.h"
#include "Source/Utilities/Grid.h"

class PhysicsWorld
{
public:
  PhysicsWorld(float world_width, float world_height);

  void Tick(std::vector<Shape*> actors, float dt);
  void UpdatePositions(std::vector<Shape*> actors, float dt) const;

  void ApplyGravity(Shape* actor, float dt) const;
  void ApplyPeriodicBC(Shape* actor) const;

  void BroadPhase_BruteForce(const std::vector<Shape*>& objects);
  void BroadPhase_BruteForce_MULTITHREAD(const std::vector<Shape*>& objects, int num_threads);

  void CircleCircleCollisionUpdate(Shape* circ_A, Shape* circ_B);
  void CircleAABBCollisionUpdate(Shape* circ, Shape* box);

  void BuildGrids(int n, int height, int width, std::vector<Shape*>& objects);


private:
  float WorldWidth;
  float WorldHeight;
  static constexpr float epsilon = 1;
  Grid gridslist[2];
};

