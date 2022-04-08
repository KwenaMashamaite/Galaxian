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

#include "LoadScreenGui.h"
#include <IME/ui/widgets/Panel.h>
#include <IME/ui/widgets/ProgressBar.h>
#include <IME/ui/widgets/Picture.h>
#include <IME/ui/widgets/Label.h>

namespace gui {
    ///////////////////////////////////////////////////////////////
    void LoadScreenGui::init(ime::ui::GuiContainer &guiContainer) {
        // Parent container
        auto pnlContainer = ime::ui::Panel::create();
        pnlContainer->getRenderer()->setBackgroundColour(ime::Colour::Black);

        // Engine logo
        auto picLEngineLogo = pnlContainer->addWidget(ime::ui::Picture::create("IME_logo.png"));
        picLEngineLogo->setOrigin(0.5f, 0.0f);
        picLEngineLogo->setPosition("50%", "50%");

        // Powered by label
        auto lblPoweredBy = ime::ui::Label::create("Powered by");
        lblPoweredBy->getRenderer()->setTextStyle(ime::TextStyle::Italic);
        lblPoweredBy->setOrigin(0.5f, 1.0f);
        lblPoweredBy->setPosition("50%", ime::bindTop(picLEngineLogo));
        pnlContainer->addWidget(std::move(lblPoweredBy), "lblPoweredBy");

        // Asset loading progress indicator
        auto* pbrAssetLoading = pnlContainer->addWidget<ime::ui::ProgressBar>(ime::ui::ProgressBar::create(""), "pbrLoadProgress");
        pbrAssetLoading->setMaximumValue(100);
        pbrAssetLoading->getRenderer()->setBorderColour({0, 230, 64, 135});
        pbrAssetLoading->getRenderer()->setFillColour(ime::Colour("#4d05e8"));
        pbrAssetLoading->setOrigin(0.5f, 0.0f);
        pbrAssetLoading->setSize("80%", "14");
        pbrAssetLoading->setPosition("50%", "95%");

        // Loading label
        auto lblLoading = ime::ui::Label::create("Loading, please wait ... ");
        lblLoading->setAutoSize(false);
        lblLoading->getRenderer()->setTextColour(ime::Colour::White);
        lblLoading->setOrigin(0.5f, 1.0f);
        lblLoading->setPosition("50%", ime::bindTop(pbrAssetLoading).append("-5"));
        pnlContainer->addWidget(std::move(lblLoading), "lblLoading");

        guiContainer.addWidget(std::move(pnlContainer));
    }
}