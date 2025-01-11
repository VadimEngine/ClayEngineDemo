// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// class
#include "Scenes/PhysicsScene/PhysicsScene.h"

namespace physics_scene {
PhysicsScene::PhysicsScene(clay::IApp& theApp)
    : clay::BaseScene(theApp), mCameraController_(getFocusCamera(), *((clay::InputHandlerDesktop*)((clay::WindowDesktop*)mApp_.getWindow())->getInputHandler())), mGui_(*this) {
    assembleResources();
    mBackgroundColor_ = {0,0,0, 1.f};
    getFocusCamera()->setPosition({0,0,5});
    // First particle
    {
        clay::Entity* theEntity = new clay::Entity(*this);
        clay::ModelRenderable* modelRenderable = theEntity->addRenderable<clay::ModelRenderable>();
        modelRenderable->setModel(mResources_.getResource<clay::Model>("CircularPlane"));
        modelRenderable->setShader(getApp().getResources().getResource<clay::ShaderProgram>("Assimp"));
        clay::RigidBodyComponent* rigid = theEntity->addPhysicsComponent<clay::RigidBodyComponent>();
        rigid->getCollider().setShape(clay::ColliderOLD::Shape::CIRCLE);
        rigid->setMobile(true);
        rigid->setAttractive(true);
        mEntities_.emplace_back(theEntity);
    }
    // floor
    {
        clay::Entity* theEntity = new clay::Entity(*this);
        clay::ModelRenderable* modelRenderable = theEntity->addRenderable<clay::ModelRenderable>();
        modelRenderable->setModel(mResources_.getResource<clay::Model>("RectPlane"));
        modelRenderable->setShader(getApp().getResources().getResource<clay::ShaderProgram>("Assimp"));
        theEntity->setPosition({0.f, -10.f, 0.f});
        theEntity->setScale({10.f, 1.f, 1.f});
        clay::RigidBodyComponent* rigid = theEntity->addPhysicsComponent<clay::RigidBodyComponent>();
        rigid->getCollider().setShape(clay::ColliderOLD::Shape::RECTANGLE);
        rigid->setMobile(false);
        rigid->setAttractive(false);
        mEntities_.emplace_back(theEntity);
    }
}

PhysicsScene::~PhysicsScene() {}

void PhysicsScene::update(const float dt) {
    mCameraController_.update(dt);
    if (mIsRunning_) {
        handleEntityCollision(dt);
        for (int i = 0; i < mEntities_.size(); ++i) {
            mEntities_[i]->update(dt);
        }
    }
    handleEntityOverlap();
}

void PhysicsScene::render(clay::Renderer& renderer) {
    renderer.setCamera(getFocusCamera());
    for (int i = 0; i < mEntities_.size(); ++i) {
        mEntities_[i]->render(renderer);
    }
}

void PhysicsScene::renderGUI() {
    mGui_.render();
}

std::vector<std::unique_ptr<clay::Entity>>& PhysicsScene::getEntities() {
    return mEntities_;
}

void PhysicsScene::addEntity(const glm::vec3 position) {
    clay::Entity* newEntity = new clay::Entity(*this);
    newEntity->setPosition(position);
    clay::ModelRenderable* modelRenderable = newEntity->addRenderable<clay::ModelRenderable>();
    modelRenderable->setModel(mResources_.getResource<clay::Model>("CircularPlane"));
    modelRenderable->setShader(getApp().getResources().getResource<clay::ShaderProgram>("Assimp"));

    clay::RigidBodyComponent* rigid = newEntity->addPhysicsComponent<clay::RigidBodyComponent>();
    rigid->getCollider().setShape(clay::ColliderOLD::Shape::CIRCLE);
    rigid->setMobile(true);
    rigid->setAttractive(true);

    mEntities_.emplace_back(newEntity);
}

void PhysicsScene::assembleResources() {
    // Circle Plane Model
    std::unique_ptr<clay::Model> circleModel = std::make_unique<clay::Model>();
    circleModel->addSharedMesh(
        mApp_.getResources().getResource<clay::Mesh>("CircularPlane")
    );
    mResources_.addResource(std::move(circleModel), "CircularPlane");
    // Rectangle Plane Model
    std::unique_ptr<clay::Model> rectModel = std::make_unique<clay::Model>();
    rectModel->addSharedMesh(
        mApp_.getResources().getResource<clay::Mesh>("RectPlane")
    );
    mResources_.addResource(std::move(rectModel), "RectPlane");
}

void PhysicsScene::handleEntityCollision(const float dt) {
    for (int i = 0; i < mEntities_.size(); ++i) {
        clay::RigidBodyComponent* rigidBodyA = mEntities_[i]->getPhysicsComponent<clay::RigidBodyComponent>();

        if (rigidBodyA != nullptr && rigidBodyA->isEnabled()) {
            for (int j = i + 1; j < mEntities_.size(); ++j) {
                clay::RigidBodyComponent* rigidBodyB = mEntities_[j]->getPhysicsComponent<clay::RigidBodyComponent>();
                if (rigidBodyB != nullptr) {
                    rigidBodyA->handleIfCollision(rigidBodyB);
                    rigidBodyA->applyIfAttraction(rigidBodyB, dt);
                }
            }
        }
    }
}

void PhysicsScene::handleEntityOverlap() {
    // Separate any overlap
    for (int i = 0; i < mEntities_.size(); ++i) {
        clay::RigidBodyComponent* rigidBodyA = mEntities_[i]->getPhysicsComponent<clay::RigidBodyComponent>();

        if (rigidBodyA != nullptr && rigidBodyA->isEnabled()) {
            for (int j = i + 1; j < mEntities_.size(); ++j) {
                clay::RigidBodyComponent* rigidBodyB = mEntities_[j]->getPhysicsComponent<clay::RigidBodyComponent>();
                if (rigidBodyB != nullptr) {
                    auto mvt = rigidBodyA->getCollider().getCollisionMVT(&(rigidBodyB->getCollider()));
                    if (mvt.has_value()) {
                        glm::vec3 newPos1 = mEntities_[i]->getPosition() + mvt.value();
                        glm::vec3 newPos2 = mEntities_[j]->getPosition() - mvt.value();

                        if (rigidBodyA->isMobile()) {
                            mEntities_[i]->setPosition(newPos1);
                        }

                        if (rigidBodyB->isMobile()) {
                            mEntities_[j]->setPosition(newPos2);
                        }
                    }
                }
            }
        }
    }
}
} // namespace physics_scene