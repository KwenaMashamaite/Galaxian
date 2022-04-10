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

#ifndef GALAXIAN_PAUSEMENUSCENE_H
#define GALAXIAN_PAUSEMENUSCENE_H

#include "Scene.h"

/**
 * @brief Pause menu scene
 */
class PauseMenuScene : public Scene {
public:
    /**
     * @brief Default constructor
     */
    PauseMenuScene();

    /**
     * @brief Enter the main menu scene
     *
     * This function is called once by IME when the scene is entered for
       the first time
     */
    void onEnter() override;

    /**
     * @brief Resume scene from cache
     *
     * This function is called by IME when the scene is uncached and
     * pushed to the engine
     */
    void onResumeFromCache() override;

private:
    /**
     * @brief Register gui input event handlers
     */
    void registerGuiEventHandlers();

    /**
     * @brief Register keyboard input event handlers
     */
    void registerKeyboardEventHandlers();
};


#endif //GALAXIAN_PAUSEMENUSCENE_H
