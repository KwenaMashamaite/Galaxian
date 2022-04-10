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

#include "GameOverGui.h"
#include "util/Utils.h"
#include <IME/ui/widgets/Panel.h>
#include <IME/ui/widgets/Label.h>
#include <IME/ui/widgets/VerticalLayout.h>
#include <IME/ui/widgets/HorizontalLayout.h>
#include <algorithm>

namespace gui {
    ///////////////////////////////////////////////////////////////
    ime::ui::HorizontalLayout::Ptr createStat(const std::string& name, const std::string& value,
        const std::string& valueLabelName)
    {
        auto hlStatsContainer = ime::ui::HorizontalLayout::create();

        auto lblStat = ime::ui::Label::create(name);
        lblStat->setAutoSize(false);
        lblStat->getRenderer()->setBorders(ime::Borders{0.0f, 0.0f, 0.0f, 1.0f});
        lblStat->getRenderer()->setTextColour(ime::Colour("#C1C7C9"));
        lblStat->setVerticalAlignment(ime::ui::Label::VerticalAlignment::Center);

        auto lblStatValue = lblStat->copy();
        lblStatValue->setName(valueLabelName);
        lblStatValue->setText(value);
        lblStatValue->setHorizontalAlignment(ime::ui::Label::HorizontalAlignment::Right);

        hlStatsContainer->addWidget(std::move(lblStat));
        hlStatsContainer->addWidget(std::move(lblStatValue));

        return hlStatsContainer;
    }

    ///////////////////////////////////////////////////////////////
    void GameOverGui::init(ime::ui::GuiContainer& guiContainer) {
        // Parent container
        auto pnlContainer = ime::ui::Panel::create();
        pnlContainer->setName("pnlContainer");
        pnlContainer->getRenderer()->setBackgroundTexture("game-over-menu-background.jpg");

        // Sub prent container
        auto pnlSubContainer = ime::ui::Panel::create("60%", "60%");
        pnlSubContainer->setName("pnlSubContainer");
        pnlSubContainer->setOrigin(0.5f, 0.5f);
        pnlSubContainer->setPosition("50%", "50%");
        pnlSubContainer->getRenderer()->setBackgroundColour(ime::Colour("#0c0c0cE8"));
        pnlSubContainer->getRenderer()->setRoundedBorderRadius(8.0f);

        // Game over label
        auto* lblHeading = pnlSubContainer->addWidget<ime::ui::Label>(ime::ui::Label::create("Game Over"));
        lblHeading->getRenderer()->setFont("GameOverDude-KYXy.ttf");
        lblHeading->getRenderer()->setTextStyle(ime::TextStyle::Bold);
        lblHeading->getRenderer()->setTextColour(ime::Colour::Yellow);
        lblHeading->setOrigin(0.5f, 0.0f);
        lblHeading->setPosition("50%", "6%");
        lblHeading->setTextSize(35.0f);

        // Stats container
        auto* vlStatsContainer = pnlSubContainer->addWidget<ime::ui::VerticalLayout>(ime::ui::VerticalLayout::create("45%", "33%"));
        vlStatsContainer->setOrigin(0.5f, 0.0f);
        vlStatsContainer->setPosition("50%", ime::bindBottom(lblHeading).append("+5%"));

        // Stats
        vlStatsContainer->addWidget(createStat("High Score", "0", "lblHighScoreVal"));
        vlStatsContainer->addWidget(createStat("Your Score", "0", "lblPlayerScoreVal"));
        vlStatsContainer->addWidget(createStat("Level", "1", "lblLevelVal"));
        vlStatsContainer->addWidget(createStat("Play Time", "0:0:0", "lblPlayTimeVal"));

        // Navigation buttons container
        auto vlButtonsContainer = ime::ui::VerticalLayout::create("35%", "23%");
        vlButtonsContainer->setName("vlButtons");
        vlButtonsContainer->setOrigin(0.5f, 0.0f);
        vlButtonsContainer->setPosition("50%", ime::bindBottom(vlStatsContainer).append("+12%"));
        vlButtonsContainer->getRenderer()->setSpaceBetweenWidgets(12.0f);

        // Navigation buttons
        vlButtonsContainer->addWidget(util::createButton("btnReplay", "Play Again"));
        vlButtonsContainer->addWidget(util::createButton("btnMainMenu", "Main Menu"));
        vlButtonsContainer->addWidget(util::createButton("btnExit", "Exit Game"));
        pnlSubContainer->addWidget(std::move(vlButtonsContainer));

        // Add widgets to parent container
        pnlContainer->addWidget(std::move(pnlSubContainer));

        // Add parent container (with all widgets) to scenes gui
        guiContainer.addWidget(std::move(pnlContainer));
    }
}