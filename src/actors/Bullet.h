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

#ifndef GALAXIAN_BULLET_H
#define GALAXIAN_BULLET_H

#include "Actor.h"

class Ship;
class AttackShip;

/**
 * @brief A projectile that can e fired by an AttackShip to launch an attack
 *        against other ships
 */
class Bullet : public Actor {
public:
    /**
     * @brief The default strength of a bullet
     */
    static constexpr double DEFAULT_STRENGTH = 100.0;

    /**
     * @brief Constructor
     * @param scene The scene the bullet belongs to
     * @param strength The strength of the bullet
     *
     * The strength of the bullet represents the amount of damage inflicted
     * on a ship when it is hit
     *
     * @see getStrength
     */
    explicit Bullet(ime::Scene& scene, double strength = DEFAULT_STRENGTH);

    /**
     * @brief Get the strength of the bullet
     * @return The strength of the bullet
     *
     * The strength of the bullet represents the amount of damage inflicted
     * on a ship when it is hit
     */
    double getStrength() const;

    /**
     * @brief Set the shooter of the bullet
     * @param shooter The shooter of the bullet
     *
     * @note Once a bullet is assigned a shooter, it is considered fired
     * and hence the shooter cannot be reassigned
     *
     * By default, the shooter is nullptr
     *
     * @see getShooter
     */
    void setShooter(AttackShip* shooter);

    /**
     * @brief Get the ship that fired this bullet
     * @return The ship that fired the bullet or nullptr if the bullet is
     *         not yet fired or the ship that fired the bullet is no longer
     *         accessible (i.e was destroyed)
     *
     * By default, the victim is nullptr
     *
     * @see getVictim
     */
    AttackShip* getShooter();
    const AttackShip* getShooter() const;

    /**
     * @brief Set the ship that was hit by the bullet
     * @param victim The ship hit by the bullet
     *
     * This function will inflict damage on the victim ship and reduce its
     * health by the power of the bullet. In addition, the bullet will
     * be deactivated
     *
     * @note A bullet can only strike one victim at a time, hence the victim
     * cannot be reassigned once assigned
     *
     * @see getVictim
     */
    void setVictim(Ship* victim);

    /**
     * @brief Get the ship hit by the bullet
     * @return The ship hit by the bullet or nullptr if the bullet did not
     *         hit any ships
     *
     * @see getShooter
     */
    Ship* getVictim();
    const Ship* getVictim() const;

    /**
     * @brief Check if the bullet is fired or not
     * @return True if fired, false otherwise
     *
     * @see setShooter
     */
    bool isFired() const;

    /**
     * @brief Get the name of the class
     * @return The name of the class as declared
     */
    std::string getClassName() const override;

    /**
     * @brief Destructor
     */
    ~Bullet();

private:
    double m_strength;      //!< The strength of the bullet
    bool m_isFired;         //!< A flag indicating whether or not the bullet is fired
    AttackShip* m_shooter;  //!< The shooter of the bullet
    Ship* m_victim;         //!< The ship hit by the bullet
};

#endif //GALAXIAN_BULLET_H
