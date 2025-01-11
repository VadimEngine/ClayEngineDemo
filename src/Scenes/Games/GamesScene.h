#pragma once
// ClayEngine
#include <clay/application/desktop/CameraController.h>
#include <clay/application/common/BaseScene.h>
#include <clay/entity/Entity.h>
#include <clay/entity/render/ModelRenderable.h>
#include <clay/entity/render/SpriteRenderable.h>
#include <clay/graphics/common/Texture.h>
// project
#include "Scenes/Games/GamesSceneGUI.h"

class GamesScene : public clay::BaseScene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    GamesScene(clay::IApp& theApp);

    /** Destructor */
    ~GamesScene();

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

private:
    /** GUI for this Scene*/
    GamesSceneGUI mGui_;
};