#pragma once
// ClayEngine
#include <Clay/Application/Scene.h>
// project
#include "Scenes/Games/Pong/PongGame.h"
#include "Scenes/Games/Pong/PongSceneGUI.h"

namespace pong {
class PongScene : public clay::Scene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    PongScene(clay::App& theApp);

    /** Destructor */
    ~PongScene();

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

    /**
     * On keyboard key press handler
     * @param newColor key code for pressed key
     */
    void onKeyPress(unsigned int code) override;

    /**
     * On keyboard key release handler
     * @param newColor key code for released key
     */
    void onKeyRelease(unsigned int code) override;

    /**
     * @brief Get the game this scene is handling
     */
    PongGame& getGame();

private:
    /** GUI for this Scene*/
    PongSceneGUI mGui_;
    /** Game logic handler */
    std::unique_ptr<PongGame> mpGame_;
};

} // namespace pong