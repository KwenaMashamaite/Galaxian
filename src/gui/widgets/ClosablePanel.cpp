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

#include "ClosablePanel.h"
#include <IME/ui/widgets/Button.h>

namespace gui {
    ///////////////////////////////////////////////////////////////
    ClosablePanel::ClosablePanel(const std::string& width, const std::string& height) :
        ime::ui::Panel(*ime::ui::Panel::create(width, height)),
        m_closeBtnName("btnClosablePanelClose")
    {
        // Default look
        getRenderer()->setBackgroundColour(ime::Colour::Black);
        getRenderer()->setBackgroundColour(ime::Colour("#000000BA"));
        getRenderer()->setRoundedBorderRadius(8.0f);
        
        // Panel close button
        auto btnClose = ime::ui::Button::create("x");
        btnClose->setName(m_closeBtnName);
        btnClose->setOrigin(1.0f, 0.0f);
        btnClose->setPosition("100%", "0%");
        btnClose->getRenderer()->setTextColour(ime::Colour::White);
        btnClose->getRenderer()->setBackgroundColour(ime::Colour::Transparent);
        btnClose->getRenderer()->setBorderColour(ime::Colour::Transparent);
        btnClose->getRenderer()->setFocusedBorderColour(ime::Colour::Transparent);
        btnClose->getRenderer()->setBorderHoverColour(ime::Colour::Transparent);
        btnClose->getRenderer()->setFocusedBorderColour(ime::Colour::Transparent);
        btnClose->getRenderer()->setBorderColourOnMouseDown(ime::Colour::Transparent);
        btnClose->on("click", ime::Callback<>([this] { setVisible(false); }));
        addWidget(std::move(btnClose));
    }

    ///////////////////////////////////////////////////////////////
    void ClosablePanel::close() {
        getWidget(m_closeBtnName)->emit("click");
    }

    ///////////////////////////////////////////////////////////////
    void ClosablePanel::onClose(const ime::Callback<>& callback) {
        getWidget(m_closeBtnName)->on("click", callback);
    }
}
