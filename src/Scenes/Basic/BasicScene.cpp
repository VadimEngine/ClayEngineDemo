// third party
#include "glm/vec2.hpp"
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
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

    mBackgroundColor_ = {.0,.0,.0,1.f};
    getFocusCamera()->setPosition({0,.1,5});

    // First Entity
    {
        std::unique_ptr<clay::Entity> theEntity = std::make_unique<clay::Entity>(*this);
        // Solid cube properties
        clay::ModelRenderable* solidCubeRenderable = theEntity->addRenderable<clay::ModelRenderable>();
        solidCubeRenderable->setModel(mResources_.getResource<clay::Model>("Cube"));
        solidCubeRenderable->setShader(getApp().getResources().getResource<clay::ShaderProgram>("Assimp"));

        solidCubeRenderable->setWireframeRendering(false);
        solidCubeRenderable->setColor({.3f, .3f, .3f, 1.0f});
        // Set sprite properties
        clay::SpriteRenderable* spriteRenderable = theEntity->addRenderable<clay::SpriteRenderable>();
        spriteRenderable->setSprite(&mSprite_);
        spriteRenderable->setColor({.3f, 0.f, 0.f, 1.0f});
        spriteRenderable->setPosition({0.f, 1.f, 0.f});
        // First entity properties
        mEntities_.push_back(std::move(theEntity));
    }
    // Second Entity
    {
        std::unique_ptr<clay::Entity> theEntity = std::make_unique<clay::Entity>(*this);
        clay::ModelRenderable* textureCubeRenderable = theEntity->addRenderable<clay::ModelRenderable>();
        textureCubeRenderable->setModel(mResources_.getResource<clay::Model>("Cube"));
        textureCubeRenderable->setShader(getApp().getResources().getResource<clay::ShaderProgram>("MVPTexShader"));
        // Texture cube properties
        textureCubeRenderable->setTexture(
            0,
            mApp_.getResources().getResource<clay::Texture>("SampleTexture")->getId(),
            "texture0"
        );

        // Second Entity properties
        theEntity->setPosition({3.f, .5f, 0.f});
        mEntities_.push_back(std::move(theEntity));
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
        floorRenderable->setColor({0.1f, 0.1f, 0.1f, 1.0f});
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
        textRenderable->setFont(mApp_.getResources().getResource<clay::Font>("Runescape"));
        textRenderable->setScale({.1f, .1f, 1});
        textRenderable->setColor({1.0f, 1.0f, 0.0f, 1.0f});

        mEntities_.push_back(std::move(entity));
    }

    mHighlightShader_ = mApp_.getResources().getResource<clay::ShaderProgram>("Solid");
}

BasicScene::~BasicScene() {}

void BasicScene::update(float dt) {
    mCameraController_.update(dt);
}

void BasicScene::render(clay::Renderer& renderer) {
    renderer.setCamera(getFocusCamera());

    // Restore default stencil settings
    mApp_.getGraphicsAPI()->stencilMask(0x00);

    // Draw unhighlighted entities normally 
    for (auto& entity : mEntities_) {
        if (mHighlightEntity_ == entity.get()) {
            continue;
        }
        entity->render(renderer);
    }

    if (mHighlightEntity_ != nullptr) {
        // Enable stencil writing for highlighted objects
        mApp_.getGraphicsAPI()->stencilFunc(clay::IGraphicsAPI::TestFunction::ALWAYS, 0xFF);
        mApp_.getGraphicsAPI()->stencilMask(0xFF);

        // Draw highlighted objects normally while also update the stencil buffer
        mHighlightEntity_->render(renderer);

        // Second pass: draw the outline only where the stencil is not 1
        mApp_.getGraphicsAPI()->stencilFunc(clay::IGraphicsAPI::TestFunction::NOTEQUAL, 0xFF);
        mApp_.getGraphicsAPI()->stencilMask(0x00);

        mHighlightShader_->bind();
        mHighlightShader_->setMat4("uScaleMat", glm::scale(glm::mat4(1.0f), {1.1f, 1.1f, 1.1f}));
        mHighlightShader_->setVec4("uSolidColor", {1.0f, 1.0f, 0.0f, 1.0f});

        // Render the highlight
        mHighlightEntity_->render(renderer, *mHighlightShader_);

        // Restore default stencil and depth settings
        glStencilMask(0xFF);
        glStencilFunc(GL_ALWAYS, 0, 0xFF);

        mApp_.getGraphicsAPI()->stencilFunc(clay::IGraphicsAPI::TestFunction::ALWAYS, 0xFF);
        mApp_.getGraphicsAPI()->stencilMask(0xFF);
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

void BasicScene::setHighLightEntity(clay::Entity* highlight) {
    mHighlightEntity_ = highlight;
}

} // namespace basic_scene