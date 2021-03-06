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

#ifndef GALAXIAN_GALAXIANFORMATION_H
#define GALAXIAN_GALAXIANFORMATION_H

#include <IME/core/scene/GameObjectContainer.h>
#include <IME/core/scene/Scene.h>

/**
 * @brief A formation of enemy ships
 */
class GalaxianFormation {
public:
    /**
     * @brief Constructor
     * @param scene The scene the enemy ships belongs to
     */
    explicit GalaxianFormation(ime::Scene& scene);

    /**
     * @brief Start moving the formation left and right
     *
     * The formation will move left until it collides with the window borders
     * at which point it moves right. Similarly, it will move right until it
     * collides with the window borders at which points its starts moving left
     *
     * By default, the formation moves in the left direction
     */
    void move();

private:
    ime::GameObjectContainer& m_objects;
    ime::Vector2i m_direction;
};

#endif //GALAXIAN_GALAXIANFORMATION_H
