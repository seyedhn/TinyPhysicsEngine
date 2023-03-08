#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <vector>
#include <iostream>
#include "Source/Colliders/Shape.h"
#include "Source/Engine/PhysicsWorld.h"


class Environment2D
{
public:

  Environment2D(int number_of_shapes);

  void DisplayWindow();
  void RenderTick();
  void EventTick();
  void Timer(sf::Clock& clock);

private:

  float width;
  float height;
  int framerate;
  float dt;
  int NumberOfParticles;

  std::vector<Shape*> actors;
  sf::RenderWindow window;
  PhysicsWorld* _collisionManager;
};

