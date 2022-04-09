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

#include "Scene.h"
#include <cassert>

///////////////////////////////////////////////////////////////
void Scene::onInit() {
    assert(m_view);

    m_view->init(getGui());
}

///////////////////////////////////////////////////////////////
void Scene::onExit() {
    // This is a workaround, IME v3.1.0 does not reset the state
    // of the gui when transitioning to another scene. For instance,
    // if a button was hovered over in the pause menu and we exited
    // to the main menu. when we return to the pause menu again, the
    // button still has a hover state even though the mouse is not on
    // top of it

    // Reset focus state
    getGui().unfocusAllWidgets();

    // Reset hover state
    ime::Event event;
    event.type = ime::Event::MouseMoved;
    event.mouseMove.x = -9999;
    getGui().handleEvent(event);

    // Reset left mouse down state
    event.type = ime::Event::MouseButtonReleased;
    event.mouseButton.button = ime::input::Mouse::Button::Left;
    event.mouseButton.x = -9999;
    getGui().handleEvent(event);
}
