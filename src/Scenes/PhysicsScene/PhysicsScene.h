#pragma once
// standard lib
#include <optional>
// third party
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
// ClayEngine
#include <clay/application/CameraController.h>
#include <clay/application/Scene.h>
#include <clay/entity/physics/RigidBodyComponent.h>
#include <clay/entity/render/ModelRenderable.h>
// project
#include "Scenes/PhysicsScene/PhysicsSceneGUI.h"

namespace physics_scene {
class PhysicsScene : public clay::Scene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    PhysicsScene(clay::App& theApp);

    /** Destructor */
    ~PhysicsScene();

    /**
     * Update the Scene
     * @param dt Time since last update in seconds
     */
    void update(const float dt) override;

    /**
     * Render this scene
     * @param renderer Rendering helper
     */
    void render(clay::Renderer& renderer) override;

    /**
     * Render just the gui for this scene
     */
    void renderGUI() override;

    /** get the entities in this scene*/
    std::vector<std::unique_ptr<clay::Entity>>& getEntities();

    /** Spawn an Entity*/
    void addEntity(const glm::vec3 position);

    /**
     * @brief Load/Build resources for this scene
     */
    void assembleResources() override;

private:
    /** Resolve collisions to avoid overlapping */
    void handleEntityOverlap();

    /** Check and enact collision actions between Entities */
    void handleEntityCollision(const float dt);

    /** Camera Controller */
    clay::CameraController mCameraController_;

    /** GUI for this Scene*/
    PhysicsSceneGUI mGui_;

    /** Entities rendered in this Scene */
    std::vector<std::unique_ptr<clay::Entity>> mEntities_;
};

} // namespace physics_scene 