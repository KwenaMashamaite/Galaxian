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

#ifndef GALAXIAN_ACTOR_H
#define GALAXIAN_ACTOR_H

#include <IME/core/scene/Scene.h>
#include <IME/core/object/GameObject.h>
#include <IME/core/physics/rigid_body/RigidBody.h>
#include <IME/core/physics/rigid_body/colliders/Collider.h>
#include <string>

/**
 * @brief A base class for all actors in the game
 */
class Actor : public ime::GameObject {
public:
    /**
     * @brief Constructor
     * @param scene The scene the actor belongs to
     */
    explicit Actor(ime::Scene& scene);

    /**
     * @brief Get the name of the class
     * @return The name of the class as declared
     */
    std::string getClassName() const override;

    /**
     * @brief Get the actors collider
     * @return The actors collider
     */
    ime::Collider* getCollider();
    const ime::Collider* getCollider() const;

    /**
     * @brief Set the texture of the actor
     * @param texture Filename of the texture
     * @param rect The sub rectangle to display
     * @throws ime::FileNotFoundException if the specified texture cannot
     *         be found
     */
    void setTexture(const std::string& texture, const ime::UIntRect& rect);

    /**
     * @brief Set the actors collision filter
     * @param category The collision category of the actor
     * @param mask The collision mask of the actor
     */
    void setCollisionFilter(ime::Uint16 category, ime::Uint16 musk);

    /**
     * @brief Destructor
     */
    virtual ~Actor() = 0;

private:
    /**
     * @brief Attach a ime::BoxCollider to the game object
     *
     * @note This function must be called after the objects sprite texture
     * is set as it uses the sprites bounds to determine the size of the
     * collider
     */
    void attachCollider();

private:
    int m_colliderId;    //!< The id of the collider attached to the actor
};

#endif //GALAXIAN_ACTOR_H
