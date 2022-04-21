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

#include "Emissary.h"
#include "CollisionFiltering.h"

///////////////////////////////////////////////////////////////
Emissary::Emissary(ime::Scene &scene) :
    Galaxian(scene, Galaxian::Type::Emissary)
{
    setTexture("objects-spritesheet.png", ime::UIntRect{3, 98, 11, 8});
    setCollisionFilter(collision::CATEGORY_GALAXIAN, collision::MASK_GALAXIAN);
}

///////////////////////////////////////////////////////////////
int Emissary::getPoints() const {
    if (m_isInFormation)
        return 40;
    else
        return 80;
}

///////////////////////////////////////////////////////////////
std::string Emissary::getClassName() const {
    return "Emissary";
}

///////////////////////////////////////////////////////////////
void Emissary::dive(float deltaTime) {

}
