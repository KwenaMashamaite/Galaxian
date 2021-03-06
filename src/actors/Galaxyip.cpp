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

#include "Galaxyip.h"
#include "CollisionFiltering.h"

///////////////////////////////////////////////////////////////
Galaxyip::Galaxyip(ime::Scene &scene) :
    AttackShip(scene, Ship::Origin::Earth, false)
{
    setHealth(4 * Ship::DEFAULT_HEALTH);
    setTexture("objects-spritesheet.png", ime::UIntRect{2, 227, 13, 20});
    setCollisionFilter(collision::CATEGORY_PLAYER, collision::MASK_PLAYER);

    // Explosion
    auto explosionAnim = ime::Animation::create("explosion", ime::SpriteSheet("objects-spritesheet.png", {32, 32}, {1, 1}, {0, 247, 133, 34}));
    explosionAnim->addFrames(ime::Index{0, 0}, 4);
    explosionAnim->setDuration(ime::milliseconds(400));
    explosionAnim->onStart([this](ime::Animation*) { resetSpriteOrigin(); });
    explosionAnim->onComplete([this] (ime::Animation*) { setActive(false); });
    getSprite().getAnimator().addAnimation(std::move(explosionAnim));
}

///////////////////////////////////////////////////////////////
std::string Galaxyip::getClassName() const {
    return "Galaxyip";
}

///////////////////////////////////////////////////////////////
void Galaxyip::onFire() {
    getSprite().setTextureRect(ime::UIntRect{19, 231, 13, 16});
    resetSpriteOrigin();
}

///////////////////////////////////////////////////////////////
void Galaxyip::onReload() {
    getSprite().setTextureRect(ime::UIntRect{2, 227, 13, 20});
    resetSpriteOrigin();
}
