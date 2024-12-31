#pragma once
// ClayEngine
#include <clay/entity/Entity.h>
#include <clay/entity/render/ModelRenderable.h>
#include <clay/graphics/common/LightSource.h>

namespace lighting_scene {

class LightEntity : public clay::Entity {
public:
    LightEntity(clay::Scene& scene);

    clay::LightSource* getLightSource();

    void setPosition(const glm::vec3& newPosition) override;

    void setColor(glm::vec4 newColor);

    glm::vec4 getColor() const;

private:
    clay::ModelRenderable* mpRenderable_ = nullptr;
    clay::LightSource mLightSource_;
};

} // namespace lighting_scene