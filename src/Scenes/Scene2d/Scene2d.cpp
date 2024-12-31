// ClayEngine
#include <clay/application/App.h>
// class
#include "Scenes/Scene2d/Scene2d.h"

namespace scene_2d {
Scene2d::Scene2d(clay::App& theApp)
    : clay::Scene(theApp),
    mCameraController_(getFocusCamera(), mApp_.getWindow().getInputHandler()),
    mGui_(*this),
    mSprite1_(*mApp_.getResources().getResource<clay::SpriteSheet>("SpriteSheet1"), glm::ivec2(0, 0)),
    mSprite2_(*mApp_.getResources().getResource<clay::SpriteSheet>("SpriteSheet1"), glm::ivec2(1, 0)) {
    assembleResources();
    mpFocusCamera_->setPosition({0,0,5});

    // first sprite
    clay::Entity* theEntity1 = new clay::Entity(*this);
    clay::SpriteRenderable* sprite1Renderable1 = new clay::SpriteRenderable(&mSprite1_);
    theEntity1->addRenderable(sprite1Renderable1);

    // second sprite
    clay::Entity* theEntity2 = new clay::Entity(*this);
    clay::SpriteRenderable* sprite1Renderable2 = new clay::SpriteRenderable(&mSprite2_);
    theEntity2->addRenderable(sprite1Renderable2);
    theEntity2->setPosition({1.f, 0.f, 0.f});

    // white square
    clay::Entity* theEntity3 = new clay::Entity(*this);
    theEntity3->addRenderable(new clay::ModelRenderable(
        getResources().getResource<clay::Model>("RectPlane"),
        getApp().getResources().getResource<clay::ShaderProgram>("Assimp")
    ));
    theEntity3->setPosition({0.f, 0.f, 0.f});
    // Add white square first so its rendered behind the sprites
    mEntities_.push_back(std::unique_ptr<clay::Entity>(theEntity3));
    mEntities_.push_back(std::unique_ptr<clay::Entity>(theEntity1));
    mEntities_.push_back(std::unique_ptr<clay::Entity>(theEntity2));

    // Text Entity
    clay::Entity* theEntity4 = new clay::Entity(*this);
    theEntity4->addRenderable(new clay::TextRenderable(
        "test",
        getApp().getResources().getResource<clay::Font>("Consolas")
    ));
    theEntity4->setScale({.01f, .01f, 0});
    theEntity4->setPosition({0, 1, 0});

    mEntities_.push_back(std::unique_ptr<clay::Entity>(theEntity4));
}

Scene2d::~Scene2d() {}

void Scene2d::update(const float dt) {
    mCameraController_.update(dt);
}

void Scene2d::render(clay::Renderer& renderer) {
    mApp_.getRenderer().enableGammaCorrect(false);
    renderer.setCamera(getFocusCamera());
    for (int i = 0; i < mEntities_.size(); ++i) {
        mEntities_[i]->render(renderer);
    }
}

void Scene2d::renderGUI() {
    mGui_.render();
}

void Scene2d::assembleResources() {
    std::unique_ptr<clay::Model> rectModel = std::make_unique<clay::Model>();
    rectModel->addSharedMesh(
        mApp_.getResources().getResource<clay::Mesh>("RectPlane")
    );
    mResources_.addResource(std::move(rectModel), "RectPlane");
}

std::vector<std::unique_ptr<clay::Entity>>& Scene2d::getEntities() {
    return mEntities_;
}

} // namespace scene_2d