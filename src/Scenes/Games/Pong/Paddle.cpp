// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// project
#include "Scenes/Games/Pong/PongScene.h"
// class
#include "Scenes/Games/Pong/Paddle.h"

namespace pong {
Paddle::Paddle(clay::BaseScene& scene, glm::vec2 dimension)
: clay::Entity(scene) {
    addRenderable(new clay::ModelRenderable(
        mScene_.getResources().getResource<clay::Model>("RectPlane"),
        mScene_.getApp().getResources().getResource<clay::ShaderProgram>("Assimp")
    ));
    setPosition(mDefaultPos_);
    setScale({dimension.x, dimension.y, 1});
    clay::RigidBodyComponent* rigid1 = addPhysicsComponent<clay::RigidBodyComponent>();
    rigid1->getCollider().setShape(clay::ColliderOLD::Shape::RECTANGLE);
    // not mobile in collisions
    rigid1->setMobile(false);
}

Paddle::~Paddle() {}

void Paddle::update(float dt) {
    Entity::update(dt);
    // keep paddle in bound
    float upperBound = ((PongScene&)mScene_).getGame().getBoardSize().y/2;
    float lowerBound = -upperBound;
    float height = getScale().y/2;

    if (mPosition_.y > upperBound - height/2) {
        mPosition_.y = upperBound - height/2;
    } else if (mPosition_.y < lowerBound + height/2) {
        mPosition_.y = lowerBound + height/2;
    }
}

void Paddle::reset() {
    setPosition(mDefaultPos_);
}

void Paddle::moveUp(float dt) {
    mPosition_.y += mMovementSpeed_ * dt;
}

void Paddle::moveDown(float dt) {
    mPosition_.y -= mMovementSpeed_ * dt;
}

void Paddle::setDefaultPosition(glm::vec2 newPosition) {
    mDefaultPos_ = {newPosition.x, newPosition.y, 0};
}

} // namespace pong