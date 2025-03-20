// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// class
#include "Scenes/Menu/MenuScene.h"

namespace menu_scene {

MenuScene::MenuScene(clay::IApp& theApp)
    : clay::BaseScene(theApp), mGui_(*this) {}

MenuScene::~MenuScene() {}

void MenuScene::update(const float dt) {}

void MenuScene::render(clay::IGraphicsContext& gContext) {
    // TODO bind a orthographic UBO via camera?
    ((clay::AppDesktop&)mApp_).getRenderer().setCamera(getFocusCamera());
}

void MenuScene::renderGUI() {
    mGui_.render();
}
} // namespace menu_scene