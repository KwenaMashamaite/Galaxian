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

#include <cassert>

///////////////////////////////////////////////////////////////
Flagship::Flagship(ime::Scene &scene) :
    Galaxian(scene, Galaxian::Type::Flagship)
{

}

///////////////////////////////////////////////////////////////
bool Flagship::addEscort(Escort *escort) {
    assert(escort);

    if (isInFormation() && getEscortCount() < getMaxNumEscorts()) {
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
unsigned int Flagship::getMaxNumEscorts() {
    return 2;
}

///////////////////////////////////////////////////////////////
std::string Flagship::getClassName() const {
    return "Flagship";
}
