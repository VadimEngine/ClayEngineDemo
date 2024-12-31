// ClayEngine
#include <clay/application/App.h>
// class
#include "Scenes/Menu/MenuScene.h"

namespace menu_scene {

MenuScene::MenuScene(clay::App& theApp)
    : clay::Scene(theApp), mGui_(*this) {}

MenuScene::~MenuScene() {}

void MenuScene::update(const float dt) {}

void MenuScene::render(clay::Renderer& renderer) {
    renderer.setCamera(getFocusCamera());
}

void MenuScene::renderGUI() {
    mGui_.render();
}
} // namespace menu_scene