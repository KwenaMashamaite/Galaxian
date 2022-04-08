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

#include "GameEngine.h"
#include "scene/LoadScreenScene.h"

///////////////////////////////////////////////////////////////
ime::PrefContainer getEngineSettings() {
    ime::PrefContainer settings;
    settings.addPref(ime::Preference{"WINDOW_TITLE", ime::PrefType::String, std::string("Galaxian")});
    settings.addPref(ime::Preference{"WINDOW_WIDTH", ime::PrefType::Int, 800});
    settings.addPref(ime::Preference{"WINDOW_HEIGHT", ime::PrefType::Int, 600});
    settings.addPref(ime::Preference{"WINDOW_ICON", ime::PrefType::String, std::string("res/Images/icon.png")});
    settings.addPref(ime::Preference{"FULLSCREEN", ime::PrefType::Bool, false});
    settings.addPref(ime::Preference{"V_SYNC", ime::PrefType::Bool, false});
    settings.addPref(ime::Preference{"FPS_LIMIT", ime::PrefType::Int, 60});
    settings.addPref(ime::Preference{"FONTS_DIR", ime::PrefType::String, std::string("res/Fonts/")});
    settings.addPref(ime::Preference{"TEXTURES_DIR", ime::PrefType::String, std::string("res/Images/")});
    settings.addPref(ime::Preference{"MUSIC_DIR", ime::PrefType::String, std::string("res/Music/")});
    settings.addPref(ime::Preference{"SOUND_EFFECTS_DIR", ime::PrefType::String, std::string("res/SoundEffects/")});

    return settings;
}

///////////////////////////////////////////////////////////////
GameEngine::GameEngine() : m_engine("Galaxian", getEngineSettings()) {
    m_engine.onInit([this] {
        m_engine.getWindow().setStyle(ime::WindowStyle::Close);
        m_engine.getWindow().setDefaultOnCloseHandlerEnable(false);

        // Push the initial scene
        m_engine.pushScene(std::make_unique<LoadScreenScene>());
    });
}

///////////////////////////////////////////////////////////////
void GameEngine::init() {
    m_engine.initialize();
}

///////////////////////////////////////////////////////////////
void GameEngine::run() {
    m_engine.run();
}
