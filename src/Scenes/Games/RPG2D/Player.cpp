// clay engine
#include <clay/application/App.h>
#include <clay/application/Scene.h>
// class
#include "Scenes/Games/RPG2D/Player.h"

namespace rpg_2d {

Player::Player(clay::Scene& scene)
: clay::Entity(scene), mSprite_(*mScene_.getApp().getResources().getResource<clay::SpriteSheet>("SpriteSheet1"), glm::ivec2(3, 0)) {
    addRenderable(new clay::SpriteRenderable(&mSprite_));
    mpCollider_ = addPhysicsComponent<clay::Collider2>();
    mpCollider_->setShape(clay::Collider2::Shape::RECTANGLE);
    mpCollider_->addOnCollisionEnterCallback(std::bind(&Player::separateFromMOB2, this, std::placeholders::_1, std::placeholders::_2));
    // collider shape is 1x1x1
    mpBoxCollider_ = addPhysicsComponent<clay::BoxCollider2D>();

    mpBoxCollider_->addOnCollisionEnterCallback(std::bind(&Player::separateFromMOB, this, std::placeholders::_1, std::placeholders::_2));
}

Player::~Player() {}

void Player::update(float dt) {
    Entity::update(dt);
    mpCollider_->setPosition(mPosition_);

    // TODO have collider's position match the parent Entity
}

void Player::render(const clay::Renderer& theRenderer) const {
    Entity::render(theRenderer);
    // mpCollider_->render(theRenderer, theCamera);
    mpBoxCollider_->render(theRenderer);
}

void Player::move(glm::vec3 direction, float dt) {
    setPosition(getPosition() + direction * speed * dt);
}

clay::Collider2& Player::getCollider() {
    return *mpCollider_;
}

clay::Collider& Player::getColliderNew() {
    return *mpBoxCollider_;
}

void Player::separateFromMOB2(clay::Collider2& thisCollider, clay::Collider2& otherCollider) {
    LOG_I("Player Collide2");

    // get MTV and separate
    auto theMVT = thisCollider.getCollisionMVT(&otherCollider);

    LOG_I("MTV %.2f, %.2f, %.2f", theMVT.value().x, theMVT.value().y, theMVT.value().z);

    setPosition(getPosition() + theMVT.value());
    otherCollider.getEntity().setPosition(otherCollider.getEntity().getPosition() - theMVT.value());
}

void Player::separateFromMOB(clay::Collider& thisCollider, clay::Collider& otherCollider) {
    LOG_I("Player Collide");

    auto mvt = thisCollider.getCollisionMTV(otherCollider);

    if (mvt.has_value()) {
        mPosition_ += mvt.value();
    }

    // get MTV and separate
    //auto theMVT = thisCollider.getCollisionMVT(&otherCollider);

    //LOG_I("MTV %.2f, %.2f, %.2f", theMVT.value().x, theMVT.value().y, theMVT.value().z);

    //setPosition(getPosition() + theMVT.value());
    //otherCollider.getEntity().setPosition(otherCollider.getEntity().getPosition() - theMVT.value());
}

} // namespace rpg_2d