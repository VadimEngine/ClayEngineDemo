#pragma once
// standard lib
#include <vector>
// ClayEngine
#include <clay/application/desktop/InputHandlerDesktop.h>
#include <clay/application/desktop/CameraController.h>
#include <clay/entity/Entity.h>
// project
#include "Scenes/Games/Vessels/Cosmos.h"
#include "Scenes/Games/Vessels/Player.h"
#include "Scenes/Games/Vessels/Soul.h"

namespace vessels {
// forward declare Scene
class VesselsScene;

class VesselsGame {
public:

    enum class GameState {
        START, MENU_SETTINGS, SOUL_SELECT, COSMOS_SELECTION, CORPOREAL_REALM, SOUL_REALM
    };

    // game states to control the GUI

    VesselsGame(VesselsScene& scene);

    ~VesselsGame();

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
     * Update the game based on key inputs// TODO SHOULD THIS BE PRIVATE?
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

    GameState getGameState();

    VesselsScene& getScene();

    void setState(GameState newState);

private:
    VesselsScene& mScene_;
    // Player
    std::unique_ptr<Player> mpPlayer_;
    // Cosmos
    // Environment
    std::vector<std::unique_ptr<clay::Entity>> mEntities_;

    GameState mState_ = GameState::START;

    clay::InputHandlerDesktop& mInputHandler_;

    clay::CameraController mCameraController_;


};

} // namespace vessels