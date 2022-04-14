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

#include "PauseMenuGui.h"
#include "util/Utils.h"
#include <IME/ui/widgets/Panel.h>
#include <IME/ui/widgets/Label.h>
#include <IME/ui/widgets/Button.h>
#include <IME/ui/widgets/VerticalLayout.h>

namespace gui {
    ///////////////////////////////////////////////////////////////
    void PauseMenuGui::init(ime::ui::GuiContainer& guiContainer) {
        // Parent container
        auto pnlContainer = ime::ui::Panel::create();
        pnlContainer->setName("pnlContainer");
        pnlContainer->getRenderer()->setBackgroundColour(ime::Colour("#28282866"));

        // Sub parent container
        auto pnlSubContainer = ime::ui::Panel::create("60%", "50%");
        pnlSubContainer->setName("pnlSubContainer");
        pnlSubContainer->setOrigin(0.5f, 0.5f);
        pnlSubContainer->setPosition("50%", "50%");
        pnlSubContainer->getRenderer()->setBackgroundColour(ime::Colour("#0c0c0cE8"));
        pnlSubContainer->getRenderer()->setRoundedBorderRadius(8.0f);

        // Paused label
        auto lblHeading = ime::ui::Label::create("GAME PAUSED");
        lblHeading->getRenderer()->setFont("ChaletLondonNineteenSixty.ttf");
        lblHeading->getRenderer()->setTextStyle(ime::TextStyle::Bold);
        lblHeading->getRenderer()->setTextColour(ime::Colour::Red);
        lblHeading->setOrigin(0.5f, 0.0f);
        lblHeading->setPosition("50%", "4%");
        lblHeading->setTextSize(40.0f);
        pnlSubContainer->addWidget(std::move(lblHeading));

        // Buttons container
        auto vlButtonsContainer = ime::ui::VerticalLayout::create("40%", "28%");
        vlButtonsContainer->setName("vlButtons");
        vlButtonsContainer->setOrigin(0.5f, 0.5f);
        vlButtonsContainer->setPosition("50%", "50%");
        vlButtonsContainer->getRenderer()->setSpaceBetweenWidgets(12.0f);

        // Buttons
        vlButtonsContainer->addWidget(util::createButton("btnResume", "Resume"));
        vlButtonsContainer->addWidget(util::createButton("btnMainMenu", "Main Menu"));
        vlButtonsContainer->addWidget(util::createButton("btnExit", "Exit Game"));
        pnlSubContainer->addWidget(std::move(vlButtonsContainer));

        pnlContainer->addWidget(std::move(pnlSubContainer));
        guiContainer.addWidget(std::move(pnlContainer));
    }
}
