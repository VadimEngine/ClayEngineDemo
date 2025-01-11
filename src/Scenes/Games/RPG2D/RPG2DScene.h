#pragma once
// ClayEngine
#include <clay/application/common/BaseScene.h>
// project
#include "Scenes/Games/RPG2D/RPG2DGame.h"
#include "Scenes/Games/RPG2D/RPG2DSceneGUI.h"

namespace rpg_2d {
class RPG2DScene : public clay::BaseScene {

public:
    RPG2DScene(clay::IApp& theApp);

    /** Destructor */
    ~RPG2DScene();

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
    void onKeyPress(unsigned int code) override;

    /**
     * On keyboard key release handler
     * @param newColor key code for released key
     */
    void onKeyRelease(unsigned int code) override;

    void onMousePress(const clay::IInputHandler::MouseEvent& mouseEvent);
private:
    RPG2DSceneGUI mGui_;

    RPG2DGame mGame_;
};

} // namespace rpg_2d 