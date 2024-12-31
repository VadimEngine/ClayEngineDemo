#pragma once
// standard lib
#include <memory>
// ClayEngine
#include <clay/application/Scene.h>
// project
#include "Scenes/Games/Vessels/VesselsGame.h"
#include "Scenes/Games/Vessels/VesselsSceneGUI.h"

namespace vessels {
class VesselsScene : public clay::Scene {
public:
    VesselsScene(clay::App& theApp);

    /** Destructor */
    ~VesselsScene();

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
     * On keyboard key press handler
     * @param newColor key code for pressed key
     */
    void onMousePress(const clay::InputHandler::MouseEvent& mouseEvent) override;

    /**
     * @brief Loads and builds resources that are used for this scene
     */
    void assembleResources() override;

    VesselsGame& getGame();


private:
    VesselsSceneGUI mGui_;

    std::unique_ptr<VesselsGame> mpGame_;
};

} // namespace vessels