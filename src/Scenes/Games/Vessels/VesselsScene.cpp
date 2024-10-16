// forward declare
// ClayEngine
#include <Clay/Application/App.h>
// class
#include "Scenes/Games/Vessels/VesselsScene.h"

namespace vessels {
VesselsScene::VesselsScene(clay::App& theApp)
: clay::Scene(theApp),
    mGui_(*this) {
    assembleResources();
    mpGame_ = std::make_unique<VesselsGame>(*this);
    }

VesselsScene::~VesselsScene() {}

void VesselsScene::update(float dt) {
    mpGame_->update(dt);
}

void VesselsScene::render(clay::Renderer& renderer) {
    renderer.setCamera(getFocusCamera());
    mpGame_->render(renderer);
}

void VesselsScene::renderGUI() {
    mGui_.render();
}

void VesselsScene::onMousePress(const clay::InputHandler::MouseEvent& mouseEvent) {}

void VesselsScene::assembleResources() {
    std::unique_ptr<clay::Model> rectModel = std::make_unique<clay::Model>();
    rectModel->addSharedMesh(
        mApp_.getResources().getResource<clay::Mesh>("RectPlane")
    );
    mResources_.addResource(std::move(rectModel), "RectPlane");
    // Cube
    std::unique_ptr<clay::Model> cubeModel = std::make_unique<clay::Model>();
    cubeModel->addSharedMesh(
        mApp_.getResources().getResource<clay::Mesh>("Cube")
    );
    mResources_.addResource(std::move(cubeModel), "Cube");
}

VesselsGame& VesselsScene::getGame() {
    return *mpGame_.get();
}

} // namespace vessels
