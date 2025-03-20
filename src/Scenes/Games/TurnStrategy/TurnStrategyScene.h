#pragma once
// ClayEngine
#include <clay/application/common/BaseScene.h>
// project
#include "Scenes/Games/TurnStrategy/TurnStrategyGame.h"
#include "Scenes/Games/TurnStrategy/TurnStrategyGUI.h"

namespace turn_strategy {
class TurnStrategyScene : public clay::BaseScene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    TurnStrategyScene(clay::IApp& theApp);

    /** Destructor */
    ~TurnStrategyScene();

    /** Load/build resources for this Scene */
    void assembleResources() override;

    /**
     * Update the Scene
     * @param dt Time since last update in seconds
     */
    void update(const float dt) override;

    /**
     * Render this scene
     * @param renderer Rendering helper
     */
    void render(clay::IGraphicsContext& gContext) override;

    /**
     * Render just the gui for this scene
     */
    void renderGUI() override;

    void onInputEvent(clay::InputEvent& e);

    /**
     * On keyboard key press handler
     * @param newColor key code for pressed key
     */
    void onKeyPress(unsigned int code);

    /**
     * On keyboard key release handler
     * @param newColor key code for released key
     */
    void onKeyRelease(unsigned int code);

    /**
     * On Mouse button press handler
     * @param mouseEvent Mouse event details
     */
    void onMousePress(const clay::MouseEvent& mouseEvent);

    /**
     * On Mouse Button release handler
     * @param mouseEvent Mouse event details
     */
    void onMouseRelease(const clay::MouseEvent& mouseEvent);

    /**
     * On wheel handler
     * @param mouseEvent Mouse event details
     */
    void onMouseWheel(const clay::MouseEvent& mouseEvent);

    /** Get reference to the game handler in this scene */
    TurnStrategyGame& getGame();

private:
    /** GUI for this scene */
    TurnStrategyGUI mGui_;
    /** Game logic handler */
    std::unique_ptr<TurnStrategyGame> mpGame_;
};

} // namespace turn_strategy