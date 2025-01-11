// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// class
#include "Scenes/Basic/BasicScene.h"

namespace basic_scene {
BasicScene::BasicScene(clay::IApp& theApp)
    : clay::BaseScene(theApp),
    mCameraController_(
        getFocusCamera(),
        *(clay::InputHandlerDesktop*)(mApp_.getWindow()->getInputHandler())
    ),
    mGui_(*this),
    mSprite_(*mApp_.getResources().getResource<clay::SpriteSheet>("SpriteSheet1"), glm::ivec2(0, 0)) {
    // load/build resources
    assembleResources();

    mBackgroundColor_ = {.4,.4,.4,1.f};
    getFocusCamera()->setPosition({0,.1,5});

    // First Entity
    {
        std::unique_ptr<clay::Entity> theEntity1 = std::make_unique<clay::Entity>(*this);
        // Solid cube properties
        clay::ModelRenderable* solidCubeRenderable = theEntity1->addRenderable<clay::ModelRenderable>();
        solidCubeRenderable->setModel(mResources_.getResource<clay::Model>("Cube"));
        solidCubeRenderable->setShader(getApp().getResources().getResource<clay::ShaderProgram>("Assimp"));

        solidCubeRenderable->setWireframeRendering(true);
        solidCubeRenderable->setColor({.3f, .3f, .3f, 1.0f});
        // Set sprite properties
        clay::SpriteRenderable* spriteRenderable = theEntity1->addRenderable<clay::SpriteRenderable>();
        spriteRenderable->setSprite(&mSprite_);
        spriteRenderable->setColor({.3f, 0.f, 0.f, 1.0f});
        spriteRenderable->setPosition({0.f, 1.f, 0.f});
        // First entity properties
        theEntity1->setPosition({0.f, .5f, 0.f});
        mEntities_.push_back(std::move(theEntity1));
    }
    // Second Entity
    {
        std::unique_ptr<clay::Entity> theEntity2 = std::make_unique<clay::Entity>(*this);
        clay::ModelRenderable* textureCubeRenderable = theEntity2->addRenderable<clay::ModelRenderable>();
        textureCubeRenderable->setModel(mResources_.getResource<clay::Model>("Cube"));
        textureCubeRenderable->setShader(getApp().getResources().getResource<clay::ShaderProgram>("MVPTexShader"));
        // Texture cube properties
        textureCubeRenderable->setTexture(
            0,
            mApp_.getResources().getResource<clay::Texture>("SampleTexture")->getId(),
            "texture0"
        );

        // Second Entity properties
        theEntity2->setPosition({3.f, .5f, 0.f});
        mEntities_.push_back(std::move(theEntity2));
    }
    // Third Entity (Floor)
    {
        std::unique_ptr<clay::Entity> floorEntity = std::make_unique<clay::Entity>(*this);
        clay::ModelRenderable* floorRenderable = floorEntity->addRenderable<clay::ModelRenderable>();
        floorRenderable->setModel(mResources_.getResource<clay::Model>("RectPlane"));
        floorRenderable->setShader(getApp().getResources().getResource<clay::ShaderProgram>("Assimp"));
        // Plane Renderable properties
        floorRenderable->setRotation({-90, 0, 0});
        floorRenderable->setScale({10, 10, 0});
        floorRenderable->setColor({0.f, 0.f, 0.f, 1.0f});
        // Add renderable to floor entity
        mEntities_.push_back(std::move(floorEntity));
    }
    // Forth Entity (Sphere)
    {
        std::unique_ptr<clay::Entity> assimpEntity = std::make_unique<clay::Entity>(*this);
        clay::ModelRenderable* assimpRenderable = assimpEntity->addRenderable<clay::ModelRenderable>();
        assimpRenderable->setModel(mResources_.getResource<clay::Model>("Sphere"));
        assimpRenderable->setShader(getApp().getResources().getResource<clay::ShaderProgram>("Assimp"));

        assimpEntity->setPosition({0.f, 5.f, 0.f});
        mEntities_.push_back(std::move(assimpEntity));
    }
    // Fifth Entity (Textured rectangle)
    {
        std::unique_ptr<clay::Entity> planeTextureEntity = std::make_unique<clay::Entity>(*this);
        clay::ModelRenderable* planeTextureRenderable = planeTextureEntity->addRenderable<clay::ModelRenderable>();
        planeTextureRenderable->setModel(mResources_.getResource<clay::Model>("RectPlane"));
        planeTextureRenderable->setShader(getApp().getResources().getResource<clay::ShaderProgram>("TextureSurface"));
        // Texture. TODO allow imgui set this from list of textures
        planeTextureRenderable->setTexture(
            1,
            mApp_.getResources().getResource<clay::Texture>("SpriteSheet")->getId(),
            "uTexture"
        );
        planeTextureRenderable->setSubTextureTopLeft({0.f, 0.f});
        planeTextureRenderable->setSubTextureSize({16.f/512.f, 16.f/512.f});

        planeTextureEntity->setPosition({-2.f, 2.f, 0.f});
        mEntities_.push_back(std::move(planeTextureEntity));
    }
    // Sixth Entity (Text rectangle)
    {
        std::unique_ptr<clay::Entity> entity = std::make_unique<clay::Entity>(*this);
        clay::TextRenderable* textRenderable = entity->addRenderable<clay::TextRenderable>();
        textRenderable->setText("TEST STRING");
        textRenderable->setFont(mApp_.getResources().getResource<clay::Font>("Consolas"));
        textRenderable->setScale({.1f, .1f, 1});
        textRenderable->setColor({1, 0, 0, 1});

        mEntities_.push_back(std::move(entity));
    }
}

BasicScene::~BasicScene() {}

void BasicScene::update(float dt) {
    mCameraController_.update(dt);
}

void BasicScene::render(clay::Renderer& renderer) {
    renderer.enableGammaCorrect(false);
    renderer.setCamera(getFocusCamera());
    for (int i = 0; i < mEntities_.size(); ++i) {
        mEntities_[i]->render(renderer);
    }
}

void BasicScene::renderGUI() {
    mGui_.render();
}

void BasicScene::assembleResources() {
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

std::vector<std::unique_ptr<clay::Entity>>& BasicScene::getEntities() {
    return mEntities_;
}
} // namespace basic_scene