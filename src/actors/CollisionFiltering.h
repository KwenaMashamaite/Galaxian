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

#ifndef GALAXIAN_COLLISIONFILTERING_H
#define GALAXIAN_COLLISIONFILTERING_H

#include <IME/Config.h>

/**
 * @brief Defines which group of objects are allowed to collide
 */
namespace collision {
    // Collision categories
    const static inline ime::Uint16 CATEGORY_PLAYER = 0x0001;     // 1
    const static inline ime::Uint16 CATEGORY_GALAXIAN = 0x0002;   // 2
    const static inline ime::Uint16 CATEGORY_BULLET = 0x0004;     // 4
    const static inline ime::Uint16 CATEGORY_VERT_WIN_BORDER = 0x0008;     // 4

    // Collision masks
    const static inline ime::Uint16 MASK_GALAXIAN = CATEGORY_PLAYER | CATEGORY_BULLET; // A galaxian collides with the player and bullets but not with other galaxians
    const static inline ime::Uint16 MASK_PLAYER = CATEGORY_BULLET | CATEGORY_GALAXIAN | CATEGORY_VERT_WIN_BORDER;
    const static inline ime::Uint16 MASK_BULLET = CATEGORY_PLAYER | CATEGORY_GALAXIAN;
    const static inline ime::Uint16 MASK_VERT_WIN_BORDER = CATEGORY_PLAYER;
}

#endif