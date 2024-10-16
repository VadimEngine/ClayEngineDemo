#pragma once
// ClayEngine
#include <Clay/Application/CameraController.h>
#include <Clay/Application/InputHandler.h>
#include <Clay/Graphics/Renderer.h>
// project
#include "Scenes/Games/RPG2D/MOB.h"
#include "Scenes/Games/RPG2D/Player.h"

namespace rpg_2d {
// forward declare Scene
class RPG2DScene;

class RPG2DGame {
public:
    RPG2DGame(RPG2DScene& scene, clay::Camera& focusCamera);

    ~RPG2DGame();

    /**
     * Update Game
     * @param dt Time since last update
     */
    void update(const float dt);

    /**
     * Render Game
     * @param renderer Rendering Renderer
     */
    void render(clay::Renderer& renderer);

    /**
     * Update the game based on key inputs
     * @param dt Time since last update
    */
    void handleKeyUpdate(float dt);

    /**
     * Update the game based on certain key pressed events
     * @param code Keycode of press key
     */
    void onKeyPress(unsigned int code);

    /**
     * Update the game based on certain key release events
     * @param code Keycode of released key
     */
    void onKeyRelease(unsigned int code);

    void onMousePress(const clay::InputHandler::MouseEvent& mouseEvent);

private:
    RPG2DScene& mScene_;

    Player thePlayer;

    MOB theMOB;

    clay::CameraController mCameraController_;

    clay::InputHandler& mInputHandler_;
};

} // namespace rpg_2d