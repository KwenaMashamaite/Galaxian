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

///////////////////////////////////////////////////////////////
AttackShip::AttackShip(ime::Scene &scene, Origin origin, double firePower) :
    Ship(scene, origin),
    m_bulletFirePower(firePower),
    m_isFireSuspended(false)
{

}

///////////////////////////////////////////////////////////////
std::unique_ptr<Bullet> AttackShip::fireBullet() {
    std::unique_ptr<Bullet> bullet;

    if (!m_isFireSuspended) {
        m_isFireSuspended = true;

        bullet = std::make_unique<Bullet>(getScene(), m_bulletFirePower);
        bullet->setShooter(this);

        // Prevent friendly fire. That is, prevent bullets fired by a galaxian
        // from shooting another galaxian and so on...
        bullet->getCollisionExcludeList().add(getCollisionGroup());

        bullet->onDestruction([this] {
            m_isFireSuspended = false;
        });
    }

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
