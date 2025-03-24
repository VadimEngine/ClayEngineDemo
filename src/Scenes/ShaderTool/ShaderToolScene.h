#pragma once
// ClayEngine
#include <clay/application/desktop/CameraController.h>
#include <clay/application/common/BaseScene.h>
#include <clay/entity/render/ModelRenderable.h>
#include <clay/entity/render/SpriteRenderable.h>
#include <clay/entity/render/TextRenderable.h>
#include <clay/graphics/common/ShaderProgram.h>
#include <clay/graphics/common/Texture.h>
// project
#include "Scenes/ShaderTool/ShaderToolSceneGUI.h"

namespace shader_tool_scene {
class ShaderToolScene : public clay::BaseScene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    ShaderToolScene(clay::IApp& theApp);

    /** Destructor */
    ~ShaderToolScene();

    /**
     * Update the Scene
     * @param dt Time since last update in seconds
     */
    void update(const float dt) override;

    /**
     * Render this scene
     * @param renderer Rendering helper
     */
    void render(clay::IGraphicsContext& gContext) override;

    /**
     * Render just the gui for this scene
     */
    void renderGUI() override;

    /**
     * @brief Loads and builds resources that are used for this scene
     */
    void assembleResources() override;

    void setShader(clay::ShaderProgram* newShader);

    void setMesh(clay::Mesh* newMesh);

    void setUniforms(const std::vector<UniformGroup>& uniforms, const std::vector<TextureUniform>& textureUniforms);

    void setTransformMat(const glm::mat4& newTransform);

private:
    /** Camera Controller */
    clay::CameraController mCameraController_;
    /** GUI for this Scene*/
    ShaderToolSceneGUI mGui_;

    std::vector<UniformGroup> mCurrentUniforms;

    std::vector<TextureUniform> mCurrentTextureUniforms_;

    clay::ShaderProgram* mCurrentShader_ = nullptr;

    clay::Mesh* mCurrentMesh_ = nullptr;

    glm::mat4 mTransformMat_ = glm::identity<glm::mat4>();

};
} // namespace shader_tool_scene