// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// class
#include "Scenes/Games/Pong/PongScene.h"

namespace pong {
PongScene::PongScene(clay::IApp& theApp)
: clay::BaseScene(theApp), mGui_(*this) {
    assembleResources();
    mpGame_ = std::make_unique<PongGame>(*this);
}

PongScene::~PongScene() {}

void PongScene::update(const float dt) {
    mpGame_->update(dt);
}

void PongScene::render(clay::IGraphicsContext& gContext) {
    ((clay::AppDesktop&)mApp_).getRenderer().setCamera(getFocusCamera());
    mpGame_->render(gContext);
}

void PongScene::renderGUI() {
    mGui_.render();
}

void PongScene::assembleResources() {
    // Circle Plane Model
    std::unique_ptr<clay::Model> circleModel = std::make_unique<clay::Model>();
    circleModel->addSharedMesh(
        mApp_.getResources().getResource<clay::Mesh>("CircularPlane")
    );
    mResources_.addResource(std::move(circleModel), "CircularPlane");
    // Rectangle Plane Model
    std::unique_ptr<clay::Model> rectModel = std::make_unique<clay::Model>();
    rectModel->addSharedMesh(
        mApp_.getResources().getResource<clay::Mesh>("RectPlane")
    );
    mResources_.addResource(std::move(rectModel), "RectPlane");
}

void PongScene::onInputEvent(clay::InputEvent& e) {
    if (e.type_ == clay::InputEvent::EventType::KEY && ((clay::KeyEvent&)e).getType() == clay::KeyEvent::Type::PRESS) {
        onKeyPress(((clay::KeyEvent&)e).getCode());
    }
}

void PongScene::onKeyPress(unsigned int code) {
    if (!clay::ImGuiComponent::keyboardGUIFocus()) {
        mpGame_->onKeyPress(code);
    }
}

void PongScene::onKeyRelease(unsigned int code) {}

PongGame& PongScene::getGame() {
    return *(mpGame_.get());
}

} // namespace pong