#pragma once
// ClayEngine
#include <Clay/Entity/Entity.h>
#include <Clay/Entity/Render/ModelRenderable.h>
#include <Clay/Graphics/LightSource.h>

namespace galaxy {
class SunEntity : public clay::Entity {
public:
    /**
     * @brief Construct a new Sun Entity
     *
     * @param scene Scene this sun is in
     */
    SunEntity(clay::Scene& scene);

    /** Destructor */
    ~SunEntity();

    /** Get radius */
    float getRadius() const;

    /**
     * @brief Set Radius
     *
     * @param radius new radius
     */
    void setRadius(float radius);

    /** Get color */
    glm::vec4 getColor() const;

    /**
     * @brief Set Color
     *
     * @param color new color
     */
    void setColor(const glm::vec4& color);

    /** Get the light source for this entity */
    clay::LightSource* getLightSource();

private:
    /** Radius of this entity*/
    float mRadius_ = 1;
    /** Pointer to this Renderable of this entity */
    clay::ModelRenderable* mpRenderable_ = nullptr;
    /** Light Source for this entity */
    clay::LightSource mLight_;
};
} // namespace galaxy