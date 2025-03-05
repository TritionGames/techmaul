#ifndef OBJECT_H
#define OBJECT_H

#include "RenderObject.h"
#include"SFML/Graphics.hpp"
#include"box2d/box2d.h"


class Object {
private:
	sf::Vector2f _position;
	sf::Vector2f initialPosition;

public:
	Object();
	~Object();

	const char* imageName;

	sf::RenderWindow* window;
	RenderObject* renderObject;

	b2BodyDef bodyDef;
	b2BodyId bodyId;
	b2Polygon dynamicBox;
	b2ShapeDef shapeDef;
	b2ShapeId shapeId;
	b2JointId jointId;

	sf::RectangleShape rect;
	sf::Vector2f wheelSpriteOrigin;

	int attached_body;

	float restitution;
	float friction;
	float density;
	bool isWheel;

	unsigned int type;

	bool jointed;

	void render();
	void update();

	void initBody(b2WorldId worldId);

	sf::Vector2f getInitialPosition() const;
	void setPosition(sf::Vector2f position);

	void initRenderObject(sf::RenderWindow* window, std::map<const char*, sf::Texture*> textures);
};

class Object1x1 : public Object {
public:
	 Object1x1();
};

class ObjectCab : public Object {
public:
	ObjectCab();
};

class ObjectWheel : public Object {
private:
	sf::Vector2f initialPosition;

public:
	ObjectWheel();

	const char* wheelImageName;
	float wheelSpeed;
	b2JointId wheelJointId;

	RenderObject* wheelRenderObject;

	b2BodyDef wheelBodyDef;
	b2BodyId wheelBodyId;
	b2ShapeDef wheelShapeDef;
	b2ShapeId wheelShapeId;

	float radius;
	float stiffness;

	void updateWheel();
	void render();
	void setPosition(sf::Vector2f position);
	void initRenderObject(sf::RenderWindow* window, std::map<const char*, sf::Texture*> textures);
	void initBody(b2WorldId worldId);
	void makeJoint(b2WorldId worldId);
};

class ObjectWheelArmoured : public ObjectWheel {
public:
	ObjectWheelArmoured();
};

class ObjectWheelSmall : public ObjectWheel {
public:
	ObjectWheelSmall();
};

#endif