// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// class
#include "Scenes/Games/GamesScene.h"

GamesScene::GamesScene(clay::IApp& theApp)
    : clay::BaseScene(theApp), mGui_(*this) {}

GamesScene::~GamesScene() {}

void GamesScene::update(float dt) {}

void GamesScene::render(clay::IGraphicsContext& gContext) {
    ((clay::AppDesktop&)mApp_).getRenderer().setCamera(getFocusCamera());
}

void GamesScene::renderGUI() {
    mGui_.render();
}
