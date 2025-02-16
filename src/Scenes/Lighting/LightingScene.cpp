// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// class
#include "Scenes/Lighting/LightingScene.h"

namespace lighting_scene {

LightingScene::LightingScene(clay::IApp& theApp)
: clay::BaseScene(theApp),
    mCameraController_(getFocusCamera(), *(clay::InputHandlerDesktop*)mApp_.getWindow()->getInputHandler()),
    mGui_(*this) {
    assembleResources();

    mBackgroundColor_ = {0.0f, 0.0f, 0.0f, 1.f};
    getFocusCamera()->setPosition({0,.1,5});

    {
        // Light source
        mpLight_ = new LightEntity(*this);
        mpLight_->setPosition({0,1,0});
        mpLight_->setColor({10,10,10,1});
        mEntities_.push_back(std::unique_ptr<LightEntity>(mpLight_));
    }
    {
        // Cube 1
        std::unique_ptr<clay::Entity> assimpEntity = std::make_unique<clay::Entity>(*this);
        clay::ModelRenderable* assimpRenderable = assimpEntity->addRenderable<clay::ModelRenderable>();
        assimpRenderable->setModel(mResources_.getResource<clay::Model>("Cube"));
        assimpRenderable->setShader(getApp().getResources().getResource<clay::ShaderProgram>("AssimpLight"));

        assimpEntity->setPosition({1.f, 0.f, 0.f});
        mEntities_.push_back(std::move(assimpEntity));
    }
    {
        // Cube 2
        std::unique_ptr<clay::Entity> assimpEntity = std::make_unique<clay::Entity>(*this);
        clay::ModelRenderable* assimpRenderable = assimpEntity->addRenderable<clay::ModelRenderable>();
        assimpRenderable->setModel(mResources_.getResource<clay::Model>("Cube"));
        assimpRenderable->setShader(getApp().getResources().getResource<clay::ShaderProgram>("AssimpLight"));

        assimpEntity->setPosition({-1.f, 0.f, 0.f});
        mEntities_.push_back(std::move(assimpEntity));
    }
}

LightingScene::~LightingScene() {}

/**
 * Update the Scene
 * @param dt Time since last update in seconds
 */
void LightingScene::update(const float dt) {
    ((clay::AppDesktop&)mApp_).getRenderer().enableGammaCorrect(true);
    mCameraController_.update(dt);
}

/**
 * Render this scene
 * @param renderer Rendering helper
 */
void LightingScene::render(clay::Renderer& renderer) {
    mApp_.getGraphicsAPI()->bindFrameBuffer(clay::IGraphicsAPI::FrameBufferTarget::FRAMEBUFFER, renderer.getHDRFBO());

    renderer.setBloom(true);
    renderer.setCamera(getFocusCamera());
    renderer.setLightSources({mpLight_->getLightSource()});
    for (int i = 0; i < mEntities_.size(); ++i) {
        mEntities_[i]->render(renderer);
    }
    renderer.setBloom(false);
    renderer.renderHDR();
}

void LightingScene::renderGUI() {
    mGui_.render();
}

void LightingScene::assembleResources() {
    // Cube
    std::unique_ptr<clay::Model> cubeModel = std::make_unique<clay::Model>();
    cubeModel->addSharedMesh(
        mApp_.getResources().getResource<clay::Mesh>("Cube")
    );
    mResources_.addResource(std::move(cubeModel), "Cube");
    // Plane
    std::unique_ptr<clay::Model> planeModel = std::make_unique<clay::Model>();
    planeModel->addSharedMesh(
        mApp_.getResources().getResource<clay::Mesh>("RectPlane")
    );
    mResources_.addResource(std::move(planeModel), "RectPlane");
    // Sphere
    std::unique_ptr<clay::Model> sphereModel = std::make_unique<clay::Model>();
    sphereModel->addSharedMesh(
        mApp_.getResources().getResource<clay::Mesh>("Sphere")
    );
    mResources_.addResource(std::move(sphereModel), "Sphere");
}

std::vector<std::unique_ptr<clay::Entity>>& LightingScene::getEntities() {
    return mEntities_;
}

} // namespace lighting_scene
