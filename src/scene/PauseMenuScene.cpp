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
#include <IME/ui/widgets/VerticalLayout.h>
#include <IME/ui/widgets/Button.h>

///////////////////////////////////////////////////////////////
PauseMenuScene::PauseMenuScene() {
    m_view = std::make_unique<gui::PauseMenuGui>();
}

///////////////////////////////////////////////////////////////
void PauseMenuScene::onEnter() {
    registerGuiEventHandlers();
    registerKeyboardEventHandlers();
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
    // We'll be using arrow keys to navigate the menu
    getGui().setTabKeyUsageEnabled(false);

    // Set the resume button as the default focused button
    getGui().getWidget<ime::ui::Button>("btnResume")->setFocused(true);

    // Allow the menu to be navigated with arrow keys
    getInput().onKeyUp([this](ime::Keyboard::Key key) {
        auto* vlButtons = getGui().getWidget<ime::ui::VerticalLayout>("vlButtons");

        if (key == ime::Keyboard::Key::Down)
            vlButtons->focusNextWidget();
        else if (key == ime::Keyboard::Key::Up)
            vlButtons->focusPreviousWidget();
        else if (key == ime::Keyboard::Key::Enter) {
            auto* focusedWidget = vlButtons->getFocusedWidget();

            if (focusedWidget)
                focusedWidget->emit("click");
        }
    });

    // Return to caller scene (Usually the gameplay scene)
    getInput().onKeyUp([this](ime::Keyboard::Key key) {
        if (key == ime::Keyboard::Key::Escape || key == ime::Keyboard::Key::P)
            getEngine().popScene();
    });
}

///////////////////////////////////////////////////////////////
void PauseMenuScene::onResumeFromCache() {
    getGui().getWidget<ime::ui::Button>("btnResume")->setFocused(true);
}
