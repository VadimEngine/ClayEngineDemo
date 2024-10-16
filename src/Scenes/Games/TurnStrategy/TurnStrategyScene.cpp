// forward declare
// ClayEngine
#include <Clay/Application/App.h>
// class
#include "Scenes/Games/TurnStrategy/TurnStrategyScene.h"

namespace turn_strategy {

TurnStrategyScene::TurnStrategyScene(clay::App& theApp)
: clay::Scene(theApp), mGui_(*this) {
    assembleResources();
    mBackgroundColor_ = {.5,.5,1,1.f};
    mpGame_ = std::make_unique<TurnStrategyGame>(*this);
}

TurnStrategyScene::~TurnStrategyScene() {}

void TurnStrategyScene::assembleResources() {
    mResources_.loadResource<clay::Texture>(
        {clay::Resource::RESOURCE_PATH / "World1.png"},
        "World1"
    );
    // Rectangle Plane Model
    std::unique_ptr<clay::Model> rectModel = std::make_unique<clay::Model>();
    rectModel->addSharedMesh(
        mApp_.getResources().getResource<clay::Mesh>("RectPlane")
    );
    mResources_.addResource(std::move(rectModel), "RectPlane");
}

void TurnStrategyScene::update(const float dt) {
    mpGame_->update(dt);
}

void TurnStrategyScene::render(clay::Renderer& renderer) {
    mApp_.getRenderer().enableGammaCorrect(false);
    renderer.setCamera(getFocusCamera());
    mpGame_->render(renderer);
}

void TurnStrategyScene::renderGUI() {
    mGui_.render();
}

void TurnStrategyScene::onKeyPress(unsigned int code) {}

void TurnStrategyScene::onKeyRelease(unsigned int code) {}

void TurnStrategyScene::onMousePress(const clay::InputHandler::MouseEvent& mouseEvent) {
    if (!clay::ImGuiComponent::mouseOnGUI()) {
        mpGame_->onMousePress(mouseEvent);
    }
}

void TurnStrategyScene::onMouseRelease(const clay::InputHandler::MouseEvent& mouseEvent) {
    mpGame_->onMouseRelease(mouseEvent);
}

void TurnStrategyScene::onMouseWheel(const clay::InputHandler::MouseEvent& mouseEvent) {
    mpGame_->onMouseWheel(mouseEvent);
}

TurnStrategyGame& TurnStrategyScene::getGame() {
    return *mpGame_.get();
}

} // namespace turn_strategy