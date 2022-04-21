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

#include "GalaxianFormation.h"
#include "Drone.h"
#include "Emissary.h"
#include "Escort.h"
#include "Flagship.h"
#include <IME/graphics/Window.h>
#include <memory>

///////////////////////////////////////////////////////////////
GalaxianFormation::GalaxianFormation(ime::Scene &scene) :
    m_objects(scene.getGameObjects()),
    m_direction(1, 0)
{
    ime::Vector2u winSize = scene.getWindow().getSize();

    // Create Drone ships
    ime::Vector2f startPos = {(winSize.x / 2.0f) - 184.5f, (winSize.y / 2.0f) - 76};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 10; j++) {
            auto drone = std::make_unique<Drone>(scene);
            ime::Vector2f spriteSize = drone->getSprite().getGlobalBounds().getSize();
            drone->getTransform().setPosition(startPos.x + j * spriteSize.x, startPos.y - 1.4 * i * spriteSize.y);
            m_objects.add("drones", std::move(drone));
        }
    }

    // Create Emissary ships
    startPos = ime::Vector2f{(winSize.x / 2.0f) - 141.2f, startPos.y - 88.6f};

    for (int i = 0; i < 8; i++) {
        auto emissary = std::make_unique<Emissary>(scene);
        ime::Vector2f spriteSize = emissary->getSprite().getGlobalBounds().getSize();
        emissary->getTransform().setPosition(startPos.x + i * spriteSize.x, startPos.y);
        m_objects.add("emissaries", std::move(emissary));
    }

    // Create Escort ships
    startPos = {(winSize.x / 2.0f) - 99.0f, startPos.y - 27.6f};

    for (int i = 0; i < 6; i++) {
        auto escort = std::make_unique<Escort>(scene);
        ime::Vector2f spriteSize = escort->getSprite().getGlobalBounds().getSize();
        escort->getTransform().setPosition(startPos.x + i * spriteSize.x, startPos.y);
        m_objects.add("escorts", std::move(escort));
    }

    // Create Flagship ships
    startPos = {(winSize.x / 2.0f) - 56.5f, startPos.y - 29.6f};

    for (int i = 0; i < 2; i++) {
        auto flagship = std::make_unique<Flagship>(scene);
        ime::Vector2f spriteSize = flagship->getSprite().getGlobalBounds().getSize();
        flagship->getTransform().setPosition(startPos.x + 4.4f * i * spriteSize.x, startPos.y);
        m_objects.add("flagships", std::move(flagship));
    }

    // Change directions when galaxian collides with the vertical window borders
    m_objects.forEachInGroups({"drones", "emissaries", "escorts", "flagships"}, [this](ime::GameObject* gameObject) {
        gameObject->onRigidBodyCollisionStart([this](ime::GameObject*, ime::GameObject* other) {
            if (other->getTag() == "window-border") {
                m_direction *= -1;
                move();
            }
        });
    });
}

///////////////////////////////////////////////////////////////
void GalaxianFormation::move() {
    m_objects.forEachInGroups({"drones", "emissaries", "escorts", "flagships"}, [this](ime::GameObject* gameObject) {
        auto* galaxian = static_cast<Galaxian*>(gameObject);

        if (!galaxian->isBlowingUp() && !galaxian->isDiving())
            galaxian->getRigidBody()->setLinearVelocity(ime::Vector2f{60.0f * (float) m_direction.x, 0.0f});
    });
}
