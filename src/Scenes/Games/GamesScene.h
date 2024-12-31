#pragma once
// ClayEngine
#include <clay/application/CameraController.h>
#include <clay/application/Scene.h>
#include <clay/entity/Entity.h>
#include <clay/entity/render/ModelRenderable.h>
#include <clay/entity/render/SpriteRenderable.h>
#include <clay/graphics/common/Texture.h>
// project
#include "Scenes/Games/GamesSceneGUI.h"

class GamesScene : public clay::Scene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    GamesScene(clay::App& theApp);

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