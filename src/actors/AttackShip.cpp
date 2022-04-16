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

#include "AttackShip.h"
#include "Bullet.h"
#include <IME/graphics/Window.h>

///////////////////////////////////////////////////////////////
AttackShip::AttackShip(ime::Scene &scene, Origin origin, bool rapidShooter, double firePower) :
    Ship(scene, origin),
    m_isRapidShooter(rapidShooter),
    m_bulletFirePower(firePower),
    m_isFireSuspended(false)
{

}

///////////////////////////////////////////////////////////////
std::unique_ptr<Bullet> AttackShip::fireBullet(const ime::Vector2f& velocity) {
    if (m_isFireSuspended)
        return nullptr;

    std::unique_ptr<Bullet> bullet = std::make_unique<Bullet>(getScene(), m_bulletFirePower);
    bullet->setShooter(this);
    bullet->getTransform().setPosition(getTransform().getPosition());
    bullet->getRigidBody()->setLinearVelocity(velocity);

    // Deactivate the bullet when it leaves the window
    bullet->onPropertyChange("position", [this, b = bullet.get()](const ime::Property& property) {
        static ime::Vector2u winSize = getScene().getWindow().getSize();
        auto position = property.getValue<ime::Vector2f>();

        if (position.y < 0.0f || position.y > winSize.y)
            b->setActive(false);
    });

    if (!m_isRapidShooter) {
        m_isFireSuspended = true;
        bullet->onDestruction([this] {
            m_isFireSuspended = false;
            onReload();
        });
    }

    // Prevent the bullet from colliding with the ship that fired it. This
    // will also prevent the bullet from colliding with ships of the same
    // kind as the shooter ship. For example, a bullet fired by a galaxian
    // ship will not collide with other galaxian ships
    ime::CollisionFilterData bulletCollisionFilter = bullet->getCollider()->getCollisionFilterData();
    bulletCollisionFilter.collisionBitMask &= ~getCollider()->getCollisionFilterData().categoryBitMask;
    bullet->setCollisionFilter(bulletCollisionFilter.categoryBitMask, bulletCollisionFilter.collisionBitMask);

    onFire();

    return bullet;
}

///////////////////////////////////////////////////////////////
bool AttackShip::isFiringSuspended() const {
    return m_isFireSuspended;
}

///////////////////////////////////////////////////////////////
std::string AttackShip::getClassName() const {
    return "AttackShip";
}
