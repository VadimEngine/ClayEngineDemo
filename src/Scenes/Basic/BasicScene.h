#pragma once
// ClayEngine
#include <clay/application/desktop/CameraController.h>
#include <clay/application/common/BaseScene.h>
#include <clay/entity/render/ModelRenderable.h>
#include <clay/entity/render/SpriteRenderable.h>
#include <clay/entity/render/TextRenderable.h>
#include <clay/graphics/common/ShaderProgram.h>
#include <clay/graphics/common/Texture.h>
// project
#include "Scenes/Basic/BasicSceneGUI.h"

namespace basic_scene {
class BasicScene : public clay::BaseScene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    BasicScene(clay::IApp& theApp);

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

    void setHighLightEntity(clay::Entity* highlight);

private:
    /** Camera Controller */
    clay::CameraController mCameraController_;
    /** GUI for this Scene*/
    BasicSceneGUI mGui_;
    /** Entities rendered in this Scene */
    std::vector<std::unique_ptr<clay::Entity>> mEntities_;
    /** Sprite used in this Scene*/
    clay::SpriteSheet::Sprite mSprite_;

    clay::ShaderProgram* mHighlightShader_ = nullptr;

    clay::Entity* mHighlightEntity_ = nullptr;
};
} // namespace basic_scene