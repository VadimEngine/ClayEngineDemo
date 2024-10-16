#pragma once
// ClayEngine
#include <Clay/Application/CameraController.h>
#include <Clay/Application/Scene.h>
#include <Clay/Entity/Render/ModelRenderable.h>
#include <Clay/Entity/Render/SpriteRenderable.h>
#include <Clay/Entity/Render/TextRenderable.h>
#include <Clay/Graphics/Shader.h>
#include <Clay/Graphics/Texture.h>
// project
#include "Scenes/Basic/BasicSceneGUI.h"

namespace basic_scene {
class BasicScene : public clay::Scene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    BasicScene(clay::App& theApp);

    /** Destructor */
    ~BasicScene();

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
    BasicSceneGUI mGui_;
    /** Entities rendered in this Scene */
    std::vector<std::unique_ptr<clay::Entity>> mEntities_;
    /** First Sprite used in this Scene*/
    clay::SpriteSheet::Sprite mSprite_;
};
} // namespace basic_scene