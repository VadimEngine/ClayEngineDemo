#pragma once
// ClayEngine
#include <clay/gui/desktop/ImGuiComponent.h>
#include <map>

namespace shader_tool_scene {
// Forward declare Scene
class ShaderToolScene;

enum class SystemUniform {
    NONE = 0,
    CAMERA_VIEW,
    CAMERA_PROJ,
    CAMERA_INV_IEW,
    CAMERA_INV_PROJ,
    MODEL,
    TIME_NS,
    FRAME,
    SCREEN_SIZE
};

struct UniformGroup {
    char label[256];
    char dataStr[256];
    std::vector<float> values;
    bool enabled;
    int binding;
    SystemUniform systemUniform;
};

struct TextureUniform {
    char label[256];
    int textureId;
    unsigned int binding;
    bool enabled;
};

class ShaderToolSceneGUI: public clay::ImGuiComponent {
public:
    /**
     * Constructor
     * @param theScene The scene this gui is for
     */
    ShaderToolSceneGUI(ShaderToolScene& theScene);

    /** Destructor */
    ~ShaderToolSceneGUI();

    /** Build the GUI ImGui components every frame */
    void buildImGui() override;

    void compileShader();

public:
    /** Build the section to list/control the camera of this scene */
    void buildCameraSection();

    void buildShaderSection();

    void buildModelTransformSection();

    void saveShaders(const std::string shaderName);

    std::vector<float> parseFloatString(const std::string& input);

    /** The Scene this GUI is for */
    ShaderToolScene& mScene_;
    /** If the GUI is set to enable VSync */
    bool mVSyncEnabled_;
    /** The Camera Mode this GUI applies*/
    int mCameraMode_;

    char vertexBuffer[1024 * 16] = 
R"(#version 450 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

uniform mat4 uProjection;
uniform mat4 uView;
uniform mat4 uModel;

void main() {
    gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0);
})";

    char tesselationControlBuffer[1024 * 16] = {};
    bool tesselationControlDefault = true;

    char tesselationEvaluationBuffer[1024 * 16] = {};
    bool tesselationEvaluationDefault = true;

    char geometryBuffer[1024 * 16] = {};
    bool geometryDefault = true;

    char fragmentBuffer[1024 * 16] = 
R"(#version 450 core

out vec4 FragColor;

void main() {
    FragColor = vec4(1,1,1,1);
}
)";

    // ordered to match enum class SystemUniform  
    const std::vector<std::string> mSystemValues_ = {
        "None", 
        "CameraView", 
        "CameraProj", 
        "CameraInvView", 
        "CameraInvProj", 
        "Model", 
        "Time", 
        "Frame", 
        "ScreenSize"
    };

    // ordered to match enum class PrimitiveTopology
    const std::vector<std::string> mDrawPrimitives_ = {
        "Point List,"
        "Line List",
        "Line Strip",
        "Line Loop",
        "Triangle List",
        "Triangle Strip",
        "Triangle Fan"
    };

    int mSelectedMeshIndex_ = 0;

    std::vector<UniformGroup> mUniforms_;

    std::vector<TextureUniform> mTextureUniforms_;

    bool mHDREnabled_ = false;

    std::vector<std::pair<std::string, clay::Mesh*>> mMeshList_;

    std::vector<const char*> meshLabels_;

    // ordered to make iterating deterministic
    std::map<unsigned int, std::string> mTextureNamesById_;

    glm::mat4 mTransformMat_ = glm::identity<glm::mat4>();

};

} // namespace shader_tool_scene