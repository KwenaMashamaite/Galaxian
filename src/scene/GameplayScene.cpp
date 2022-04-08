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
#include "gui/GameplayGui.h"
#include <IME/core/engine/Engine.h>

///////////////////////////////////////////////////////////////
GameplayScene::GameplayScene() {
    m_view = std::make_unique<gui::GameplayGui>();
}

void GameplayScene::onEnter() {
    setCached(true, "GameplayScene");

    // Pause game
    getEngine().cacheScene("PauseMenuScene", std::make_unique<PauseMenuScene>());

    auto pauseGame = [this] { getEngine().pushCachedScene("PauseMenuScene"); };

    int handler = getWindow().onClose(pauseGame);
    onDestruction([handler, this] {
        getWindow().removeEventListener(handler);
    });

    getInput().bindKey(ime::Keyboard::Key::P, ime::input::KeyBindType::KeyUp, pauseGame);
    getInput().bindKey(ime::Keyboard::Key::Escape, ime::input::KeyBindType::KeyUp, pauseGame);
}
