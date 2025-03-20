// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// project
#include "Scenes/Games/Vessels/VesselsGame.h"
#include "Scenes/Games/Vessels/VesselsScene.h"
// class
#include "Scenes/Games/Vessels/Player.h"

namespace vessels {

Player::Player(VesselsGame& theGame)
: clay::Entity(theGame.getScene()) {}

void Player::update(const float dt) {
}

void Player::render(clay::IGraphicsContext& gContext) const {
    Entity::render(gContext);
}

void Player::renderInMenu(const clay::RendererOpenGL& theRenderer, const glm::vec2& guiPosition, const glm::vec3& scale, const glm::vec3& rotation) {}

glm::vec3 Player::getForward() {
    // Start with a default forward vector (looking down the negative Z-axis)
    glm::vec3 forward = glm::vec3(0.0f, 0.0f, -1.0f);

    forward = mOrientation_ * forward;

    // Normalize the result to ensure the vector has length 1
    return glm::normalize(forward);
}

glm::vec3 Player::getRight() {
    // Start with a default Right vector (looking down the X-axis)
    glm::vec3 right = glm::vec3(1.0f, 0.0f, 0.0f);

    right = mOrientation_ * right;

    // Normalize the result to ensure the vector has length 1
    return glm::normalize(right);
}


} // namespace vessels