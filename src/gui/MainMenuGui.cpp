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

#include "MainMenuGui.h"
#include "common/Config.h"
#include "util/Utils.h"
#include <IME/ui/widgets/Panel.h>
#include <IME/ui/widgets/VerticalLayout.h>
#include <IME/ui/widgets/HorizontalLayout.h>
#include <IME/ui/widgets/Button.h>
#include <IME/ui/widgets/Label.h>
#include <string>

namespace gui {
    ///////////////////////////////////////////////////////////////
    std::string getPrefix(int number) {
        switch (number) {
            case 1: return "ST";
            case 2: return "ND";
            case 3: return "RD";
            default: return "TH";
        }
    }

    ///////////////////////////////////////////////////////////////
    ime::ui::Panel::Ptr createSubMenuContainer(const std::string& name) {
        ime::ui::Panel::Ptr pnlContainer = ime::ui::Panel::create("80%", "80%");
        pnlContainer->setVisible(false);
        pnlContainer->setName("pnl" + name);
        pnlContainer->setOrigin(0.5f, 0.5f);
        pnlContainer->setPosition("50%", "50%");
        pnlContainer->getRenderer()->setBackgroundColour(ime::Colour::Black);
        pnlContainer->getRenderer()->setBackgroundColour(ime::Colour("#000000BA"));
        pnlContainer->getRenderer()->setRoundedBorderRadius(8.0f);

        // Panel close button
        auto btnClose = ime::ui::Button::create("x");
        btnClose->setName("btnClose" + name + "Panel");
        btnClose->setOrigin(1.0f, 0.0f);
        btnClose->setPosition("100%", "0%");
        btnClose->getRenderer()->setTextColour(ime::Colour::White);
        btnClose->getRenderer()->setBackgroundColour(ime::Colour::Transparent);
        btnClose->getRenderer()->setBorderColour(ime::Colour::Transparent);
        btnClose->getRenderer()->setFocusedBorderColour(ime::Colour::Transparent);
        btnClose->getRenderer()->setBorderHoverColour(ime::Colour::Transparent);
        btnClose->getRenderer()->setFocusedBorderColour(ime::Colour::Transparent);
        btnClose->getRenderer()->setBorderColourOnMouseDown(ime::Colour::Transparent);
        pnlContainer->addWidget(std::move(btnClose));

        return pnlContainer;
    }

    ///////////////////////////////////////////////////////////////
    ime::ui::VerticalLayout::Ptr createList(const std::string& heading, ime::Colour headingColour, const std::string& placeholder) {
        auto vlColumn = ime::ui::VerticalLayout::create();
        vlColumn->getRenderer()->setSpaceBetweenWidgets(5);

        // Create column heading
        auto* lblHeading = vlColumn->addWidget<ime::ui::Label>(ime::ui::Label::create(heading), "lblHeading");
        lblHeading->setHorizontalAlignment(ime::ui::Label::HorizontalAlignment::Center);
        lblHeading->getRenderer()->setTextColour(headingColour);
        lblHeading->getRenderer()->setTextStyle(ime::TextStyle::Bold);

        // Create placeholder text
        for (int i = 1; i <= 10; i++) {
            auto lblEntry = ime::ui::Label::create();
            lblEntry->setName("lbl" + heading + std::to_string(i));
            lblEntry->setHorizontalAlignment(ime::ui::Label::HorizontalAlignment::Center);

            if (heading == "RANK")
                lblEntry->setText(std::to_string(i) + getPrefix(i));
            else
                lblEntry->setText(placeholder);

            lblEntry->getRenderer()->setBorderColour(ime::Colour("#ffffff33"));
            lblEntry->getRenderer()->setTextColour(ime::Colour::White);
            vlColumn->addWidget(std::move(lblEntry));
        }

        return vlColumn;
    }


