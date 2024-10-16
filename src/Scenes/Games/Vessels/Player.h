#pragma once
// standard lib
#include <string>
// ClayEngine
#include <Clay/Entity/Entity.h>

namespace vessels {

class VesselsGame;

class Player : public clay::Entity {
public:

    /**
     * @brief Construct a new Player object
     *
     * @param theGame game this player is in
     */
    Player(VesselsGame& theGame);

    /**
     * Update player
     * @param dt Time since last update
     */
    void update(const float dt) override;

    void render(const clay::Renderer& theRenderer) const override;

    void renderInMenu(const clay::Renderer& theRenderer, const glm::vec2& guiPosition, const glm::vec3& scale, const glm::vec3& rotation);

    glm::vec3 getForward();

    glm::vec3 getRight();

private:
    std::string mName_;
};

} // namespace vessels
