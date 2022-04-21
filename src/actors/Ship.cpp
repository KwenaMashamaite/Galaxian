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

#include "Ship.h"
#include "Bullet.h"

///////////////////////////////////////////////////////////////
Ship::Ship(ime::Scene &scene, Origin origin, double health) :
    Actor(scene),
    m_health(health),
    m_origin(origin)
{

}

///////////////////////////////////////////////////////////////
Ship::Origin Ship::getOrigin() const {
    return m_origin;
}

///////////////////////////////////////////////////////////////
void Ship::setHealth(double health) {
    if (m_health != 0.0 && m_health != health) {
        m_health = health;

        if (m_health <= 0) {
            health = 0.0;

            if (ime::RigidBody* rigidBody = getRigidBody(); rigidBody)
                rigidBody->setLinearVelocity(ime::Vector2f(0.0f, 0.0f));

            getSprite().getAnimator().startAnimation("explosion");
        }

        emitChange(ime::Property{"health", m_health});
    }
}

///////////////////////////////////////////////////////////////
double Ship::getHeath() const {
    return m_health;
}

///////////////////////////////////////////////////////////////
bool Ship::isBlowingUp() const {
    ime::Animation::Ptr curAnim = getSprite().getAnimator().getActiveAnimation();

    return curAnim && curAnim->getName() == "explosion";
}

///////////////////////////////////////////////////////////////
void Ship::onHitByBullet(Bullet &bullet) {
    if (isActive())
        setHealth(m_health - bullet.getStrength());
}
