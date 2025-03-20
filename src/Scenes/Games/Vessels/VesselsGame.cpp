// third party
#include <GLFW/glfw3.h>
// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// project
#include "Scenes/Games/Vessels/VesselsScene.h"
// class
#include "Scenes/Games/Vessels/VesselsGame.h"

namespace vessels {

VesselsGame::VesselsGame(VesselsScene& scene)
    : mScene_(scene),
    mInputHandler_(*(clay::InputHandlerDesktop*) mScene_.getApp().getWindow()->getInputHandler()),
    mCameraController_(mScene_.getFocusCamera(), *(clay::InputHandlerDesktop*)mScene_.getApp().getWindow()->getInputHandler()) {
    mpPlayer_ = std::make_unique<Player>(*this);
    mpPlayer_->addRenderable(new clay::ModelRenderable(
        mScene_.getResources().getResource<clay::Model>("Cube"),
        mScene_.getApp().getResources().getResource<clay::ShaderProgram>("Assimp")
    ));
    mpPlayer_->setPosition({0.0f, 0.0f,-3.f});

    // make floor
    {
        std::unique_ptr<clay::Entity> floorEntity = std::make_unique<clay::Entity>(mScene_);
        clay::ModelRenderable* floorRenderable = floorEntity->addRenderable<clay::ModelRenderable>();
        floorRenderable->setModel(mScene_.getResources().getResource<clay::Model>("RectPlane"));
        floorRenderable->setShader(mScene_.getApp().getResources().getResource<clay::ShaderProgram>("Assimp"));
        // Plane Renderable properties
        floorRenderable->setOrientation(glm::angleAxis(glm::radians(-90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
        floorRenderable->setScale({10, 10, 0});
        floorRenderable->setColor({0.f, 1.f, 0.f, 1.0f});
        // Add renderable to floor entity
        mEntities_.push_back(std::move(floorEntity));
    }
}

VesselsGame::~VesselsGame() {}

void VesselsGame::update(const float dt) {
    handleKeyUpdate(dt);
}

void VesselsGame::render(clay::IGraphicsContext& gContext) {
    if (mState_ == VesselsGame::GameState::CORPOREAL_REALM) {
        mpPlayer_->render(gContext);
        for (const auto& entity: mEntities_) {
            entity->render(gContext);
        }
    }
}

void VesselsGame::handleKeyUpdate(float dt) {
    if (mState_ == VesselsGame::GameState::CORPOREAL_REALM) {

        if (mInputHandler_.isKeyPressed(GLFW_KEY_LEFT)) {
            auto& currRot = mpPlayer_->getOrientation();
            currRot *= glm::angleAxis(-glm::radians(-50.0f * dt), glm::vec3(0.0f, 1.0f, 0.0f));
        }
        if (mInputHandler_.isKeyPressed(GLFW_KEY_RIGHT)) {
            auto& currRot = mpPlayer_->getOrientation();
            currRot *= glm::angleAxis(-glm::radians(50.0f * dt), glm::vec3(0.0f, 1.0f, 0.0f));
        }

        const float speed = 5.f;
        glm::vec3 curPlayerPos = mpPlayer_->getPosition();

        glm::vec3 dir = {0,0,0};

        if (mInputHandler_.isKeyPressed(GLFW_KEY_W)) {
            dir += mpPlayer_->getForward();
        }
        if (mInputHandler_.isKeyPressed(GLFW_KEY_D)) {
            dir += mpPlayer_->getRight();
        }
        if (mInputHandler_.isKeyPressed(GLFW_KEY_S)) {
            dir += -mpPlayer_->getForward();
        }
        if (mInputHandler_.isKeyPressed(GLFW_KEY_A)) {
            dir += -mpPlayer_->getRight();
        }

        if (glm::length(dir) > 0.0f) {
            dir = glm::normalize(dir);
            mpPlayer_->setPosition(curPlayerPos + dir * dt * speed);
        }
    }
}

void VesselsGame::onKeyPress(unsigned int code) {}

void VesselsGame::onKeyRelease(unsigned int code) {}

VesselsGame::GameState VesselsGame::getGameState() {
    return mState_;
}

void VesselsGame::setState(VesselsGame::GameState newState) {
    mState_ = newState;
}

VesselsScene& VesselsGame::getScene() {
    return mScene_;
}

} // namespace vessels