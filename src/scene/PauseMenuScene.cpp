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

#include "PauseMenuScene.h"
#include "gui/PauseMenuGui.h"
#include <IME/core/engine/Engine.h>
#include <IME/ui/widgets/Button.h>

///////////////////////////////////////////////////////////////
PauseMenuScene::PauseMenuScene() {
    m_view = std::make_unique<gui::PauseMenuGui>();
}

///////////////////////////////////////////////////////////////
void PauseMenuScene::onEnter() {
    registerGuiEventHandlers();
    registerKeyboardEventHandlers();
    enableKeyboardNavigation(true, "btnResume");
}

///////////////////////////////////////////////////////////////
void PauseMenuScene::registerGuiEventHandlers() {
    // Resume button handler
    getGui().getWidget("btnResume")->on("click", ime::Callback<>([this] {
        getEngine().popScene();
    }));

    // Main menu button handler
    getGui().getWidget("btnMainMenu")->on("click", ime::Callback<>([this] {
        getEngine().removeAllScenes();
        getEngine().pushCachedScene("MainMenuScene");
    }));

    // Exit game button handler
    getGui().getWidget("btnExit")->on("click", ime::Callback<>([this] {
        getEngine().quit();
    }));
}

///////////////////////////////////////////////////////////////
void PauseMenuScene::registerKeyboardEventHandlers() {
    // Return to caller scene (Usually the gameplay scene)
    getInput().onKeyUp([this](ime::Keyboard::Key key) {
        if (key == ime::Keyboard::Key::Escape || key == ime::Keyboard::Key::P)
            getEngine().popScene();
    });
}
