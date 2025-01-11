// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
#include <clay/application/common/BaseScene.h>
// class
#include "Scenes/Games/RPG2D/MOB.h"

namespace rpg_2d {
MOB::MOB(clay::BaseScene& scene)
: clay::Entity(scene), mSprite_(*mScene_.getApp().getResources().getResource<clay::SpriteSheet>("SpriteSheet1"), {0,0}) {
    addRenderable(new clay::SpriteRenderable(&mSprite_));
    mpCollider_ = addPhysicsComponent<clay::Collider2>();
    mpCollider_->setShape(clay::Collider2::Shape::RECTANGLE);
    // mpCollider_->addOnCollisionEnterCallback(separateFromMOB);
    // collider shape is 1x1x1
    mpBoxCollider_ = addPhysicsComponent<clay::BoxCollider2D>();
}

MOB::~MOB() {}

void MOB::update(float dt) {
    Entity::update(dt);
    mpCollider_->setPosition(mPosition_);
}

void MOB::move(glm::vec3 direction, float dt) {
    setPosition(getPosition() + direction * speed * dt);
}

clay::Collider2& MOB::getCollider() {
    return *mpCollider_;
}

clay::Collider& MOB::getColliderNew() {
    return *mpBoxCollider_;
}

} // namespace rpg_2d