    ///////////////////////////////////////////////////////////////
    ime::ui::Panel::Ptr createMainPanel() {
        // Parent container
        auto pnlContainer = ime::ui::Panel::create();
        pnlContainer->setName("pnlMain");

        auto* pnlContainerRenderer = pnlContainer->getRenderer();
        pnlContainerRenderer->setBackgroundTexture("main-menu-background.jpg");

        // UI elements container
        auto pnlRibbon = ime::ui::Panel::create("32%", "100%");
        pnlRibbon->setName("pnlRibbon");
        pnlRibbon->getRenderer()->setBackgroundColour(ime::Colour("#12121233"));

        // Game name / logo
        auto* lblGameName = pnlRibbon->addWidget<ime::ui::Label>(ime::ui::Label::create("Galaxian"));
        lblGameName->setTextSize(40);
        lblGameName->setOrigin(0.5f, 0.0f);
        lblGameName->setPosition("50%", "10%");
        lblGameName->getRenderer()->setFont("Entanglement-rgpRB.ttf");
        lblGameName->getRenderer()->setTextStyle(ime::TextStyle::Italic);
        lblGameName->getRenderer()->setTextColour(ime::Colour::Yellow);

        // Buttons container
        auto vlButtonsContainer = ime::ui::VerticalLayout::create("70%", "28%");
        vlButtonsContainer->setOrigin(0.5f, 0.5f);
        vlButtonsContainer->setPosition("50%", "50%");
        vlButtonsContainer->getRenderer()->setSpaceBetweenWidgets(12.0f);

        // Buttons
        vlButtonsContainer->addWidget(util::createButton("btnResume", "Resume"));
        vlButtonsContainer->addWidget(util::createButton("btnPlay", "Start"));
        vlButtonsContainer->addWidget(util::createButton("btnOptions", "Options"));
        vlButtonsContainer->addWidget(util::createButton("btnHighScores", "High Scores"));
        vlButtonsContainer->addWidget(util::createButton("btnAbout", "About"));
        vlButtonsContainer->addWidget(util::createButton("btnExit", "Quit"));
        pnlRibbon->addWidget(std::move(vlButtonsContainer));

        // Game version
        auto lblVersion = ime::ui::Label::create("v " + config::VERSION);
        lblVersion->setTextSize(10);
        lblVersion->setOrigin(0.0f, 1.0f);
        lblVersion->setPosition("0%", "100%");
        lblVersion->getRenderer()->setTextStyle(ime::TextStyle::Italic);
        lblVersion->getRenderer()->setTextColour(ime::Colour("#FFFFFF99"));
        pnlRibbon->addWidget(std::move(lblVersion));

        pnlContainer->addWidget(std::move(pnlRibbon));

        return pnlContainer;
    }

    ///////////////////////////////////////////////////////////////
    ime::ui::Panel::Ptr createOptionsPanel() {
        return createSubMenuContainer("Options");
    }

    ///////////////////////////////////////////////////////////////
    ime::ui::Panel::Ptr createAboutPanel() {
        // Prent container
        ime::ui::Panel::Ptr pnlContainer = createSubMenuContainer("About");

        // Sub container
        auto* pnlCenterPanel = pnlContainer->addWidget<ime::ui::Panel>(ime::ui::Panel::create("90%", "80%"));
        pnlCenterPanel->getRenderer()->setBackgroundColour(ime::Colour::Transparent);
        pnlCenterPanel->setOrigin(0.5f, 0.5f);
        pnlCenterPanel->setPosition("50%", "50%");

        // Build information
        auto* vlBuildInfo = pnlCenterPanel->addWidget<ime::ui::VerticalLayout>(ime::ui::VerticalLayout::create("80%", "20%"));
        vlBuildInfo->setOrigin(0.5f, 0.0f);
        vlBuildInfo->setPosition("50%", "4%");

        auto lblName = ime::ui::Label::create("Galaxian v" + config::VERSION);
        lblName->setTextSize(17);
        lblName->getRenderer()->setTextStyle(ime::TextStyle::Bold);
        lblName->getRenderer()->setTextColour(ime::Colour("#F2F3F4"));
        vlBuildInfo->addWidget(std::move(lblName));

        auto lblBuildDate = ime::ui::Label::create("Built with IME v" + config::IME_VERSION + " on " + util::getDate());
        lblBuildDate->getRenderer()->setTextColour(ime::Colour("#B8B8B8"));
        vlBuildInfo->addWidget(std::move(lblBuildDate));
        vlBuildInfo->setRatio(std::size_t{1}, 0.85f);

        // Disclaimer label
        auto lblDisclaimerHeading = pnlCenterPanel->addWidget<ime::ui::Label>(ime::ui::Label::create("DISCLAIMER"));
        lblDisclaimerHeading->setTextSize(18);
        lblDisclaimerHeading->getRenderer()->setTextColour(ime::Colour::Red);
        lblDisclaimerHeading->getRenderer()->setTextStyle(ime::TextStyle::Bold);
        lblDisclaimerHeading->getRenderer()->setBackgroundColour(ime::Colour::Transparent);
        lblDisclaimerHeading->setOrigin(0.5f, 1.0f);
        lblDisclaimerHeading->setPosition("50%", ime::bindBottom(vlBuildInfo).append("+20%"));

        auto lblDisclaimer = ime::ui::Label::create(
                "This game is a demo for my 2D game engine, Infinite Motion Engine "
                "which can be found here - github.com/KwenaMashamaite/IME \n\n"
                "I do not own nor do I claim the idea for this game. The game is a "
                "clone of the original Galaxian game from Bandai Namco Entertainment. "
                "All third party content, brands, names, and logos are used under license "
                "and remain property of their respective owners.");

        lblDisclaimer->getRenderer()->setTextColour(ime::Colour("#B8B8B8"));
        lblDisclaimer->setHorizontalAlignment(ime::ui::Label::HorizontalAlignment::Center);
        lblDisclaimer->setVerticalAlignment(ime::ui::Label::VerticalAlignment::Top);
        lblDisclaimer->setSize("90%", "35%");
        lblDisclaimer->getRenderer()->setBackgroundColour(ime::Colour::Transparent);
        lblDisclaimer->getRenderer()->setBorderColour({192, 192, 192});
        lblDisclaimer->setOrigin(0.5f, 0.0f);
        lblDisclaimer->setPosition("50%", ime::bindBottom(lblDisclaimerHeading).append("+3%"));
        pnlCenterPanel->addWidget(std::move(lblDisclaimer));

        // Copyright label
        auto lblCopyright = ime::ui::Label::create("Copyright \xa9 2022 Kwena Mashamaite");
        lblCopyright->getRenderer()->setTextColour(ime::Colour("#B8B8B8"));
        lblCopyright->setOrigin(0.5f, 1.0f);
        lblCopyright->setPosition("50%", "98%");
        pnlContainer->addWidget(std::move(lblCopyright));

        return pnlContainer;
    }

