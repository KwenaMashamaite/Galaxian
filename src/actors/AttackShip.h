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

#ifndef GALAXIAN_ATTACKSHIP_H
#define GALAXIAN_ATTACKSHIP_H

#include "Ship.h"
#include "Bullet.h"

#include <memory>

/**
 * @brief A base class for all ships that can fire a projectile
 */
class AttackShip : public Ship {
public:
    /**
     * @brief Constructor
     * @param scene The scene the ship belongs to
     * @param origin The ships origin
     * @param firePower The bullet fire power of the ship
     *
     * The bullet fire power indicates the amount of damage inflicted on
     * other ships by bullets fired by this ship
     */
    explicit AttackShip(ime::Scene& scene, Origin origin, double firePower = Bullet::DEFAULT_STRENGTH);

    /**
     * @brief Fire a bullet
     * @param velocity The velocity of the bullet
     * @return The fired bullet or nullptr if firing is suspended
     *
     * @note The ship won't be able to fire another bullet until the returned
     * bullet is destroyed. This can happen when the bullet leaves the game
     * window or hits another ship. In other words, the ship can only fire one
     * bullet at a time
     *
     * @see isFiringSuspended
     */
    std::unique_ptr<Bullet> fireBullet(const ime::Vector2f& velocity);

    /**
     * @brief Check if the ship can fire a bullet or not
     * @return True if cannot fire a bullet, false otherwise
     *
     * @see fireBullet
     */
    bool isFiringSuspended() const;

    /**
     * @brief Get the name of the class
     * @return The name of the class as declared
     */
    std::string getClassName() const override;

private:
    double m_bulletFirePower;   //!< The power of the bullet fired by this ship
    bool m_isFireSuspended;     //!< A flag indicating whether or not the ship can fire a bullet
};

#endif //GALAXIAN_ATTACKSHIP_H
