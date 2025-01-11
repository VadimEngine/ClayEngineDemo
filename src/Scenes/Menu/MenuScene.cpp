// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// class
#include "Scenes/Menu/MenuScene.h"

namespace menu_scene {

MenuScene::MenuScene(clay::IApp& theApp)
    : clay::BaseScene(theApp), mGui_(*this) {}

MenuScene::~MenuScene() {}

void MenuScene::update(const float dt) {}

void MenuScene::render(clay::Renderer& renderer) {
    renderer.setCamera(getFocusCamera());
}

void MenuScene::renderGUI() {
    mGui_.render();
}
} // namespace menu_scene