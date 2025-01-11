// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// class
#include "Scenes/Lighting/LightEntity.h"

namespace lighting_scene {
LightEntity::LightEntity(clay::BaseScene& scene)
: clay::Entity(scene), mLightSource_(clay::LightSource::Type::Point) {
    mpRenderable_ = new clay::ModelRenderable(
        mScene_.getResources().getResource<clay::Model>("Sphere"),
        mScene_.getApp().getResources().getResource<clay::ShaderProgram>("Assimp")
    );
    addRenderable(mpRenderable_);
}

void LightEntity::setPosition(const glm::vec3& newPosition) {
    Entity::setPosition(newPosition);
    mLightSource_.setPosition(newPosition);
}

void LightEntity::setColor(glm::vec4 newColor) {
    mpRenderable_->setColor(newColor);
    mLightSource_.setColor(newColor);
}


clay::LightSource* LightEntity::getLightSource() {
    return &mLightSource_;
}

glm::vec4 LightEntity::getColor() const {
    return mLightSource_.getColor();
}

}// namespace lighting_scene