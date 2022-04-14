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

#ifndef GALAXIAN_SCROLLINGBACKGROUNDSCENE_H
#define GALAXIAN_SCROLLINGBACKGROUNDSCENE_H

#include "Scene.h"

/**
 * @brief A scene that displays an infinite vertical scrolling background
 */
class ScrollingBackgroundScene : public ime::Scene {
public:
    /**
     * @brief Default constructor
     */
    ScrollingBackgroundScene();

    /**
     * @brief Enter the scrolling background scene
     *
     * This function is called once by IME when the scene is entered for
     * the first time
     */
    void onEnter() override;

    /**
     * @brief Update the scene at fixed intervals
     * @param deltaTime The time passed since the last update
     *
     * This function is called by IME every fixed frame-rate frame
     */
    void onFixedUpdate(ime::Time deltaTime) override;

private:
    /**
     * @brief Update a background sprite
     * @param name The name/tag of the background sprite to be updated
     * @param deltaTime The time passed since the last update
     */
    void update(const std::string& name, const ime::Time& deltaTime);

private:
    float m_speed;                 //!< The scroll m_speed
    ime::Vector2f m_bg2StartPos;   //!< The start position of the second background sprite
};

#endif //GALAXIAN_SCROLLINGBACKGROUNDSCENE_H
