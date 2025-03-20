// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// class
#include "Scenes/Games/RPG2D/RPG2DScene.h"

namespace rpg_2d {

RPG2DScene::RPG2DScene(clay::IApp& theApp)
    : clay::BaseScene(theApp), mGui_(*this), mGame_(*this, *getFocusCamera()) {
    getFocusCamera()->setPosition({0,0,10});
}

RPG2DScene::~RPG2DScene() {}

void RPG2DScene::update(const float dt) {
    mGame_.update(dt);
}

void RPG2DScene::render(clay::IGraphicsContext& gContext) {
    ((clay::AppDesktop&)mApp_).getRenderer().enableGammaCorrect(false);
    ((clay::AppDesktop&)mApp_).getRenderer().setCamera(getFocusCamera());
    mGame_.render(gContext);
}

void RPG2DScene::renderGUI() {
    mGui_.render();
}

void RPG2DScene::onInputEvent(clay::InputEvent& e) {
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
        }
        break;
    }
    default:
        break;
    }
}

void RPG2DScene::onKeyPress(unsigned int code) {
    mGame_.onKeyPress(code);
}

void RPG2DScene::onKeyRelease(unsigned int code) {
}

void RPG2DScene::onMousePress(const clay::MouseEvent& mouseEvent) {
    mGame_.onMousePress(mouseEvent);
}

} // namespace rpg_2d