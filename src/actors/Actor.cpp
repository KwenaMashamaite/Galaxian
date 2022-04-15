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

#include "Actor.h"
#include <IME/core/physics/rigid_body/PhysicsEngine.h>
#include <IME/core/physics/rigid_body/colliders/BoxCollider.h>

///////////////////////////////////////////////////////////////
Actor::Actor(ime::Scene &scene) :
    ime::GameObject(scene),
    m_colliderId{-1}
{
    attachRigidBody(std::move(scene.getPhysicsEngine().createBody(ime::RigidBody::Type::Dynamic)));
}

///////////////////////////////////////////////////////////////
std::string Actor::getClassName() const {
    return "Actor";
}

///////////////////////////////////////////////////////////////
void Actor::attachCollider() {
    if (m_colliderId == -1) {
        ime::BoxCollider::Ptr collider = ime::BoxCollider::create(getSprite().getGlobalBounds().getSize());
        m_colliderId = collider->getObjectId();
        getRigidBody()->attachCollider(std::move(collider));
    }
}

///////////////////////////////////////////////////////////////
ime::Collider* Actor::getCollider() {
    return getRigidBody()->getColliderById(m_colliderId);
}

///////////////////////////////////////////////////////////////
const ime::Collider* Actor::getCollider() const {
    return getRigidBody()->getColliderById(m_colliderId);
}

///////////////////////////////////////////////////////////////
void Actor::setTexture(const std::string &texture, const ime::UIntRect &rect) {
    getSprite().setTexture(texture);
    getSprite().setTextureRect(rect);
    resetSpriteOrigin();
    getTransform().scale(2.0f, 2.0f);
    attachCollider();
}

///////////////////////////////////////////////////////////////
void Actor::setCollisionFilter(ime::Uint16 category, ime::Uint16 mask) {
    ime::Collider* collider = getCollider();
    ime::CollisionFilterData filter = collider->getCollisionFilterData();

    filter.categoryBitMask = category;
    filter.collisionBitMask = mask;
    collider->setCollisionFilter(filter);
}

///////////////////////////////////////////////////////////////
Actor::~Actor() = default;