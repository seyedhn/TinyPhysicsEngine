#include <thread>
#include "PhysicsWorld.h"
#include "CollisionFunctions.h"



PhysicsWorld::PhysicsWorld(float width, float height) : WorldWidth(width), WorldHeight(height) {}

void PhysicsWorld::Tick(std::vector<Shape*> actors, float dt)
{
  //BroadPhase_BruteForce(actors);
  BroadPhase_BruteForce_MULTITHREAD(actors, 6);
  UpdatePositions(actors, dt);
}

void PhysicsWorld::UpdatePositions(std::vector<Shape*> actors, float dt) const
{
  for (Shape* i : actors)
  {
    //ApplyGravity(i, dt);
    //ApplyPeriodicBC(i);
    i->UpdateKinematics(dt);
  }
}

void PhysicsWorld::ApplyGravity(Shape* actor, float dt) const
{
  if(actor->GetSimulatePhysics())
  {
  Vector2f gravity(0.f, 10.f * 9.81f * dt);
  actor->addVel(gravity);
  }
}

void PhysicsWorld::ApplyPeriodicBC(Shape* i) const
{
  if (i->GetPos().y > WorldHeight) {  i->setPosY(0); }
  else if (i->GetPos().y < 0)      {  i->setPosY(float(WorldHeight)); }
  if (i->GetPos().x > WorldWidth)  { i->setPosX(0); }
  else if (i->GetPos().x < 0)      {  i->setPosX(float(WorldWidth)); }
}

void PhysicsWorld::BroadPhase_BruteForce(const std::vector<Shape*>& objects)
{
  int size = int(objects.size());
  CollisionFunctions::CheckPairwiseCollisions(*this, objects, 0, size-1);
}

void BroadPhase_BruteForce_TwoSided(PhysicsWorld& colman, const std::vector<Shape*>& objects, int begin, int end)
{
  int size = int(objects.size());
  CollisionFunctions::CheckPairwiseCollisions(colman, objects, begin, end);
  CollisionFunctions::CheckPairwiseCollisions(colman, objects, size - end, size - begin);
}

void PhysicsWorld::BroadPhase_BruteForce_MULTITHREAD(const std::vector<Shape*>& objects, int N)
{
  std::vector<std::thread> threads;
  int size = int(objects.size());
  int a = size / N;

  for (int i = 0; i < N; i++)
    threads.push_back(std::thread(BroadPhase_BruteForce_TwoSided, std::ref(*this), std::ref(objects), a * i / 2, a * (i + 1) / 2));

  for (std::thread& t : threads)
    t.join();

}

void PhysicsWorld::CircleCircleCollisionUpdate(Shape* shape_A, Shape* shape_B)
{
  Circle* circ_A = static_cast<Circle*>(shape_A);
  Circle* circ_B = static_cast<Circle*>(shape_B);  
  Vector2f p = CollisionFunctions::CircleCircleImpulse(*circ_A, *circ_B, epsilon);
  Vector2f delta_v = (-1 / circ_A->GetMass()) * p;
  Vector2f n_delta_v = (1 / circ_B->GetMass()) * p;

  circ_A->addVel(n_delta_v);
  circ_B->addVel(delta_v);
}

void PhysicsWorld::CircleAABBCollisionUpdate(Shape* _circ, Shape* _box)
{
  Circle* circ = static_cast<Circle*>(_circ);
  AABB* box = static_cast<AABB*>(_box);
  Vector2f p = CollisionFunctions::CircleAABBImpulse(*circ, *box, epsilon);
  Vector2f delta_v = (1 / circ->GetMass()) * p;

  circ->addVel(delta_v);
  //ADD CODE FOR AABB VELOCITY CHANGE

}

void PhysicsWorld::BuildGrids(int n, int height, int width, std::vector<Shape*>& objects)
{
  gridslist[0] = Grid(Vector2f(0.f, 0.f), Vector2f(width/2.f, float(height)));
  gridslist[1] = Grid(Vector2f(width/2.f, 0.f), Vector2f(float(width), float(height)));

  int size = int(objects.size());

  for (int i = 0; i < size - 1; i++)
  {
    for (Grid& g : gridslist)
    {
      if (g.ContainsColliderAABB(*objects[i]))
      {
        //THIS SHOULD BE CHANGED SO IT CAN TAKE ANY SHAPE NOT JUST CIRCLES
        Circle* circ_A = static_cast<Circle*>(objects[i]); 
        g.list.AddNode(*circ_A);
      }
    }
  }

}




