#pragma once
// ClayEngine
#include <Clay/Application/CameraController.h>
#include <Clay/Application/Scene.h>
#include <Clay/Entity/Entity.h>
#include <Clay/Entity/Render/ModelRenderable.h>
#include <Clay/Entity/Render/SpriteRenderable.h>
#include <Clay/Graphics/Shader.h>
#include <Clay/Graphics/Texture.h>
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