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

#include "Escort.h"
#include "Flagship.h"

#include <cassert>

///////////////////////////////////////////////////////////////
Escort::Escort(ime::Scene &scene) :
    Galaxian(scene, Galaxian::Type::Escort),
    m_flagship(nullptr)
{

}

///////////////////////////////////////////////////////////////
bool Escort::isEscorting() const {
    return m_flagship != nullptr;
}

///////////////////////////////////////////////////////////////
void Escort::setFlagship(Flagship *flagship) {
    assert(flagship);

    if (isActive() && m_isInFormation && flagship->isActive() && flagship->isInFormation()) {
        m_flagship = flagship;
        m_flagship->onDestruction([this] { m_flagship = nullptr; });
    }
}

///////////////////////////////////////////////////////////////
Flagship *Escort::flagship() {
    return m_flagship;
}

///////////////////////////////////////////////////////////////
const Flagship *Escort::flagship() const {
    return m_flagship;
}

///////////////////////////////////////////////////////////////
std::string Escort::getClassName() const {
    return "Escort";
}