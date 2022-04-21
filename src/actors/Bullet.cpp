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

#include "Bullet.h"
#include "Ship.h"
#include "AttackShip.h"
#include "CollisionFiltering.h"
#include <cassert>

///////////////////////////////////////////////////////////////
Bullet::Bullet(ime::Scene &scene, double strength) :
    Actor(scene),
    m_isFired(false),
    m_strength(strength),
    m_shooter(nullptr),
    m_victim(nullptr)
{
    setTexture("objects-spritesheet.png", ime::UIntRect{89, 192, 1, 4});
    setCollisionFilter(collision::CATEGORY_BULLET, collision::MASK_BULLET);

    onRigidBodyCollisionStart([this](ime::GameObject* bullet, ime::GameObject* other) {
        Ship* ship = dynamic_cast<Ship*>(other);

        if (ship)
            setVictim(ship);
    });
}

///////////////////////////////////////////////////////////////
double Bullet::getStrength() const {
    return m_strength;
}

///////////////////////////////////////////////////////////////
void Bullet::setShooter(AttackShip *shooter) {
    assert(shooter);

    if (!m_isFired) {
        m_isFired = true;
        m_shooter = shooter;
        m_shooter->onDestruction([this] { m_shooter = nullptr; });
    }
}

///////////////////////////////////////////////////////////////
AttackShip *Bullet::getShooter() {
    return m_shooter;
}

///////////////////////////////////////////////////////////////
const AttackShip *Bullet::getShooter() const {
    return m_shooter;
}

///////////////////////////////////////////////////////////////
void Bullet::setVictim(Ship* victim) {
    assert(victim);

    if (isActive() && m_victim == nullptr) {
        m_victim = victim;
        m_victim->onDestruction([this] { m_victim = nullptr; });
        m_victim->onHitByBullet(*this);
        setActive(false);
    }
}

///////////////////////////////////////////////////////////////
Ship *Bullet::getVictim() {
    return m_victim;
}

///////////////////////////////////////////////////////////////
const Ship *Bullet::getVictim() const {
    return m_victim;
}

///////////////////////////////////////////////////////////////
bool Bullet::isFired() const {
    return m_isFired;
}

///////////////////////////////////////////////////////////////
std::string Bullet::getClassName() const {
    return "Bullet";
}

///////////////////////////////////////////////////////////////
Bullet::~Bullet() {
    emitDestruction();
}
