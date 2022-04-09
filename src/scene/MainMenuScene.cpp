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

#include "MainMenuScene.h"
#include "gui/MainMenuGui.h"
#include "gui/widgets/ClosablePanel.h"
#include "GameplayScene.h"
#include "scoreboard/Scoreboard.h"
#include <IME/core/engine/Engine.h>
#include <IME/ui/widgets/Label.h>
#include <IME/ui/widgets/Panel.h>
#include <IME/ui/widgets/Button.h>
#include <IME/ui/widgets/VerticalLayout.h>

///////////////////////////////////////////////////////////////
MainMenuScene::MainMenuScene() {
    m_view = std::make_unique<gui::MainMenuGui>();
}

///////////////////////////////////////////////////////////////
void MainMenuScene::onEnter() {
    populateScoreboard();
    registerEventHandlers();

    // On boot up, the game cannot be resumed
    getGui().getWidget("btnResume")->setVisible(false);

    // Support main menu navigation with the keyboard
    getGui().getWidget<ime::ui::Button>("btnPlay")->setFocused(true);
    getGui().setTabKeyUsageEnabled(false);

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
        } else if (key == ime::Keyboard::Key::Backspace) {
            if (!m_activeSubMenuPanel.empty())
                getGui().getWidget<gui::ClosablePanel>(m_activeSubMenuPanel)->close();
        }
    });
}

///////////////////////////////////////////////////////////////
void MainMenuScene::onResumeFromCache() {
    if (getEngine().isSceneCached("GameplayScene")) {
        getGui().getWidget("btnResume")->setVisible(true);
        getGui().getWidget<ime::ui::Button>("btnPlay")->setText("New Game");
    }
}

///////////////////////////////////////////////////////////////
void MainMenuScene::onExit() {
    Scene::onExit();
    getGui().getWidget("btnResume")->setVisible(false);
    getGui().getWidget<ime::ui::Button>("btnPlay")->setText("Play");
}

///////////////////////////////////////////////////////////////
void MainMenuScene::populateScoreboard() {
    auto* scoreboard = getCache().getValue<Scoreboard*>("SCOREBOARD");

    // Replace placeholder text with actual Scoreboard data
    scoreboard->forEach([this, count = 1] (const Score& score) mutable {
        static const int MAX_NUM_HIGH_SCORES_TO_DISPLAY = 10;
        if (count > MAX_NUM_HIGH_SCORES_TO_DISPLAY)
            return;

        auto& gui = getGui();
        gui.getWidget<ime::ui::Label>("lblNAME" + std::to_string(count))->setText(score.owner);
        gui.getWidget<ime::ui::Label>("lblSCORE" + std::to_string(count))->setText(std::to_string(score.value));
        gui.getWidget<ime::ui::Label>("lblLEVEL" + std::to_string(count))->setText(std::to_string(score.level));
        gui.getWidget<ime::ui::Label>("lblDATE" + std::to_string(count))->setText(score.date);
        count++;
    });
}

///////////////////////////////////////////////////////////////
void MainMenuScene::registerEventHandlers() {
    ime::ui::GuiContainer& gui = getGui();

    /*-- Main panel event handlers --*/

    // Resume button handler
    gui.getWidget("btnResume")->on("click", ime::Callback<>([this] {
        getEngine().popScene();
        getEngine().pushCachedScene("GameplayScene");
    }));

    // Play button handler
    gui.getWidget("btnPlay")->on("click", ime::Callback<>([this] {
        getEngine().uncacheScene("GameplayScene");
        getEngine().popScene();
        getEngine().pushScene(std::make_unique<GameplayScene>());
    }));

    // Exit button handler
    gui.getWidget("btnExit")->on("click", ime::Callback<>([this] {
        getEngine().quit();
    }));

    // Hide the main menu panel and display a sub menu panel
    auto showSubMenu = [&gui, this](const std::string& subMenuPanel) {
        m_activeSubMenuPanel = subMenuPanel;
        gui.getWidget("pnlRibbon")->setVisible(false);
        gui.getWidget(subMenuPanel)->setVisible(true);
        gui.moveWidgetToFront(subMenuPanel);
        gui.getWidget<ime::ui::Panel>("pnlMain")->getRenderer()->setBackgroundTexture("sub-main-menu-background.jpg");
    };

    gui.getWidget("btnOptions")->on("click", ime::Callback<>(std::bind(showSubMenu, "pnlOptions")));
    gui.getWidget("btnHighScores")->on("click", ime::Callback<>(std::bind(showSubMenu, "pnlHighScores")));
    gui.getWidget("btnAbout")->on("click", ime::Callback<>(std::bind(showSubMenu, "pnlAbout")));

    /*-- Sub menu panels event handlers --*/

    // Hide the submenu panel and show the main menu panel
    auto showMainMenu = [&gui, this]() {
        m_activeSubMenuPanel.clear();
        gui.getWidget("pnlRibbon")->setVisible(true);
        gui.getWidget<ime::ui::Panel>("pnlMain")->getRenderer()->setBackgroundTexture("main-menu-background.jpg");
    };

    gui.getWidget<gui::ClosablePanel>("pnlOptions")->onClose(showMainMenu);
    gui.getWidget<gui::ClosablePanel>("pnlHighScores")->onClose(showMainMenu);
    gui.getWidget<gui::ClosablePanel>("pnlAbout")->onClose(showMainMenu);
}
