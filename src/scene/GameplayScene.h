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

#ifndef GALAXIAN_GAMEPLAYSCENE_H
#define GALAXIAN_GAMEPLAYSCENE_H

#include "Scene.h"
#include "actors/GalaxianFormation.h"
#include <memory>

/**
 * @brief Gameplay scene
 */
class GameplayScene : public Scene {
public:
    /**
     * @brief Default constructor
     */
    GameplayScene();

    /**
     * @brief Enter the gameplay scene
     *
     * This function is called once by IME when the scene is entered for the
     * first time
     */
    void onEnter() override;

    /**
     * @brief Destroy inactive game objects
     *
     * This function is called by IME at the end of the current frame
     */
    void onFrameEnd() override;

private:
    /**
     * @brief Initialize the gui
     */
    void initGui();

    /**
     * @brief Register event handlers
     */
    void registerEventHandlers();

    /**
     * @brief Create the 2D physics engine
     */
    void initPhysicsEngine();

    /**
     * @brief Add vertical window borders
     *
     * This borders prevent the player from leaving the game window
     */
    void addWindowBorders();

    /**
     * @brief Create the player ship
     */
    void createPlayerShip();

    /**
     * @brief Create the galaxian ships
     */
    void createGalaxians();

private:
    std::unique_ptr<GalaxianFormation> m_galaxianFormation;
};

#endif //GALAXIAN_GAMEPLAYSCENE_H
