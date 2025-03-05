#include<iostream>
#include<assert.h>

#include "Game.h"
#include "box2d/box2d.h"
#include "Object.h"

Game::Game() {
    this->window = nullptr;
    this->mouse_pointer = nullptr;
    this->run_simulation = false;
    this->scene = 0;
    initVariables();
    loadTextures();
    initDisplay();
}

void Game::update() {
    this->prevTime = currentTime;
    this->currentTime = clock.getElapsedTime().asSeconds();

    this->dt = (this->currentTime - this->prevTime);

    if (this->run_simulation) {
        b2World_Step(this->worldId, std::min(this->dt, 0.1f), 4);
        b2World_Step(this->worldId, std::min(this->dt, 0.1f), 4);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        for (ObjectWheel* wheel : ObjectWheels) {
            b2Body_SetAngularVelocity(wheel->wheelBodyId, wheel->wheelSpeed);
        }
    }

    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        for (ObjectWheel* wheel : ObjectWheels) {
            b2Body_SetAngularVelocity(wheel->wheelBodyId, -wheel->wheelSpeed);
        }
    }


    pollEvents();
}

void Game::render() {
    this->window->clear(sf::Color(40, 204, 223));

    //rendering goes here

    groundRender->sprite.setPosition(sf::Vector2f(0, 800));
    groundRender->render();
    groundRender->sprite.setPosition(sf::Vector2f(1280, 800));
    groundRender->render();

    for (Object* r : this->Objects) {
        if (this->run_simulation) { r->update(); }
        r->render();
    }

    for (ObjectWheel* r : this->ObjectWheels) {
        if (this->run_simulation) { r->updateWheel(); }
        r->render();
    }

    mouse_pointer->sprite.setPosition(sf::Vector2f(sf::Mouse::getPosition(*window)));
    mouse_pointer->render();

    this->window->display();
}

void Game::clear() {
    b2DestroyWorld(worldId);

    delete this->window;
    delete this->mouse_pointer;
}

void Game::initVariables() {
    this->videoMode.width = 1920;
    this->videoMode.height = 1080;
    this->running = true;

    this->Objects.reserve(MAX_OBJECT_COUNT);
    this->framerate = 280;

    this->worldDef = b2DefaultWorldDef();
    this->worldId = b2CreateWorld(&this->worldDef);

    b2Vec2 gravity = { 0.0f, -200.0f };
    b2World_SetGravity(this->worldId, gravity);

    b2BodyDef groundBodyDef = b2DefaultBodyDef();
    b2Vec2 position = {0.0f, -800 - 100.0f + 16.0f};
    groundBodyDef.position = position;

    b2BodyId groundId = b2CreateBody(worldId, &groundBodyDef);
    b2Polygon groundBox = b2MakeBox(2000, 100.0f);

    b2ShapeDef groundShapeDef = b2DefaultShapeDef();
    groundShapeDef.filter.categoryBits = 0x0003;
    groundShapeDef.friction = 2.0f;
   
    b2CreatePolygonShape(groundId, &groundShapeDef, &groundBox);
}

void Game::initDisplay() {
    this->window = new sf::RenderWindow(this->videoMode, "Game", sf::Style::Titlebar | sf::Style::Close);
    this->window->setMouseCursorVisible(false);
    this->window->setFramerateLimit(this->framerate);
    this->window->setVerticalSyncEnabled(true);

    this->mouse_pointer = new RenderObject(this->window, *loadTexture("assets/images/pointer.png"), sf::Vector2f(0, 0));
    this->groundRender = new RenderObject(this->window, *this->textures["ground"], sf::Vector2f(0, 800));
}

