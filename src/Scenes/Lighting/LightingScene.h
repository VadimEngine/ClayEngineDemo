#pragma once
// project
// ClayEngine
#include <Clay/Application/CameraController.h>
#include <Clay/Application/Scene.h>
#include <Clay/Graphics/LightSource.h>
// project
#include "Scenes/Lighting/LightEntity.h"
#include "Scenes/Lighting/LightingSceneGUI.h"
#include "Scenes/Menu/MenuScene.h"

namespace lighting_scene {

class LightingScene : public clay::Scene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    LightingScene(clay::App& theApp);

    /** Destructor */
    ~LightingScene();

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

    /**
     * @brief Loads and builds resources that are used for this scene
     */
    void assembleResources() override;

    /** Get the entities in this scene*/
    std::vector<std::unique_ptr<clay::Entity>>& getEntities();

private:
    /** Camera Controller */
    clay::CameraController mCameraController_;
    /** GUI for this Scene*/
    LightingSceneGUI mGui_;

    // reference to the light entity in this scene
    LightEntity* mpLight_;

    /** Entities rendered in this Scene */
    std::vector<std::unique_ptr<clay::Entity>> mEntities_;
};
} // namespace lighting_scene