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

#include "Galaxian.h"

///////////////////////////////////////////////////////////////
Galaxian::Galaxian(ime::Scene &scene, Type type) :
    AttackShip(scene, Ship::Origin::OuterSpace, true),
    m_isDiving(false),
    m_isInFormation(false),
    m_type(type)
{
    // Explosion animation
    auto explosionAnim = ime::Animation::create("explosion", ime::SpriteSheet("objects-spritesheet.png", {16, 16}, {1, 1}, {50, 213, 69, 18}));
    explosionAnim->addFrames(ime::Index{0, 0}, 4);
    explosionAnim->setDuration(ime::milliseconds(300));
    explosionAnim->onStart([this](ime::Animation*) { resetSpriteOrigin(); });
    explosionAnim->onComplete([this] (ime::Animation*) { setActive(false); });
    getSprite().getAnimator().addAnimation(std::move(explosionAnim));
}

///////////////////////////////////////////////////////////////
Galaxian::Type Galaxian::getType() const {
    return m_type;
}

///////////////////////////////////////////////////////////////
bool Galaxian::isDiving() const {
    return m_isDiving;
}

///////////////////////////////////////////////////////////////
bool Galaxian::isInFormation() const {
    return m_isInFormation;
}

///////////////////////////////////////////////////////////////
bool Galaxian::isFlagship() const {
    return m_type == Type::Flagship;
}

///////////////////////////////////////////////////////////////
void Galaxian::update(ime::Time deltaTime) {
    dive(deltaTime.asSeconds());
}

///////////////////////////////////////////////////////////////
void Galaxian::setDefaultAnimation(const ime::UIntRect &rect) {
    auto defAnim = ime::Animation::create("formation", ime::SpriteSheet("objects-spritesheet.png", {16, 8}, {1, 1}, rect));
    defAnim->addFrames(ime::Index{0, 0}, 4);
    defAnim->onStart([this] (ime::Animation*) { resetSpriteOrigin(); });
    defAnim->setDuration(ime::milliseconds(800));
    defAnim->setLoop(true);
    getSprite().getAnimator().addAnimation(std::move(defAnim));
    getSprite().getAnimator().startAnimation("formation");
    resetSpriteOrigin();
}
