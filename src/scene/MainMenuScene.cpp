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
#include "GameplayScene.h"
#include <IME/core/engine/Engine.h>
#include <IME/ui/widgets/Panel.h>

///////////////////////////////////////////////////////////////
MainMenuScene::MainMenuScene() {
    m_view = std::make_unique<gui::MainMenuGui>();
}

void MainMenuScene::onEnter() {
    /*-- Main menu event handlers  --*/

    ime::ui::GuiContainer& gui = getGui();

    // Play button handler
    gui.getWidget("btnPlay")->on("click", ime::Callback<>([this] {
        getEngine().popScene();
        getEngine().pushScene(std::make_unique<GameplayScene>());
    }));

    // Options button handler
    gui.getWidget("btnOptions")->on("click", ime::Callback<>([&gui] {

    }));

    // High score button handler
    gui.getWidget("btnHighScores")->on("click", ime::Callback<>([&gui] {
        gui.getWidget("pnlRibbon")->setVisible(false);
        gui.getWidget("pnlHighScores")->setVisible(true);
        gui.getWidget<ime::ui::Panel>("pnlMain")->getRenderer()->setBackgroundTexture("sub-main-menu-background.jpg");
    }));

    // About button handler
    gui.getWidget("btnAbout")->on("click", ime::Callback<>([&gui] {
        gui.getWidget("pnlRibbon")->setVisible(false);
        gui.getWidget("pnlAbout")->setVisible(true);
        gui.getWidget<ime::ui::Panel>("pnlMain")->getRenderer()->setBackgroundTexture("sub-main-menu-background.jpg");
    }));

    // Exit button handler
    gui.getWidget("btnExit")->on("click", ime::Callback<>([this] {
        getEngine().quit();
    }));

    /*** Sub menu event handlers **/

    // About panel close button handler
    gui.getWidget("btnCloseAboutPanel")->on("click", ime::Callback<>([&gui] {
        gui.getWidget("pnlAbout")->setVisible(false);
        gui.getWidget("pnlRibbon")->setVisible(true);
        gui.getWidget<ime::ui::Panel>("pnlMain")->getRenderer()->setBackgroundTexture("main-menu-background.jpg");
    }));

    // High scores close button handler
    gui.getWidget("btnCloseScoresPanel")->on("click", ime::Callback<>([&gui] {
        gui.getWidget("pnlHighScores")->setVisible(false);
        gui.getWidget("pnlRibbon")->setVisible(true);
        gui.getWidget<ime::ui::Panel>("pnlMain")->getRenderer()->setBackgroundTexture("main-menu-background.jpg");
    }));
}
