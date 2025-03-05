#include<iostream>

#include"Object.h"

Object::Object() {
	this->window = nullptr;
	this->renderObject = nullptr;

	this->density = 0.2f;
	this->friction = 0.2f;
	this->restitution = 0.05f;

	this->attached_body = 0;
}

Object::~Object() {
	delete this->renderObject;
}

void Object::initRenderObject(sf::RenderWindow* window, std::map<const char*, sf::Texture*> textures) {
	this->window = window;

	this->renderObject = new RenderObject(this->window, *textures[imageName]);
}

void Object::initBody(b2WorldId worldId) {
	this->bodyDef = b2DefaultBodyDef();
	this->bodyDef.type = b2_dynamicBody;

	bodyId = b2CreateBody(worldId, &bodyDef);

	this->dynamicBox = b2MakeBox(this->rect.getSize().x/2.0f, this->rect.getSize().y / 2.0f);

	this->shapeDef = b2DefaultShapeDef();

	shapeDef.density = this->density;
	shapeDef.friction = this->friction;
	shapeDef.restitution = this->restitution;

	shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &dynamicBox);
}

sf::Vector2f Object::getInitialPosition() const {
	return this->initialPosition;
}

void Object::setPosition(sf::Vector2f position) {
	this->initialPosition = position;

	b2Vec2 pos = { position.x, position.y };
	
	b2Body_SetTransform(this->bodyId, pos, {1.0f, 0.0f});

	this->renderObject->sprite.setPosition(sf::Vector2f(position.x,
		-position.y));
}

void Object::render() {
	this->window->draw(this->renderObject->sprite);
}

void Object::update() {
	//this->setPosition(sf::Vector2f(this->getPosition().x + 0.3f, this->getPosition().y));
	b2Vec2 bodyPosition = b2Body_GetPosition(this->bodyId);
	b2Rot r = b2Body_GetRotation(this->bodyId);

	this->renderObject->sprite.setOrigin(this->rect.getOrigin());

	this->renderObject->sprite.setRotation(57.2958f * -b2Rot_GetAngle(r));
	this->renderObject->sprite.setPosition(sf::Vector2f(bodyPosition.x + 16, 
													   -bodyPosition.y + 16));

	//std::cout << bodyPosition.x << ',' << bodyPosition.y << '\n';
}



Object1x1::Object1x1() {
	this->rect.setSize(sf::Vector2f(32.0f, 32.0f));
	this->rect.setOrigin(sf::Vector2f(16.0f, 16.0f));

	this->imageName = "block_1x1";
}



ObjectCab::ObjectCab() {
	this->rect.setSize(sf::Vector2f(32.0f, 32.0f));
	this->rect.setOrigin(sf::Vector2f(16.0f, 16.0f));

	this->density = 0.7f;

	this->imageName = "cab";
}



ObjectWheel::ObjectWheel() {
	this->rect.setSize(sf::Vector2f(32.0f, 32.0f));
	this->rect.setOrigin(sf::Vector2f(16.0f, 16.0f));

	this->density = 3.0f;
	this->restitution = 0.6f;
	this->friction = 1.0f;

	this->wheelSpeed = 5.0f;
	this->radius = 32.0f;
	this->stiffness = 25.0f;

	this->imageName = "wheelbase";
	this->wheelImageName = "wheel";

	this->wheelSpriteOrigin = sf::Vector2f(32.0f, 32.0f);
}

void ObjectWheel::updateWheel() {
	//this->setPosition(sf::Vector2f(this->getPosition().x + 0.3f, this->getPosition().y));
	b2Vec2 bodyPosition = b2Body_GetPosition(this->wheelBodyId);
	b2Rot r = b2Body_GetRotation(this->wheelBodyId);

	this->wheelRenderObject->sprite.setRotation(57.2958f * -b2Rot_GetAngle(r));
	this->wheelRenderObject->sprite.setPosition(sf::Vector2f(bodyPosition.x + 16,
		-bodyPosition.y + 16));

	//std::cout << bodyPosition.x << ',' << bodyPosition.y << '\n';
}


void ObjectWheel::initBody(b2WorldId worldId) {
	this->bodyDef = b2DefaultBodyDef();
	this->bodyDef.type = b2_dynamicBody;
	this->bodyId = b2CreateBody(worldId, &bodyDef);

	this->shapeDef = b2DefaultShapeDef();
	this->shapeDef.filter.categoryBits = 0x0001;
	this->shapeDef.filter.maskBits = 0x0001;

	shapeDef.density = 0.2f;
	shapeDef.friction = 0.2f;
	shapeDef.restitution = 0.2f;

	b2Polygon box = b2MakeBox(16.0f, 16.0f);
	shapeId = b2CreatePolygonShape(bodyId, &shapeDef, &box);

	this->wheelBodyDef = b2DefaultBodyDef();
	this->wheelBodyDef.type = b2_dynamicBody;
	this->wheelBodyDef.angularDamping = 10.0f;

	this->wheelBodyId = b2CreateBody(worldId, &this->wheelBodyDef);

	this->wheelShapeDef = b2DefaultShapeDef();
	this->wheelShapeDef.density = this->density;
	this->wheelShapeDef.friction = this->friction;
	this->wheelShapeDef.restitution = this->restitution;
	
	b2Circle circle = b2Circle();
	circle.radius = this->radius;

	wheelShapeId = b2CreateCircleShape(this->wheelBodyId, &this->wheelShapeDef, &circle);
}

void ObjectWheel::makeJoint(b2WorldId worldId){

	b2WheelJointDef wheelJoint = b2DefaultWheelJointDef();
	wheelJoint.bodyIdA = this->bodyId;
	wheelJoint.bodyIdB = this->wheelBodyId;
	wheelJoint.collideConnected = false;
	wheelJoint.hertz = this->stiffness;

	this->wheelJointId = b2CreateWheelJoint(worldId, &wheelJoint);
}

void ObjectWheel::setPosition(sf::Vector2f position) {
	this->initialPosition = position;

	b2Vec2 pos = { position.x, position.y };

	b2Body_SetTransform(this->bodyId, pos, { 1.0f, 0.0f });
	b2Body_SetTransform(this->wheelBodyId, pos, { 1.0f, 0.0f });

	this->renderObject->sprite.setPosition(sf::Vector2f(position.x,
		-position.y));

	this->wheelRenderObject->sprite.setPosition(sf::Vector2f(position.x + 16,
		-position.y + 16));
}

void ObjectWheel::initRenderObject(sf::RenderWindow* window, std::map<const char*, sf::Texture*> textures) {
	this->window = window;

	this->renderObject = new RenderObject(this->window, *textures[imageName]);
	this->wheelRenderObject = new RenderObject(this->window, *textures[wheelImageName]);

	this->wheelRenderObject->sprite.setOrigin(this->wheelSpriteOrigin);
}

void ObjectWheel::render() {
	this->window->draw(this->wheelRenderObject->sprite);
}

ObjectWheelArmoured::ObjectWheelArmoured() {
	this->wheelSpeed = 7.0f;
	this->radius = 32.0f;
	this->stiffness = 30.0f;

	this->imageName = "wheelbase";
	this->wheelImageName = "wheelarmour";
}

ObjectWheelSmall::ObjectWheelSmall() {
	this->wheelSpeed = 14.0f;
	this->radius = 25.0f;
	this->friction = 3.0f;
	this->stiffness = 20.0f;
	this->density = 1.0f;

	this->imageName = "wheelbase";
	this->wheelImageName = "wheelsmall";

	this->wheelSpriteOrigin = sf::Vector2f(25.0f, 25.0f);
}
