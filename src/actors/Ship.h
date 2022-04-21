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

#ifndef GALAXIAN_SHIP_H
#define GALAXIAN_SHIP_H

#include "Actor.h"

class Bullet;

/**
 * @brief Base class for all ships in the game
 */
class Ship : public Actor {
public:
    /**
     * @brief Defines where the ship came from
     */
    enum class Origin {
        Earth,       //!< An earth/player ship
        OuterSpace   //!< An alien/galaxian ship
    };

    /**
     * @brief The default health of a ship
     */
    static constexpr double DEFAULT_HEALTH = 100.0;

    /**
     * @brief Constructor
     * @param scene The scene the ship belongs to
     * @param origin The ships origin
     * @param health The health of the ship
     */
    Ship(ime::Scene& scene, Origin origin, double health = DEFAULT_HEALTH);

    /**
     * @brief Get the ships origin
     * @return The ships origin
     *
     * @see Ship::Origin
     */
    Origin getOrigin() const;

    /**
     * @brief Set the health of the ship
     * @param health The new health of the ship
     *
     * By default, the health is 100
     *
     * @see getHealth
     */
    void setHealth(double health);

    /**
     * @brief Get the health of the ship
     * @return The health of the ship
     *
     * @see setHealth
     */
    double getHeath() const;

    /**
     * @brief Check if the ship is blowing up or not
     * @return True if blowing up, false otherwise
     */
    bool isBlowingUp() const;

    /**
     * @brief Handle a collision with a bullet
     * @param bullet The bullet that hit the ship
     *
     * This function is called automatically when a ship becomes a victim
     * of the bullet
     *
     * By default, the function subtracts the bullets strength from the ships
     * health
     */
    virtual void onHitByBullet(Bullet& bullet);

private:
    double m_health;    //!< The current health of the ship
    Origin m_origin;    //!< The ships origin
};

#endif //GALAXIAN_SHIP_H
