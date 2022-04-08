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

#include "Utils.h"
#include <ctime>

///////////////////////////////////////////////////////////////
std::string convertToMonth(int month) {
    switch (month) {
        case 1:     return "January";
        case 2:     return "February";
        case 3:     return "March";
        case 4:     return "April";
        case 5:     return "May";
        case 6:     return "June";
        case 7:     return "July";
        case 8:     return "August";
        case 9:     return "September";
        case 10:    return "October";
        case 11:    return "November";
        case 12:    return "December";
        default:
            return "Invalid";
    }
}

namespace util {
    ///////////////////////////////////////////////////////////////
    std::string getDate() {
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        return std::to_string(now->tm_mday) + " " + convertToMonth(now->tm_mon + 1) + " " + std::to_string(now->tm_year + 1900);
    }

    ///////////////////////////////////////////////////////////////
    ime::ui::Button::Ptr createButton(const std::string& name, const std::string& text) {
        auto btn = ime::ui::Button::create(text);
        btn->setName(name);
        btn->setTextSize(14.0f);

        ime::ui::ButtonRenderer* renderer = btn->getRenderer();
        renderer->setRoundedBorderRadius(20);
        renderer->setHoverTextStyle(ime::TextStyle::Italic);
        renderer->setBackgroundColour(ime::Colour::Transparent);
        renderer->setBackgroundHoverColour(ime::Colour::Transparent);
        renderer->setBackgroundColourDown(ime::Colour::Transparent);
        renderer->setTextColour(ime::Colour("#808080"));
        renderer->setTextHoverColour(ime::Colour::White);
        renderer->setBorderColour(ime::Colour::Transparent);
        renderer->setFocusedBorderColour(ime::Colour::Transparent);
        renderer->setBorderHoverColour(ime::Colour::Transparent);
        renderer->setFocusedBorderColour(ime::Colour::Transparent);
        renderer->setBorderColourOnMouseDown(ime::Colour::Transparent);

        return btn;
    }
}
