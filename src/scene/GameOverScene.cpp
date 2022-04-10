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

#include "GameOverScene.h"
#include "GameplayScene.h"
#include "gui/GameOverGui.h"
#include <IME/core/engine/Engine.h>
#include <IME/ui/widgets/Label.h>

///////////////////////////////////////////////////////////////
GameOverScene::GameOverScene() {
    m_view = std::make_unique<gui::GameOverGui>();
}

///////////////////////////////////////////////////////////////
void GameOverScene::onEnter() {
    setCached(true, "GameOverScene");
    enableKeyboardNavigation(true, "btnReplay");
    populateGui();
    registerEventHandlers();
}

///////////////////////////////////////////////////////////////
void GameOverScene::onResumeFromCache() {
    Scene::onResumeFromCache();
    populateGui();
}

///////////////////////////////////////////////////////////////
void GameOverScene::populateGui() {
    auto& gui = getGui();
    auto& cache = getCache();

    gui.getWidget<ime::ui::Label>("lblLevelVal")->setText(std::to_string(cache.getValue<int>("CURRENT_LEVEL")));
    gui.getWidget<ime::ui::Label>("lblPlayerScoreVal")->setText(std::to_string(cache.getValue<int>("CURRENT_SCORE")));
    gui.getWidget<ime::ui::Label>("lblHighScoreVal")->setText(std::to_string(cache.getValue<int>("HIGH_SCORE")));
    gui.getWidget<ime::ui::Label>("lblPlayTimeVal")->setText(std::to_string(cache.getValue<ime::Time>("PLAY_TIME").asMinutes()) + " minutes");
}

///////////////////////////////////////////////////////////////
void GameOverScene::registerEventHandlers() {
    // Play again button handler
    getGui().getWidget("btnReplay")->on("click", ime::Callback<>([this] {
        getEngine().popScene();
        getEngine().pushScene(std::make_unique<GameplayScene>());
    }));

    // Main menu button handler
    getGui().getWidget("btnMainMenu")->on("click", ime::Callback<>([this] {
        getEngine().popScene();
        getEngine().pushCachedScene("MainMenuScene");
    }));

    // Exit game button handler
    getGui().getWidget("btnExit")->on("click", ime::Callback<>([this] {
        getEngine().quit();
    }));
}
