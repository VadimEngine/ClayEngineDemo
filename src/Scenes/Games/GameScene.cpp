// forward declare
// ClayEngine
#include <Clay/Application/App.h>
// class
#include "Scenes/Games/GamesScene.h"

GamesScene::GamesScene(clay::App& theApp)
    : clay::Scene(theApp), mGui_(*this) {}

GamesScene::~GamesScene() {}

void GamesScene::update(float dt) {}

void GamesScene::render(clay::Renderer& renderer) {
    renderer.setCamera(getFocusCamera());
}

void GamesScene::renderGUI() {
    mGui_.render();
}
