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

#include "LoadScreenScene.h"
#include "gui/LoadScreenGui.h"
#include "MainMenuScene.h"
#include <IME/ui/widgets/ProgressBar.h>
#include <IME/ui/widgets/Label.h>
#include <IME/core/resources/ResourceLoader.h>
#include <IME/core/engine/Engine.h>
#include <thread>
#include <algorithm>

///////////////////////////////////////////////////////////////
void loadGameAssets() {
    ime::ResourceLoader::loadFromFile(ime::ResourceType::Font, {
        "Entanglement-rgpRB.ttf"
    });

    ime::ResourceLoader::loadFromFile(ime::ResourceType::Texture,  {
        "main-menu-background.jpg", "sub-main-menu-background.jpg"
    });
}

///////////////////////////////////////////////////////////////
LoadScreenScene::LoadScreenScene() {
    m_view = std::make_unique<gui::LoadScreenGui>();
}

///////////////////////////////////////////////////////////////
void LoadScreenScene::onEnter() {
    // Transition to the main menu when the progress bar if filled
    getGui().getWidget("pbrLoadProgress")->on("full", ime::Callback<>([this] {
        getEngine().popScene();

        // Instantiate the main menu once
        getEngine().cacheScene("MainMenuScene", std::make_unique<MainMenuScene>());
        getEngine().pushCachedScene("MainMenuScene");
    }));

    // Update the loading text every interval
    getTimer().setInterval(ime::milliseconds(300), [this] {
        auto* lblLoading = getGui().getWidget<ime::ui::Label>("lblLoading");
        std::string lblLoadingText = lblLoading->getText();

        unsigned int dotCount = std::count(lblLoadingText.begin(), lblLoadingText.end(), '.');

        if (dotCount == 0)
            lblLoading->setText("Loading, please wait.");
        else if (dotCount == 1)
            lblLoading->setText("Loading, please wait..");
        else if (dotCount == 2)
            lblLoading->setText("Loading, please wait...");
        else
            lblLoading->setText("Loading, please wait");
    });

    // Update the progress bar every interval
    getTimer().setInterval(ime::milliseconds(30), [this] {
        auto* pbrProgress = getGui().getWidget<ime::ui::ProgressBar>("pbrLoadProgress");
        pbrProgress->incrementValue();
        pbrProgress->setText(std::to_string(static_cast<int>(((float) (pbrProgress->getValue()) / (float) pbrProgress->getMaximumValue()) * 100)) + "%");
    });

    // The progress bar and the thread are not in sync. The thread finishes
    // almost instantly and the progress bar is just for user experience
    std::thread(&loadGameAssets).detach();
}
