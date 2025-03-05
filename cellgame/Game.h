
#include"Object.h"
#include "SFML/Graphics.hpp"
#include"RenderObject.h"
#include"settings.h"
#include<iostream>
#include"box2d/box2d.h"

class Game {
private:
	sf::VideoMode videoMode;

	std::vector<Object*> Objects;
	std::vector<ObjectWheel*> ObjectWheels;

	RenderObject* mouse_pointer;

	sf::Clock clock;

	float prevTime;
	float currentTime;
	float dt;

	RenderObject* groundRender;

	bool run_simulation;
	int scene;

public:

	Game();

	sf::RenderWindow* window;
	std::map<const char*, sf::Texture*> textures;

	unsigned int render_object_id;

	int renderObjectCount;
	int framerate;

	bool running = true;

	b2WorldDef worldDef;
	b2WorldId worldId;

	void initDisplay();
	void initVariables();
	void loadTextures();

	sf::Texture* loadTexture(const char* filename);

	void pollEvents();
	void update();
	void render();
	void clear();

	//int getRenderObjectIndex(RenderObject& r);
};
