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
#include <clay/utils/desktop/UtilsDesktop.h>
// class
#include "Scenes/ShaderTool/ShaderToolScene.h"

namespace shader_tool_scene {
ShaderToolScene::ShaderToolScene(clay::IApp& theApp)
    : clay::BaseScene(theApp),
    mCameraController_(
        getFocusCamera(),
        *(clay::InputHandlerDesktop*)(mApp_.getWindow()->getInputHandler())
    ),
    mGui_(*this) {
    // load/build resources
    assembleResources();

    mBackgroundColor_ = {.0,.0,.0,1.f};
    getFocusCamera()->setPosition({0,.1,5});

    mGui_.compileShader();
    mCurrentMesh_ = mGui_.mMeshList_[0].second;
    mCurrentUniforms = mGui_.mUniforms_;
}

ShaderToolScene::~ShaderToolScene() {}

void ShaderToolScene::update(float dt) {
    if (!clay::ImGuiComponent::keyboardGUIFocus()) {
        mCameraController_.update(dt);// dont update if focused on gui
    }
}

void ShaderToolScene::render(clay::IGraphicsContext& gContext) {
    clay::RendererOpenGL renderer = ((clay::AppDesktop&)mApp_).getRenderer();

    if (mCurrentShader_ != nullptr && mCurrentMesh_ != nullptr) {
        renderer.setCamera(getFocusCamera());

        mCurrentShader_->bind();

        for (const auto& eachUniform: mCurrentUniforms) {
            if (eachUniform.enabled) {
                if (eachUniform.systemUniform != SystemUniform::NONE) {
                    if (eachUniform.systemUniform == SystemUniform::CAMERA_PROJ) {
                        mCurrentShader_->setMat4(eachUniform.label, mpFocusCamera_->getProjectionMatrix());
                    } else if (eachUniform.systemUniform == SystemUniform::CAMERA_VIEW) {
                        mCurrentShader_->setMat4(eachUniform.label, mpFocusCamera_->getViewMatrix());
                    } else if (eachUniform.systemUniform == SystemUniform::MODEL) {
                        mCurrentShader_->setMat4(eachUniform.label, mTransformMat_);
                    }
                } else {
                    if (eachUniform.values.size() == 4) {
                        const auto& value = eachUniform.values;
                        mCurrentShader_->setVec4(eachUniform.label , glm::vec4(value[0], value[1], value[2], value[3]));
                    }
                }
            }
        }

        for (int i = 0 ; i < mCurrentTextureUniforms_.size(); ++i) {
            const auto eachTextureUniform = mCurrentTextureUniforms_[i];

            if (eachTextureUniform.enabled) {
                mCurrentShader_->setTexture(eachTextureUniform.label, eachTextureUniform.textureId, i);
            }
        }

        mCurrentMesh_->render(*mCurrentShader_);
    }

}

void ShaderToolScene::renderGUI() {
    mGui_.render();
}

void ShaderToolScene::setShader(clay::ShaderProgram* newShader) {
    if (mCurrentShader_ != nullptr) {
        delete mCurrentShader_;
    }
    mCurrentShader_ = newShader;
}

void ShaderToolScene::setMesh(clay::Mesh* newMesh) {
    mCurrentMesh_ = newMesh;
}

void ShaderToolScene::setUniforms(const std::vector<UniformGroup>& uniforms, const std::vector<TextureUniform>& textureUniforms) {
    mCurrentUniforms = uniforms;
    mCurrentTextureUniforms_ = textureUniforms;
}

void ShaderToolScene::setTransformMat(const glm::mat4& newTransform) {
    mTransformMat_ = newTransform;
}

void ShaderToolScene::assembleResources() {
    std::unique_ptr<clay::Model> sphereModel = std::make_unique<clay::Model>();
}
} // namespace shader_tool_scene