void Game::pollEvents() {
    sf::Event event;

    this->window->pollEvent(event);

    if (event.type == sf::Event::Closed) {
        this->running = false;
    }

    if (event.type == sf::Event::KeyPressed) {
        sf::Vector2f pos = sf::Vector2f(sf::Mouse::getPosition(*window));
        pos.y *= -1;

        pos.x = int(pos.x / 32) * 32;
        pos.y = int(pos.y / 32) * 32;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {

            Object1x1* x = new Object1x1();
            x->initRenderObject(this->window, this->textures);
            x->initBody(worldId);
            x->setPosition(pos);

            Objects.push_back(x);
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {

            ObjectCab* x = new ObjectCab();
            x->initRenderObject(this->window, this->textures);
            x->initBody(worldId);
            x->setPosition(pos);

            Objects.push_back(x);
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {

            ObjectWheelArmoured* x = new ObjectWheelArmoured();
            x->initRenderObject(this->window, this->textures);
            x->initBody(worldId);
            x->setPosition(pos);

            Objects.push_back(x);
            ObjectWheels.push_back(x);
        }

        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {

            ObjectWheelSmall* x = new ObjectWheelSmall();
            x->initRenderObject(this->window, this->textures);
            x->initBody(worldId);
            x->setPosition(pos);

            Objects.push_back(x);
            ObjectWheels.push_back(x);
        }


        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
            if (!(this->run_simulation)) {
                /*
                b2Vec2 cabPosition;
                b2BodyId cabId;
                bool hasCab = false;

                for (auto& r : Objects) {
                    if (r->type == 1) {
                        cabPosition = b2Body_GetPosition(r->bodyId);
                        cabId = r->bodyId;
                        hasCab = true;
                        break;
                    }
                }

                if (hasCab) {
                    for (auto& r : Objects) {
                        b2WeldJointDef jointDef = b2DefaultWeldJointDef();
                        b2Vec2 objPos = b2Body_GetPosition(r->bodyId);

                        jointDef.bodyIdA = cabId;
                        jointDef.bodyIdB = r->bodyId;
                        jointDef.localAnchorB = { cabPosition.x - objPos.x, cabPosition.y - objPos.y};

                        b2CreateWeldJoint(this->worldId, &jointDef);
                    }
                }

                */
                for (auto* r : Objects) {
                    for (auto* r2 : Objects) {
                        if (r == r2) {
                            continue;
                        }


                        b2WeldJointDef jointDef = b2DefaultWeldJointDef();
                        b2Vec2 objPos = b2Body_GetPosition(r->bodyId);
                        b2Vec2 originPos = b2Body_GetPosition(r2->bodyId);

                        jointDef.bodyIdA = r2->bodyId;
                        jointDef.bodyIdB = r->bodyId;
                        jointDef.localAnchorB = { originPos.x - objPos.x, originPos.y - objPos.y };

                        r->jointId = b2CreateWeldJoint(this->worldId, &jointDef);
                        r->attached_body = 1;

                        b2Filter filter;

                        filter.categoryBits = 0x0002;
                        filter.maskBits = 0x0002 | 0x0003;

                        b2Shape_SetFilter(r->shapeId, filter);
                    }
                }

                for (ObjectWheel* r : ObjectWheels) {
                    r->makeJoint(worldId);

                    b2Filter filter;

                    filter.categoryBits = 0x0001;
                    filter.maskBits = 0x0001;

                    b2Shape_SetFilter(r->wheelShapeId, filter);
                }
            }
            else {
                for (Object* r : Objects) {
                    //std::cout << r->getInitialPosition().x << ';' << r->getInitialPosition().y << '\n';
                    r->setPosition(r->getInitialPosition());
                    b2DestroyJoint(r->jointId);
                    r->renderObject->sprite.setRotation(0.0f);
                }

                for (ObjectWheel* r : ObjectWheels) {
                    //std::cout << r->getInitialPosition().x << ';' << r->getInitialPosition().y << '\n';
                    b2DestroyJoint(r->wheelJointId);
                }
            }
            this->run_simulation = !this->run_simulation;
        }
    }
}

void Game::loadTextures() {
    this->textures.emplace("block_1x1", loadTexture("assets/images/block_1x1.png"));
    this->textures.emplace("block_2x1", loadTexture("assets/images/block_2x1.png"));
    this->textures.emplace("cab", loadTexture("assets/images/cab.png"));
    this->textures.emplace("ground", loadTexture("assets/images/ground.png"));
    this->textures.emplace("wheel", loadTexture("assets/images/wheel.png"));
    this->textures.emplace("wheelbase", loadTexture("assets/images/wheelbase.png"));
    this->textures.emplace("wheelarmour", loadTexture("assets/images/wheelarmour.png"));
    this->textures.emplace("wheelsmall", loadTexture("assets/images/wheelsmall.png"));
}

sf::Texture* Game::loadTexture(const char* filename) 
{
    sf::Texture* tex = (new sf::Texture);
    tex->loadFromFile(filename);

    return tex;
}
