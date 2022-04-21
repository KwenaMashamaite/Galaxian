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
    m_objects(scene.getGameObjects())
{
    ime::Vector2u winSize = scene.getWindow().getSize();

    // Create Drone ships
    const int NUM_DRONES_PER_ROW = 10;
    ime::Vector2f startPos = {(winSize.x / 2.0f) - 148.5f, winSize.y / 2.0f};

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < NUM_DRONES_PER_ROW; j++) {
            auto drone = std::make_unique<Drone>(scene);
            ime::Vector2f spriteSize = drone->getSprite().getGlobalBounds().getSize();
            drone->getTransform().setPosition(startPos.x + 1.5 * j * spriteSize.x, startPos.y - 1.8 * i * spriteSize.y);
            m_objects.add("drones", std::move(drone));
        }
    }

    // Create Emissary ships
    const int NUM_EMISSARY_PER_ROW = 8;
    startPos = {(winSize.x / 2.0f) - 116.0f, (winSize.y / 2.0f) - 81.6f};

    for (int i = 0; i < NUM_EMISSARY_PER_ROW; i++) {
        auto emissary = std::make_unique<Emissary>(scene);
        ime::Vector2f spriteSize = emissary->getSprite().getGlobalBounds().getSize();
        emissary->getTransform().setPosition(startPos.x + 1.5 * i * spriteSize.x, startPos.y);
        m_objects.add("emissaries", std::move(emissary));
    }

    // Create Escort ships
    const int NUM_ESCORT_PER_ROW = 6;
    startPos = {(winSize.x / 2.0f) - 82.0f, (winSize.y / 2.0f) - 105.6f};

    for (int i = 0; i < NUM_ESCORT_PER_ROW; i++) {
        auto escort = std::make_unique<Escort>(scene);
        ime::Vector2f spriteSize = escort->getSprite().getGlobalBounds().getSize();
        escort->getTransform().setPosition(startPos.x + 1.5 * i * spriteSize.x, startPos.y);
        m_objects.add("escorts", std::move(escort));
    }

    // Create Flagship ships
    const int NUM_FLAGSHIP_PER_ROW = 2;
    startPos = {(winSize.x / 2.0f) - 50.0f, (winSize.y / 2.0f) - 130.6f};

    for (int i = 0; i < NUM_FLAGSHIP_PER_ROW; i++) {
        auto flagship = std::make_unique<Flagship>(scene);
        ime::Vector2f spriteSize = flagship->getSprite().getGlobalBounds().getSize();
        flagship->getTransform().setPosition(startPos.x + 4.5f * i * spriteSize.x, startPos.y);
        m_objects.add("flagships", std::move(flagship));
    }
}
