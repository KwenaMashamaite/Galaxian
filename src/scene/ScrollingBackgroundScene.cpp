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

#include "ScrollingBackgroundScene.h"
#include <IME/graphics/Window.h>

///////////////////////////////////////////////////////////////
ScrollingBackgroundScene::ScrollingBackgroundScene() :
    m_speed(25)
{

}

///////////////////////////////////////////////////////////////
void ScrollingBackgroundScene::onEnter() {
    // Star field animation
    auto starFieldAnim = ime::Animation::create("starField", ime::SpriteSheet("starFieldSpriteSheet.png", {getWindow().getSize().x, getWindow().getSize().y}));
    starFieldAnim->addFrames(ime::Index{0, 0}, 10);
    starFieldAnim->setLoop(true);
    starFieldAnim->setFrameRate(8);

    // The first visible background that appears on the screen
    auto bg1 = std::make_unique<ime::Sprite>("starField.png");
    bg1->setTag("bg1");
    bg1->setOrigin(0.0f, bg1->getLocalBounds().height);
    bg1->setPosition(0.0f, getWindow().getSize().y);
    bg1->getAnimator().addAnimation(std::move(starFieldAnim));
    bg1->getAnimator().startAnimation("starField");

    // The background that appears after the first background disappears from the screen
    auto bg2 = std::make_unique<ime::Sprite>(*bg1);
    bg2->setPosition(bg1->getPosition().x, bg1->getPosition().y - bg1->getLocalBounds().height);
    m_bg2StartPos = bg2->getPosition();
    bg2->setTag("bg2");

    getSprites().add(std::move(bg1));
    getSprites().add(std::move(bg2));
}

///////////////////////////////////////////////////////////////
void ScrollingBackgroundScene::onFixedUpdate(ime::Time deltaTime) {
    update("bg1", deltaTime);
    update("bg2", deltaTime);
}

///////////////////////////////////////////////////////////////
void ScrollingBackgroundScene::update(const std::string &name, const ime::Time &deltaTime) {
    ime::Sprite* bg = getSprites().findByTag(name);

    bg->move(0.0f, m_speed * deltaTime.asSeconds());

    if (bg->getPosition().y >= 2 * bg->getLocalBounds().height)
        bg->setPosition(m_bg2StartPos.x, m_bg2StartPos.y);
}
