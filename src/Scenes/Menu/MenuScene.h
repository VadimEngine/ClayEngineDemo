#pragma once
// ClayEngine
#include <clay/application/Scene.h>
// project
#include "Scenes/Menu/MenuGUI.h"

namespace menu_scene {
class MenuScene : public clay::Scene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    MenuScene(clay::App& theApp);

    /** Destructor */
    ~MenuScene();

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
    /** GUI for this scene*/
    MenuGUI mGui_;
};
} // namespace menu_scene