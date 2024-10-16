// forward declare
// ClayEngine
#include <Clay/Application/App.h>
// class
#include "Scenes/Games/RPG2D/RPG2DScene.h"

namespace rpg_2d {

RPG2DScene::RPG2DScene(clay::App& theApp)
    : clay::Scene(theApp), mGui_(*this), mGame_(*this, *getFocusCamera()) {
    getFocusCamera()->setPosition({0,0,10});
}

RPG2DScene::~RPG2DScene() {}

void RPG2DScene::update(const float dt) {
    mGame_.update(dt);
}

void RPG2DScene::render(clay::Renderer& renderer) {
    mApp_.getRenderer().enableGammaCorrect(false);
    renderer.setCamera(getFocusCamera());
    mGame_.render(renderer);
}

void RPG2DScene::renderGUI() {
    mGui_.render();
}

void RPG2DScene::onKeyPress(unsigned int code) {
    mGame_.onKeyPress(code);
}

void RPG2DScene::onKeyRelease(unsigned int code) {
}

void RPG2DScene::onMousePress(const clay::InputHandler::MouseEvent& mouseEvent) {
    mGame_.onMousePress(mouseEvent);
}

} // namespace rpg_2d