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
    AttackShip(scene, Ship::Origin::OuterSpace),
    m_isDiving(false),
    m_isInFormation(false),
    m_type(type)
{
    // Prevent collisions between galaxians
    setCollisionGroup("galaxians");
    getCollisionExcludeList().add(getCollisionGroup());
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