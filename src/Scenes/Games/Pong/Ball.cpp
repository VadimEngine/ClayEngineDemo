// forward declare
// ClayEngine
#include <Clay/Application/App.h>
// project
#include "Scenes/Games/Pong/PongScene.h"
// class
#include "Scenes/Games/Pong/Ball.h"

namespace pong {
Ball::Ball(clay::Scene& scene, float radius)
: clay::Entity(scene), mRadius_(radius) {
    addRenderable(new clay::ModelRenderable(
        mScene_.getResources().getResource<clay::Model>("CircularPlane"),
        mScene_.getApp().getResources().getResource<clay::Shader>("Assimp")
    ));
    mPosition_ = {0.f,0.f,0.f};
    mScale_ = {radius, radius, 1};
    clay::RigidBodyComponent* rigid3 = addPhysicsComponent<clay::RigidBodyComponent>();
    rigid3->getCollider().setShape(clay::ColliderOLD::Shape::CIRCLE);
}

Ball::~Ball() {}

void Ball::update(float dt) {
    Entity::update(dt);
    float boardHeight = ((PongScene&)(mScene_)).getGame().getBoardSize().y;

    // Bounce off top/bottom
    if (mPosition_.y < (-boardHeight/2 + mRadius_) || mPosition_.y > ((boardHeight/2 - mRadius_))) {
        glm::vec3 ballVel = getVelocity();
        ballVel.y *= -1;
        setVelocity(ballVel);
    }
}

void Ball::start(const glm::vec3& dir) {
    const float epsilon = 1e-6f;
    if (glm::length2(dir) > epsilon) {
        setVelocity(glm::normalize(dir) * mInitalBallSpeed_);
    } else {
        // if dir is zero, then set velocity to zero
        setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

float Ball::getSpeed() {
    return glm::length(mVelocity_);
}

void Ball::setSpeed(float newSpeed) {
    const float epsilon = 1e-6f;
    setVelocity(glm::normalize(mVelocity_) * newSpeed);
    if (glm::length2(mVelocity_) > epsilon) {
        setVelocity(glm::normalize(mVelocity_) * newSpeed);
    } else {
        // if velocity is zero, then set velocity to zero
        setVelocity(glm::vec3(0.0f, 0.0f, 0.0f));
    }
}

void Ball::reset() {
    setPosition({0,0,0});
    setVelocity({0,0,0});
}

} // namespace pong