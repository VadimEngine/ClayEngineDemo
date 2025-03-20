// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// class
#include "Scenes/Galaxy/PlanetEntity.h"

namespace galaxy {
PlanetEntity::PlanetEntity(clay::BaseScene& scene)
    :Entity(scene) {
    mpRenderable_ = new clay::ModelRenderable(
        mScene_.getResources().getResource<clay::Model>("Torus"),
        mScene_.getApp().getResources().getResource<clay::ShaderProgram>("AssimpLight")
    );
    mpRenderable_->setScale({mRadius_, mRadius_, mRadius_});
    mpRenderable_->setOrientation(glm::angleAxis(glm::radians(20.0f), glm::vec3(0.0f, 0.0f, 1.0f)));

    mpRenderable_->setColor(0x00FF00FF);
    // Add Renderable to Entity
    addRenderable(mpRenderable_);
    setPosition({mOrbitRadius_, 0.f, 0.f});
}
PlanetEntity::~PlanetEntity() {}

float PlanetEntity::getRadius() const {
    return mRadius_;
}

void PlanetEntity::setRadius(float radius) {
    mRadius_ = radius;
    mpRenderable_->setScale({mRadius_, mRadius_, mRadius_});
}

glm::vec4 PlanetEntity::getColor() const {
    return mpRenderable_->getColor();
}

void PlanetEntity::setColor(const glm::vec4& color) {
    return mpRenderable_->setColor(color);
}

float PlanetEntity::getRotationSpeed() const {
    return mRotationSpeed_;
}

void PlanetEntity::setRotationSpeed(float rotation) {
    mRotationSpeed_ = rotation;
}

} // namespace galaxy