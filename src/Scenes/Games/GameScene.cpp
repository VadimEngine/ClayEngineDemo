// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// class
#include "Scenes/Games/GamesScene.h"

GamesScene::GamesScene(clay::IApp& theApp)
    : clay::BaseScene(theApp), mGui_(*this) {}

GamesScene::~GamesScene() {}

void GamesScene::update(float dt) {}

void GamesScene::render(clay::Renderer& renderer) {
    renderer.setCamera(getFocusCamera());
}

void GamesScene::renderGUI() {
    mGui_.render();
}
