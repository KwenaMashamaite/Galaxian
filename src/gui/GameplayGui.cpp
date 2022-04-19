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

#include "GameplayGui.h"
#include <IME/ui/widgets/Label.h>
#include <IME/ui/widgets/Picture.h>
#include <IME/ui/widgets/Panel.h>
#include <IME/ui/widgets/HorizontalLayout.h>
#include <cassert>

namespace gui {
    ///////////////////////////////////////////////////////////////
    void GameplayGui::init(ime::ui::GuiContainer &guiContainer) {
        // Parent container
        auto pnlContainer = ime::ui::Panel::create();
        pnlContainer->setName("pnlContainer");
        pnlContainer->getRenderer()->setFont("Emulogic-zrEw.ttf");
        pnlContainer->getRenderer()->setBackgroundColour(ime::Colour::Transparent);

        // One up label
        auto* lblOneUp = pnlContainer->addWidget<ime::ui::Label>(ime::ui::Label::create("1UP"), "lblOneUp");
        lblOneUp->setPosition("8.3%", "0");
        lblOneUp->getRenderer()->setTextColour(ime::Colour::Red);

        // Score value
        auto lblScoreValue = ime::ui::Label::create("00");
        lblScoreValue->setName("lblScoreVal");
        lblScoreValue->getRenderer()->setTextColour(ime::Colour::White);
        lblScoreValue->setPosition("4%", ime::bindBottom(lblOneUp));
        pnlContainer->addWidget(std::move(lblScoreValue));

        // High score label
        auto* lblHighScore = pnlContainer->addWidget<ime::ui::Label>(ime::ui::Label::create("HIGH SCORE"));
        lblHighScore->setOrigin(0.5f, 0.0f);
        lblHighScore->getRenderer()->setTextColour(ime::Colour::Red);
        lblHighScore->setPosition("50%", "0");

        // High score value
        auto lblHighScoreValue = ime::ui::Label::create("00");
        lblHighScoreValue->setName("lblHighScoreVal");
        lblHighScoreValue->setOrigin(0.5f, 0.0f);
        lblHighScoreValue->getRenderer()->setTextColour(ime::Colour::White);
        lblHighScoreValue->setPosition("50%", ime::bindBottom(lblHighScore));
        pnlContainer->addWidget(std::move(lblHighScoreValue));

        guiContainer.addWidget(std::move(pnlContainer));
    }

    void GameplayGui::addLives(ime::ui::GuiContainer& guiContainer, int lives) {
        assert(lives > 0);

        ime::ui::Picture::Ptr picLife = ime::ui::Picture::create("objects-spritesheet.png", ime::UIntRect{127, 238, 7, 9});

        ime::ui::HorizontalLayout::Ptr container = ime::ui::HorizontalLayout::create("8%", "4%");
        container->getRenderer()->setSpaceBetweenWidgets(4);
        container->setOrigin(0.0f, 1.0f);
        container->setPosition("2%", "99%");

        for (int i = 0; i < lives - 1; i++)
            container->addWidget(picLife->copy());

        container->addWidget(std::move(picLife));
        guiContainer.getWidget<ime::ui::Panel>("pnlContainer")->addWidget(std::move(container));
    }
}
