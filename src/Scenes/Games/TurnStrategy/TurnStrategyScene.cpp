// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
#include <clay/utils/desktop/UtilsDesktop.h>
// class
#include "Scenes/Games/TurnStrategy/TurnStrategyScene.h"

namespace turn_strategy {

TurnStrategyScene::TurnStrategyScene(clay::IApp& theApp)
: clay::BaseScene(theApp), mGui_(*this) {
    assembleResources();
    mBackgroundColor_ = {.5,.5,1,1.f};
    mpGame_ = std::make_unique<TurnStrategyGame>(*this);
}

TurnStrategyScene::~TurnStrategyScene() {}

void TurnStrategyScene::assembleResources() {
    auto vFileData = clay::Resources::loadFileToMemory((clay::Resources::RESOURCE_PATH / "World1.png").string());
    auto imageData = clay::utils::fileDataToImageData(vFileData);
    mResources_.addResource(std::move(std::make_unique<clay::Texture>(*((clay::AppDesktop&)mApp_).getGraphicsAPI(), imageData, true)), "World1");
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
    ((clay::AppDesktop&)mApp_).getRenderer().enableGammaCorrect(false);
    renderer.setCamera(getFocusCamera());
    mpGame_->render(renderer);
}

void TurnStrategyScene::renderGUI() {
    mGui_.render();
}

void TurnStrategyScene::onKeyPress(unsigned int code) {}

void TurnStrategyScene::onKeyRelease(unsigned int code) {}

void TurnStrategyScene::onMousePress(const clay::IInputHandler::MouseEvent& mouseEvent) {
    if (!clay::ImGuiComponent::mouseOnGUI()) {
        mpGame_->onMousePress(mouseEvent);
    }
}

void TurnStrategyScene::onMouseRelease(const clay::IInputHandler::MouseEvent& mouseEvent) {
    mpGame_->onMouseRelease(mouseEvent);
}

void TurnStrategyScene::onMouseWheel(const clay::IInputHandler::MouseEvent& mouseEvent) {
    mpGame_->onMouseWheel(mouseEvent);
}

TurnStrategyGame& TurnStrategyScene::getGame() {
    return *mpGame_.get();
}

} // namespace turn_strategy