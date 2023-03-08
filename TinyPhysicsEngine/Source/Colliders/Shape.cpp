#include "Shape.h"


void Shape::setVel(const Vector2f& new_vel)
{
  v = new_vel;
}

void Shape::setVel(float _x, float _y)
{
  v.setX(_x);
  v.setY(_y);
}

void Shape::setPos(const Vector2f& new_pos)
{
  r = new_pos;
}

void Shape::setPosX(float _x)
{
  r.setX(_x);
}

void Shape::setPosY(float _y)
{
  r.setY(_y);
}

void Shape::addVel(const Vector2f& delta_v)
{
  v = v + delta_v;
}

Vector2f Shape::GetPos() const
{
  return r;
}

Vector2f Shape::GetVel() const
{
  return v;
}

float Shape::GetMass() const
{
  return m;
}

bool Shape::GetSimulatePhysics() const
{
    return SimulatePhysics;
}

void Shape::UpdateKinematics(float dt)
{
  //VerletIntegration(dt);
  ExplicitEuler(dt);
}

void Shape::VerletIntegration(float dt)
{
  Vector2f r2 = 2 * r - r0 + (1 / m) * F * dt * dt;
  r0 = r;
  r = r2;
}

void Shape::ExplicitEuler(float dt)
{
  r = r + v * dt;
}
