////////////////////////////////////////////////////////////////////////////////
// Galaxian clone
//
// Copyright (c) 2022 Kwena Mashamaite (kwena.mashamaite1@gmail.com)
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
////////////////////////////////////////////////////////////////////////////////

#include "GameplayScene.h"
#include "PauseMenuScene.h"
#include "ScrollingBackgroundScene.h"
#include "gui/GameplayGui.h"
#include "actors/Galaxyip.h"
#include "actors/CollisionFiltering.h"
#include <IME/core/engine/Engine.h>
#include <IME/ui/widgets/Label.h>
#include <IME/core/physics/rigid_body/PhysicsEngine.h>
#include <IME/core/physics/rigid_body/colliders/BoxCollider.h>

///////////////////////////////////////////////////////////////
GameplayScene::GameplayScene() {
    m_view = std::make_unique<gui::GameplayGui>();
}

///////////////////////////////////////////////////////////////
void GameplayScene::onEnter() {
    setCached(true, "GameplayScene");
    setVisibleOnPause(true);
    setBackgroundScene(std::make_unique<ScrollingBackgroundScene>());
    initGui();
    registerEventHandlers();
    initPhysicsEngine();
    addWindowBorders();
    createPlayerShip();

    // Instantiate pause menu once
    if (!getEngine().isSceneCached("PauseMenuScene"))
        getEngine().cacheScene("PauseMenuScene", std::make_unique<PauseMenuScene>());
}

///////////////////////////////////////////////////////////////
void GameplayScene::initGui() {
    getGui().getWidget<ime::ui::Label>("lblHighScoreVal")->setText(
        std::to_string(getCache().getValue<int>("HIGH_SCORE")));

    // Toggle one up label every interval
    getTimer().setInterval(ime::milliseconds(200), [this] {
        getGui().getWidget("lblOneUp")->toggleVisibility();
    });
}

///////////////////////////////////////////////////////////////
void GameplayScene::registerEventHandlers() {
    auto pauseGame = [this] { getEngine().pushCachedScene("PauseMenuScene"); };

    int handler = getWindow().onClose(pauseGame);
    onDestruction([handler, this] { getWindow().removeEventListener(handler); });

    getInput().bindKey(ime::Keyboard::Key::P, ime::input::KeyBindType::KeyUp, pauseGame);
    getInput().bindKey(ime::Keyboard::Key::Escape, ime::input::KeyBindType::KeyUp, pauseGame);
}

///////////////////////////////////////////////////////////////
void GameplayScene::initPhysicsEngine() {
    const ime::Vector2f gravity = {0, 0};
    createPhysicsEngine(gravity);

#ifndef NDEBUG
    getPhysicsEngine().setDebugDrawEnable(true);
#else
    getPhysicsEngine().setDebugDrawEnable(false);
#endif
}

///////////////////////////////////////////////////////////////
void GameplayScene::addWindowBorders() {
    ime::RigidBody::Ptr rigidBody = getPhysicsEngine().createBody(ime::RigidBody::Type::Static);
    ime::Collider* collider = rigidBody->attachCollider(ime::BoxCollider::create(ime::Vector2f(1.0f, (float) getWindow().getSize().y)));

    ime::CollisionFilterData colFilterData;
    colFilterData.categoryBitMask = collision::CATEGORY_VERT_WIN_BORDER;
    colFilterData.collisionBitMask = collision::MASK_VERT_WIN_BORDER;
    collider->setCollisionFilter(colFilterData);

    // Left window border
    ime::GameObject::Ptr leftBorder = ime::GameObject::create(*this);
    leftBorder->attachRigidBody(std::move(rigidBody));
    leftBorder->getTransform().setPosition({0.5f, getWindow().getSize().y / 2.0f});

    // Right window border
    ime::GameObject::Ptr rightBorder = leftBorder->copy();
    rightBorder->getTransform().setPosition(ime::Vector2f(getWindow().getSize().x, getWindow().getSize().y / 2.0f));

    getGameObjects().add("window-borders", std::move(leftBorder));
    getGameObjects().add("window-borders", std::move(rightBorder));
}

///////////////////////////////////////////////////////////////
void GameplayScene::createPlayerShip() {
    auto* playerShip = getGameObjects().add<Galaxyip>(std::make_unique<Galaxyip>(*this));
    playerShip->setTag("playerShip");
    playerShip->getTransform().setPosition(getWindow().getSize().x / 2.0f,
        getWindow().getSize().y - 1.5f * playerShip->getSprite().getGlobalBounds().height);

    gui::GameplayGui::addLives(getGui(), playerShip->getHeath() / 100);

    // Move the player
    getInput().onKeyDown([playerShip](ime::Keyboard::Key key) {
        const static ime::Vector2f shipSpeed = {300.0f, 0.0f};

        if (key == ime::Keyboard::Key::Left)
            playerShip->getRigidBody()->setLinearVelocity(-shipSpeed);
        else if (key == ime::Keyboard::Key::Right)
            playerShip->getRigidBody()->setLinearVelocity(shipSpeed);
    });

    // Stop the player
    getInput().onKeyUp([playerShip](ime::Keyboard::Key key) {
        ime::Vector2f playerVelocity = playerShip->getRigidBody()->getLinearVelocity();

        if ((key == ime::Keyboard::Key::Left && playerVelocity.x < 0) ||
            (key == ime::Keyboard::Key::Right && playerVelocity.x > 0))
        {
            playerShip->getRigidBody()->setLinearVelocity(ime::Vector2f{0.0f, 0.0f});
        }
    });

    // Attempt to fire the players bullet
    getInput().onKeyDown([this, playerShip](ime::Keyboard::Key key) {
        const static ime::Vector2f bulletVelocity = {0.0f, -600.0f};

        if (key == ime::Keyboard::Key::Space) {
            std::unique_ptr<Bullet> bullet = playerShip->fireBullet(bulletVelocity);

            if (bullet)
                getGameObjects().add("bullets", std::move(bullet));
        }
    });
}

void GameplayScene::onFrameEnd() {
    getGameObjects().removeIf([](const ime::GameObject* gameObject) {
        return !gameObject->isActive();
    });
}
