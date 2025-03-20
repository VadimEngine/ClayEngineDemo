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
    mResources_.loadResource<clay::Texture>({(clay::Resources::RESOURCE_PATH  / "textures" / "World1.png").string()}, "World1");

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

void TurnStrategyScene::render(clay::IGraphicsContext& gContext) {
    ((clay::AppDesktop&)mApp_).getRenderer().enableGammaCorrect(false);
     ((clay::AppDesktop&)mApp_).getRenderer().setCamera(getFocusCamera());
    mpGame_->render(gContext);
}

void TurnStrategyScene::renderGUI() {
    mGui_.render();
}

void TurnStrategyScene::onInputEvent(clay::InputEvent& e) {
    switch (e.type_) {
    case clay::InputEvent::EventType::KEY: {
        clay::KeyEvent& keyEvent = (clay::KeyEvent&)e;
        if (keyEvent.getType() == clay::KeyEvent::Type::PRESS) {
            onKeyPress(keyEvent.getCode());
        }
        break;
    }
    case clay::InputEvent::EventType::MOUSE: {
        clay::MouseEvent& mouseEvent = (clay::MouseEvent&)e;
        if (mouseEvent.getType() == clay::MouseEvent::Type::PRESS) {
            onMousePress(mouseEvent);
        } else if (mouseEvent.getType() == clay::MouseEvent::Type:: SCROLL_DOWN || mouseEvent.getType() == clay::MouseEvent::Type:: SCROLL_UP) {
            onMouseWheel(mouseEvent);
        }
        break;
    }
    default:
        break;
    }
}

void TurnStrategyScene::onKeyPress(unsigned int code) {}

void TurnStrategyScene::onKeyRelease(unsigned int code) {}

void TurnStrategyScene::onMousePress(const clay::MouseEvent& mouseEvent) {
    if (!clay::ImGuiComponent::mouseOnGUI()) {
        mpGame_->onMousePress(mouseEvent);
    }
}

void TurnStrategyScene::onMouseRelease(const clay::MouseEvent& mouseEvent) {
    mpGame_->onMouseRelease(mouseEvent);
}

void TurnStrategyScene::onMouseWheel(const clay::MouseEvent& mouseEvent) {
    mpGame_->onMouseWheel(mouseEvent);
}

TurnStrategyGame& TurnStrategyScene::getGame() {
    return *mpGame_.get();
}

} // namespace turn_strategy