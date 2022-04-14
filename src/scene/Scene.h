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

#ifndef GALAXIAN_SCENE_H
#define GALAXIAN_SCENE_H

#include "gui/IView.h"

#include <IME/core/scene/Scene.h>
#include <memory>

/**
 * @brief A base class for all game scenes
 */
class Scene : public ime::Scene {
public:
    /**
     * @brief Constructor
     */
    Scene();

    /**
     * @brief Initialise the scene gui
     */
    void onInit() override;

    /**
     * @brief Resume scene from cache
     *
     * This function is called by IME when the scene is uncached and
     * pushed to the engine
     */
    void onResumeFromCache() override;

protected:
    /**
     * @brief Enable navigation of the menu with the keyboard arrow keys
     * @param enable True to enable keyboard navigation or false otherwise
     * @param defaultButton The name of the default focused button
     *
     * @warning This function enables navigation of ime::ui::Button widgets
     * placed inside a ime::ui::VerticalLayout with the name 'vlButtons'.
     * Therefore, calling this function with an argument of @a true on a
     * scene that does not have the aforementioned widget is undefined behavior.
     * Furthermore, it is also undefined behaviour if the specified default
     * button cannot be found
     *
     * By default keyboard navigation is disabled
     */
    void enableKeyboardNavigation(bool enable, const std::string& defaultButton = "");

protected:
    std::unique_ptr<gui::IView> m_view; //!< The scenes view
    std::string m_defaultFocusedButton; //!< The name of the default focused button

private:
    int m_keyboardNavHandler;           //!< The id number of the keyboard navigation handler
};

#endif //GALAXIAN_SCENE_H
