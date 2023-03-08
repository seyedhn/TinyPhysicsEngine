#include "Application.h"
#include "Source/Colliders/Shape.h"
#include "Source/Colliders/Circle.h"


Environment2D::Environment2D(int num)
	: width(1920.f)
	, height(1080.f)
	, dt(0.167)
	, NumberOfParticles(num)
	, framerate(60)
	, window(sf::VideoMode(int(width), int(height)), "Collision Test")
{
	_collisionManager = new PhysicsWorld(width, height);
	window.setFramerateLimit(framerate);

	for (int i = 0; i < NumberOfParticles; i++)
	{
		float radius = 5.f;
		actors.push_back(new Circle(radius, Vector2f(int(5*radius), int(width - 5*radius), int(5*radius), int(height - 5*radius)), Vector2f(-200, 200, -50, 50)));
	}

	actors.push_back(new AABB(0.f,0.f,width,5.f));
	actors.push_back(new AABB(0.f, height-5, width, height));
	actors.push_back(new AABB(0.f, 0.f, 5.f, height));
	actors.push_back(new AABB(width-5.f, 0.f, width, height));
}



void Environment2D::DisplayWindow()
{
	sf::Clock frameTimer;

	while (window.isOpen())
	{
		Timer(frameTimer);
		_collisionManager->Tick(actors, dt);
		EventTick();
		RenderTick();
	}
}



void Environment2D::Timer(sf::Clock& frameTimer)
{
	dt = frameTimer.getElapsedTime().asSeconds();

	float currentTime = frameTimer.restart().asSeconds();
	float fps = 1.f / currentTime;
	//std::cout << fps << std::endl; //UNCOMMENT TO SEE FPS

	frameTimer.restart();
}

void Environment2D::EventTick()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Environment2D::RenderTick()
{
	window.clear(sf::Color(0, 0, 0));

	for (Shape* i : actors)
	{
		i->UpdateRenderPosition(i->GetPos());
		i->DrawToWindow(window);
	}
	window.display();
}