    ///////////////////////////////////////////////////////////////
    ime::ui::Panel::Ptr createHighScorePanel() {
        // Parent container
        ime::ui::Panel::Ptr pnlContainer = createSubMenuContainer("HighScores");

        // High scores label
        auto* lblHighScores = pnlContainer->addWidget<ime::ui::Label>(ime::ui::Label::create("TOP 10 HIGH SCORES"));
        lblHighScores->setSize("90%", "5%");
        lblHighScores->setVerticalAlignment(ime::ui::Label::VerticalAlignment::Center);
        lblHighScores->setHorizontalAlignment(ime::ui::Label::HorizontalAlignment::Center);
        lblHighScores->setOrigin(0.5f, 0.0f);
        lblHighScores->setPosition("50%", "10%");
        lblHighScores->getRenderer()->setBackgroundColour(ime::Colour::Transparent);
        lblHighScores->setTextSize(18.0f);
        lblHighScores->getRenderer()->setTextColour(ime::Colour("#ffffffe6"));
        lblHighScores->getRenderer()->setTextStyle(ime::TextStyle::Bold);

        // Vertical layout list
        auto hlEntryContainer = ime::ui::HorizontalLayout::create("80%", "80%");
        hlEntryContainer->setOrigin(0.5f, 0.0f);
        hlEntryContainer->setPosition("50%", ime::bindBottom(lblHighScores).append("+4%"));

        hlEntryContainer->addWidget(createList("RANK", ime::Colour::Green, ""));
        hlEntryContainer->addWidget(createList("NAME", ime::Colour::Yellow, "AAA"));
        hlEntryContainer->addWidget(createList("SCORE", ime::Colour::Violet, "00"));
        hlEntryContainer->addWidget(createList("LEVEL", ime::Colour("#9f5afd"), "1"));
        hlEntryContainer->addWidget(createList("DATE", ime::Colour::Pink, util::getDate()));
        pnlContainer->addWidget(std::move(hlEntryContainer));

        return pnlContainer;
    }

    ///////////////////////////////////////////////////////////////
    void MainMenuGui::init(ime::ui::GuiContainer& guiContainer) {
        guiContainer.addWidget(createMainPanel());
        guiContainer.addWidget(createOptionsPanel());
        guiContainer.addWidget(createHighScorePanel());
        guiContainer.addWidget(createAboutPanel());
    }
}
