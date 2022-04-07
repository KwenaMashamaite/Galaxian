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

#ifndef GALAXIAN_GALAXIAN_H
#define GALAXIAN_GALAXIAN_H

#include "IPointsAwarder.h"
#include "AttackShip.h"

/**
 * @brief A base class for all enemy ships
 */
class Galaxian : public AttackShip, public IPointsAwarder {
public:
    /**
     * @brief The type of galaxian
     */
    enum class Type {
        Flagship,   //!< Flagship galaxian
        Escort,     //!< Escort galaxian (red)
        Emissary,   //!< Emissary galaxian (purple)
        Drone       //!< Drone galaxian (blue)
    };

    /**
     * @brief Constructor
     * @param scene The scene the galaxian belongs to
     * @param type The type of galaxian
     */
    Galaxian(ime::Scene& scene, Type type);

    /**
     * @brief Get the type of the galaxian
     * @return The type of the galaxian
     */
    Type getType() const;

    /**
     * @brief Check if the galaxian is diving or not
     * @return True if diving, false otherwise
     *
     * By default, the galaxian is not diving
     *
     * @see isInFormation
     */
    bool isDiving() const;

    /**
     * @brief Check if the galaxian is in formation
     * @return True if it is in formation, false otherwise
     *
     * @see isDiving
     */
    bool isInFormation() const;

    /**
     * @brief Check if the galaxian is a Flagship
     * @return True if it is a flagship, false otherwise
     */
    bool isFlagship() const;

    /**
     * @brief Define the galaxians dive
     * @param deltaTime The time passed since the last dive
     *
     * @note This function is called automatically
     */
    virtual void dive(float deltaTime) = 0;

    /**
     * @brief Update the galaxian
     * @param deltaTime The time passed since the last update
     *
     * @note This function is called automatically by IME
     */
    void update(ime::Time deltaTime) final;

protected:
    bool m_isDiving;        //!< A flag indicating whether or not the galaxian is diving
    bool m_isInFormation;   //!< A flag indicating whether or not the galaxian is in formation

private:
    Type m_type;            //!< The type of the galaxian
};

#endif //GALAXIAN_GALAXIAN_H
