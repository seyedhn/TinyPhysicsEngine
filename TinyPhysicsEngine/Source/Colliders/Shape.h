#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include "Source/Utilities/Vector2d.h"

class Circle;
class AABB;

class Shape
{
public:
  
  void setVel(const Vector2f& velocity);
  void setVel(float _x, float _y);
  void setPos(const Vector2f& position);
  void setPosX(float _x);
  void setPosY(float _y);

  void addVel(const Vector2f& delta_v);

  Vector2f GetPos() const;
  Vector2f GetVel() const;
  float GetMass() const;
  bool GetSimulatePhysics() const;


  virtual void UpdateRenderPosition(const Vector2f& position) = 0;
  virtual void DrawToWindow(sf::RenderWindow& window) const = 0;
  virtual void ChangeColour(const sf::Color& colour) = 0;
 
  virtual AABB GetAABB() const = 0;
  virtual void OnCollision(const Shape& other) = 0;

  virtual bool IsColliding(const Shape& other) const = 0;
  virtual bool IsCollidingWithCircle(const Circle& other) const = 0;
  virtual bool IsCollidingWithBox(const AABB& other) const = 0;
  template <typename T> bool IsType() const
  { return (typeid(*this).hash_code() == typeid(T).hash_code()); }

  virtual void VerletIntegration(float dt);
  virtual void ExplicitEuler(float dt);
  virtual void UpdateKinematics(float dt);

protected:
  Vector2f r0;
  Vector2f r;
  Vector2f v;
  Vector2f F;
  float m;
  bool SimulatePhysics;
  sf::Color colour;

};

