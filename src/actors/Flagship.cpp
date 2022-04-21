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

#include "Flagship.h"
#include "Escort.h"
#include "CollisionFiltering.h"
#include <cassert>
#include <iostream>

///////////////////////////////////////////////////////////////
Flagship::Flagship(ime::Scene &scene) :
    Galaxian(scene, Galaxian::Type::Flagship),
    m_hadEscorts(false)
{
    setTexture("objects-spritesheet.png", ime::UIntRect{3, 3, 11, 11});
    getSprite().scale(1.3f, 1.3f);
    setCollisionFilter(collision::CATEGORY_GALAXIAN, collision::MASK_GALAXIAN);
}

///////////////////////////////////////////////////////////////
bool Flagship::addEscort(Escort *escort) {
    assert(escort);

    if (isInFormation() && getEscortCount() < getMaxNumEscorts()) {
        m_hadEscorts = true;
        m_escorts.push_back(escort);
        escort->setFlagship(this);
        escort->onDestruction([escort, this] { removeEscort(escort); });

        return true;
    }

    return false;
}

///////////////////////////////////////////////////////////////
void Flagship::removeEscort(Escort *escort) {
    assert(escort);

    m_escorts.erase(std::remove_if(m_escorts.begin(), m_escorts.end(), [escort](Escort* esc) {
        return escort == esc;
    }), m_escorts.end());
}

///////////////////////////////////////////////////////////////
std::vector<Escort*> Flagship::getEscorts() const {
    return m_escorts;
}

///////////////////////////////////////////////////////////////
unsigned int Flagship::getEscortCount() const {
    return m_escorts.size();
}

///////////////////////////////////////////////////////////////
bool Flagship::isEscortedBy(Escort *escort) const {
    assert(escort);

    return std::any_of(m_escorts.begin(), m_escorts.begin(), [escort](Escort* esc) {
        return escort == esc;
    });
}

///////////////////////////////////////////////////////////////
bool Flagship::isEscorted() const {
    return !m_escorts.empty();
}

///////////////////////////////////////////////////////////////
bool Flagship::hadEscorts() const {
    return m_hadEscorts;
}


///////////////////////////////////////////////////////////////
unsigned int Flagship::getMaxNumEscorts() {
    return 2;
}

///////////////////////////////////////////////////////////////
int Flagship::getPoints() const {
    if (m_isInFormation)
        return 60;
    else {
        switch (getEscortCount()) {
            case 0:
                if (m_hadEscorts)   // Both escorts destroyed before the flagship
                    return 800;
                else
                    return 150;     // Flagship attacked alone
            case 1:
                return 200;
            case 2:
                return 300;
            default:
                std::cerr << "Error: Flagship has more that two escorts" << "\n";
                exit(-1);
        }
    }
}

///////////////////////////////////////////////////////////////
std::string Flagship::getClassName() const {
    return "Flagship";
}

///////////////////////////////////////////////////////////////
void Flagship::dive(float deltaTime) {

}
