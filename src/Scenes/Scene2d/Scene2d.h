#pragma once
// ClayEngine
#include <clay/application/desktop/CameraController.h>
#include <clay/application/common/BaseScene.h>
#include <clay/entity/render/TextRenderable.h>
#include <clay/graphics/common/ShaderProgram.h>
#include <clay/graphics/common/SpriteSheet.h>
#include <clay/graphics/common/Texture.h>
// project
#include "Scenes/Scene2d/Scene2dGUI.h"

namespace scene_2d {
class Scene2d : public clay::BaseScene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    Scene2d(clay::AppDesktop& theApp);

    /** Destructor */
    ~Scene2d();

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

    /** Build/load resources for this scene */
    void assembleResources() override;

    /** get the entities in this scene*/
    std::vector<std::unique_ptr<clay::Entity>>& getEntities();

private:
    /** Camera Controller */
    clay::CameraController mCameraController_;
    /** GUI for this Scene*/
    Scene2dGUI mGui_;
    /** Entities rendered in this Scene */
    std::vector<std::unique_ptr<clay::Entity>> mEntities_;
    /** First Sprite used in this Scene*/
    clay::SpriteSheet::Sprite mSprite1_;
    /** Second Sprite used in this Scene*/
    clay::SpriteSheet::Sprite mSprite2_;
};
} // namespace scene_2d