// standard lib
#include <fstream>
#include <iostream>
// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
// third party
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/euler_angles.hpp>
// project
#include "Scenes/ShaderTool/ShaderToolScene.h"
#include "Scenes/Menu/MenuScene.h"
// class
#include "Scenes/ShaderTool/ShaderToolSceneGUI.h"

namespace shader_tool_scene {
ShaderToolSceneGUI::ShaderToolSceneGUI(ShaderToolScene& theScene)
    : mScene_(theScene) {
    mVSyncEnabled_ = ((clay::WindowDesktop*)(mScene_.getApp().getWindow()))->getGLFWSwapInterval();
    mCameraMode_ = static_cast<int>(mScene_.getFocusCamera()->getMode());

    mMeshList_.emplace_back("Cube", mScene_.getApp().getResources().getResource<clay::Mesh>("Cube"));
    mMeshList_.emplace_back("Sphere", mScene_.getApp().getResources().getResource<clay::Mesh>("Sphere"));
    mMeshList_.emplace_back("CircularPlane", mScene_.getApp().getResources().getResource<clay::Mesh>("CircularPlane"));
    mMeshList_.emplace_back("RectPlane", mScene_.getApp().getResources().getResource<clay::Mesh>("RectPlane"));

    mTextureNamesById_[mScene_.getApp().getResources().getResource<clay::Texture>("SampleTexture")->getId()] = "SampleTexture";
    mTextureNamesById_[mScene_.getApp().getResources().getResource<clay::Texture>("SpriteSheet")->getId()] = "SpriteSheet";

    for (const auto& eachMesh : mMeshList_) {
        meshLabels_.push_back(eachMesh.first.c_str());
    }

    mUniforms_ = {
        {
            .label="uProjection",
            .dataStr="",
            .values={},
            .enabled=true,
            .binding=0, //binding
            .systemUniform=SystemUniform::CAMERA_PROJ
        },
        {
            .label="uView",
            .dataStr="",
            .values={},
            .enabled=true,
            .binding=0, //binding
            .systemUniform=SystemUniform::CAMERA_VIEW
        },
        {
            .label="uModel",
            .dataStr="",
            .values={},
            .enabled=true,
            .binding=0, //binding
            .systemUniform=SystemUniform::MODEL
        }
    };
}

ShaderToolSceneGUI::~ShaderToolSceneGUI() {}

void ShaderToolSceneGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings");
    {
        ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 0.40f));
        if (ImGui::Button("Back")) {
            mScene_.getApp().setScene(new menu_scene::MenuScene(mScene_.getApp()));
            mScene_.setRemove(true);
        }
        ImGui::PopStyleColor();
        ImGui::Separator();
        ImGui::Text("Shader Tool Scene");
        ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));
        if (ImGui::Checkbox("vSync", &mVSyncEnabled_)) {
            ((clay::WindowDesktop*)mScene_.getApp().getWindow())->setVSync(mVSyncEnabled_);
        }
        ImGui::Separator();
        // Camera control
        buildCameraSection();
        ImGui::Separator();
        buildModelTransformSection();
        ImGui::Separator();
        buildShaderSection();
    }
    ImGui::End();
}

void ShaderToolSceneGUI::buildCameraSection() {
    ImGui::Text("Camera");

    ImGui::Text("Camera Mode");

    if (ImGui::RadioButton("Perspective", &mCameraMode_, 0)) {
        mScene_.getFocusCamera()->setMode(static_cast<clay::Camera::CameraMode>(mCameraMode_));
    }
    ImGui::SameLine();
    if (ImGui::RadioButton("Orthogonal", &mCameraMode_, 1)) {
        mScene_.getFocusCamera()->setMode(static_cast<clay::Camera::CameraMode>(mCameraMode_));
    }

    ImGui::Text("Camera Movement");
    glm::vec3 camPosition = mScene_.getFocusCamera()->getPosition();
    ImGui::Text(
        "Position: %.2f %.2f %.2f",
        camPosition.x,
        camPosition.y,
        camPosition.z
    );
    glm::vec3 camForward = mScene_.getFocusCamera()->getForward();
    ImGui::Text(
        "Direction: %.2f %.2f %.2f",
        camForward.x,
        camForward.y,
        camForward.z
    );
    ImGui::Text(
        "FOV: %.2f",
        mScene_.getFocusCamera()->getFOV()
    );
}

void ShaderToolSceneGUI::buildShaderSection() {
    static ImGuiInputTextFlags flags = ImGuiInputTextFlags_AllowTabInput; // Enable tab input

    ImGui::Checkbox("HDR", &mHDREnabled_);

    ImGui::Text("Mesh");
    ImGui::SameLine();
    // TODO replace with BeginComboBox and use mMeshList_
    if (ImGui::Combo(
        "##MeshSelect",
        &mSelectedMeshIndex_,
        meshLabels_.data(), 
        static_cast<int>(meshLabels_.size())
    )) {
        mScene_.setMesh(mMeshList_[mSelectedMeshIndex_].second);
    }
    ImGui::SameLine();
    if (ImGui::Button("Add##AddMesh")) {
        ImGui::OpenPopup("Load Mesh");
    }

    if (ImGui::BeginPopupModal("Load Mesh", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
        static char labelBuffer[128] = "";
        static char filePathLabel[128] = "";

        static std::string errorMessage = "";

        ImGui::Text("Label:");
        ImGui::SameLine();
        if (ImGui::InputText("##MeshLabel", labelBuffer, IM_ARRAYSIZE(labelBuffer))) {
            // TODO check if label is already used
            // if (mScene_.getResources()) {

            // }
        }
        ImGui::Text("Mesh Path:");
        ImGui::SameLine();
        ImGui::InputText("##MeshPath", filePathLabel, IM_ARRAYSIZE(filePathLabel));

        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f)); // Set text color to red
        ImGui::Text("%s", errorMessage.c_str());
        ImGui::PopStyleColor(); 


        if (ImGui::Button("Load Mesh")) {
            if (std::filesystem::exists(filePathLabel) && std::filesystem::is_regular_file(filePathLabel)) {
                LOG_I("LOAD Filepath %s", filePathLabel);
                errorMessage = "";
            } else {
                errorMessage = "Invalid File path";
            }
        }
        
        ImGui::SameLine();
        
        if (ImGui::Button("Close")) {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    ImGui::Separator();

    if (ImGui::CollapsingHeader("Uniforms")) {
        for (int i = 0; i < mUniforms_.size(); ++i) {
            ImGui::PushID(i);
            ImGui::BeginGroup();
            {
                ImGui::Text("Label:");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(100.0f);
                ImGui::InputText("##Label", mUniforms_[i].label, sizeof(mUniforms_[i].label));
                ImGui::SameLine();

                if (mUniforms_[i].systemUniform == SystemUniform::NONE) {
                    ImGui::Text("Data:");
                    ImGui::SameLine();
                    ImGui::SetNextItemWidth(100.0f);
                    if (ImGui::InputText("##Data", mUniforms_[i].dataStr, sizeof(mUniforms_[i].label))) {
                        mUniforms_[i].values = parseFloatString(mUniforms_[i].dataStr);
                    }
                    ImGui::SameLine();
                }

                ImGui::Text("System Value:");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(100.0f);

                ImGui::PushID("SystemValue");
                if (ImGui::BeginCombo("##SelectSystemValue", mSystemValues_[(int)mUniforms_[i].systemUniform].c_str())) {
                    for (int j = 0; j < mSystemValues_.size(); j++) {
                        bool isSelected = ((int)mUniforms_[i].systemUniform == j);
                        if (ImGui::Selectable(mSystemValues_[j].c_str(), isSelected)) {
                            mUniforms_[i].systemUniform = (SystemUniform)j;
                        }
                    }
                    ImGui::EndCombo();
                }
                ImGui::PopID();

                ImGui::SameLine();
                ImGui::Text("Enabled:");
                ImGui::SameLine();
                ImGui::Checkbox("##EnabledUniform", &mUniforms_[i].enabled);
                ImGui::SameLine();
                ImGui::Button("Remove##SystemValue");
            }
            ImGui::EndGroup();
            ImGui::PopID();
        }
        ImGui::Text("Texture Uniforms:");
        for (int i = 0; i < mTextureUniforms_.size(); ++i) {
            ImGui::PushID(i);
            ImGui::BeginGroup();
            {
                ImGui::Text("Label:");
                ImGui::SameLine();
                ImGui::SetNextItemWidth(100.0f);
                ImGui::InputText("##TextureUniformLabel", mTextureUniforms_[i].label, sizeof(mTextureUniforms_[i].label));
                ImGui::SameLine();

                ImGui::Text("Texture");
                ImGui::SameLine();
                
                {
                    ImGui::SetNextItemWidth(100.0f);
                    ImGui::PushID("TextureOptions");
                    if (ImGui::BeginCombo("##SelectTextureUniform", mTextureNamesById_[mTextureUniforms_[i].textureId].c_str())) {
                        for (const auto& [textureId, textureName]: mTextureNamesById_) {
                            bool isSelected = (mTextureUniforms_[i].textureId == textureId);
                            if (ImGui::Selectable(textureName.c_str(), isSelected)) {
                                mTextureUniforms_[i].textureId = textureId;
                            }
                            // Show the image preview inside the dropdown
                            ImGui::Image(textureId, ImVec2(50, 50));  
                        }
                        ImGui::EndCombo();
                    }
                    ImGui::PopID();
                }

                ImGui::SameLine();
                ImGui::Image(mTextureUniforms_[i].textureId, ImVec2(50, 50)); 

                ImGui::SameLine();
                ImGui::Text("Enabled:");
                ImGui::SameLine();
                ImGui::Checkbox(("##EnabledTextureUniform"), &mTextureUniforms_[i].enabled);
                ImGui::SameLine();
                ImGui::Button("Remove##TextureUniform");
            }
            ImGui::EndGroup();
            ImGui::PopID();
        }

        if (ImGui::Button("Add Uniform")) {
            mUniforms_.emplace_back();
        }
        ImGui::SameLine();
        // for uniforms textures, select from a drop down list. If you want to add new texture, use a "Load GUI" to add to this list
        if (ImGui::Button("Add Texture")) {
            mTextureUniforms_.push_back({"", (int)mTextureNamesById_.begin()->first, 0, true});
        }

        {
            // Button to open the modal
            if (ImGui::Button("Load Texture##OpenModal")) {
                ImGui::OpenPopup("Load Texture");
            }

            // Define the modal popup
            if (ImGui::BeginPopupModal("Load Texture", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
                static char inputBuffer1[128] = "";
                static char inputBuffer2[128] = "";

                static std::string errorMessage = "";

                ImGui::Text("Label:");
                ImGui::SameLine();
                if (ImGui::InputText("##TextureLabel", inputBuffer1, IM_ARRAYSIZE(inputBuffer1))) {
                    // TODO check if label is already used
                    // if (mScene_.getResources()) {

                    // }
                }
                ImGui::Text("Image Path:");
                ImGui::SameLine();
                ImGui::InputText("##ImagePath", inputBuffer2, IM_ARRAYSIZE(inputBuffer2));

                // TODO gamma correction checkbox

                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 0.0f, 0.0f, 1.0f));
                ImGui::Text("%s", errorMessage.c_str());
                ImGui::PopStyleColor(); 

                if (ImGui::Button("Load Texture")) {
                    if (std::filesystem::exists(inputBuffer2) && std::filesystem::is_regular_file(inputBuffer2)) {
                        LOG_I("LOAD Filepath %s", inputBuffer2);
                        errorMessage = "";
                    } else {
                        errorMessage = "Invalid File path";
                    }
                }
                
                ImGui::SameLine();
                
                if (ImGui::Button("Close")) {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
        }

        if (ImGui::Button("Apply Uniforms")) {
            mScene_.setUniforms(mUniforms_, mTextureUniforms_);
        }
    }

    // todo replace with mDrawPrimitives_
    static const char* drawModes[] = {"Triangles", "Lines",  "Points", "Line Strips"};
    static int selectedDrawMode = 0;

    ImGui::Text("Draw Mode");
    ImGui::SameLine();
    if (ImGui::Combo("##DrawMode", &selectedDrawMode, drawModes, IM_ARRAYSIZE(drawModes))) {}

    ImGui::Text("Shader Stages");

    if (ImGui::CollapsingHeader("Vertex Shader")) {
        ImGui::InputTextMultiline("##VertexEditor", vertexBuffer, sizeof(vertexBuffer), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), flags);
    }

    // TODO load shaders with a modal that has a section for each shader
    if (ImGui::CollapsingHeader("Tesselation Control Shader")) { 
        ImGui::Checkbox("Default##TesselationControl", &tesselationControlDefault);
        ImGui::InputTextMultiline("##TesselationControlEditor", tesselationControlBuffer, sizeof(tesselationControlBuffer), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), flags);
    }

    if (ImGui::CollapsingHeader("Tesselation Evaluation Shader")) {
        ImGui::Checkbox("Default##TesselationEvaluation", &tesselationEvaluationDefault);
        ImGui::InputTextMultiline("##TesselationEvaluationEditor", tesselationEvaluationBuffer, sizeof(tesselationEvaluationBuffer), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), flags);
    }

    if (ImGui::CollapsingHeader("Geometry Shader")) {
        ImGui::Checkbox("Default##Geometry", &geometryDefault);
        ImGui::InputTextMultiline("##GeometryEditor", geometryBuffer, sizeof(geometryBuffer), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), flags);
    }

    if (ImGui::CollapsingHeader("Fragment Shader")) {
        ImGui::InputTextMultiline("##FragmentEditor", fragmentBuffer, sizeof(fragmentBuffer), ImVec2(-FLT_MIN, ImGui::GetTextLineHeight() * 16), flags);
    }
    ImGui::NewLine();

    if (ImGui::Button("Compile")) {
        compileShader();
    }
    ImGui::SameLine();
    ImGui::Text("Status: N/A");

    static char tempBuffer[256];
    ImGui::Text("Save Name");
    ImGui::SameLine();
    ImGui::SetNextItemWidth(100.0f);
    ImGui::InputText("##SaveName", tempBuffer, sizeof(tempBuffer));
    ImGui::SameLine();
    if (ImGui::Button("Save")) { // for now just output all to ./<input_file_name>.stage
        if (strlen(tempBuffer) != 0) {
            saveShaders(tempBuffer);
        } else {
            LOG_I("Invalid save name");
        }
    }
}

void ShaderToolSceneGUI::compileShader() {
    clay::ShaderProgram* shaderProgram = new clay::ShaderProgram(*mScene_.getApp().getGraphicsAPI());

    try {
        // vertex
        shaderProgram->addShader({
            .type = clay::ShaderCreateInfo::Type::VERTEX,
            .sourceData = vertexBuffer,
            .sourceSize = strlen(vertexBuffer) + 1
        });
        // fragment
        shaderProgram->addShader({
            .type = clay::ShaderCreateInfo::Type::FRAGMENT,
            .sourceData = fragmentBuffer,
            .sourceSize = strlen(fragmentBuffer) + 1
        });

        // tesselation control
        if (!tesselationControlDefault) {
            shaderProgram->addShader({
                .type = clay::ShaderCreateInfo::Type::TESSELLATION_CONTROL,
                .sourceData = tesselationControlBuffer,
                .sourceSize = strlen(tesselationControlBuffer) + 1
            });
        }
        // tesselation evaluation
        if (!tesselationEvaluationDefault) {
            shaderProgram->addShader({
                .type = clay::ShaderCreateInfo::Type::TESSELLATION_EVALUATION,
                .sourceData = tesselationEvaluationBuffer,
                .sourceSize = strlen(tesselationEvaluationBuffer) + 1
            });
        }
        // geometry shader
        if (!geometryDefault) {
            shaderProgram->addShader({
                .type = clay::ShaderCreateInfo::Type::GEOMETRY,
                .sourceData = geometryBuffer,
                .sourceSize = strlen(geometryBuffer) + 1
            });
        }

        shaderProgram->linkProgram();
        // send to scene
        mScene_.setShader(shaderProgram);
        LOG_I("Compile success");

    } catch (const std::runtime_error& e) {
        LOG_E("Error in shader Compile");
        // TODO delete shaderProgram on error
    }
}

void ShaderToolSceneGUI::buildModelTransformSection() {
    // Decompose transformation matrix into position, rotation, and scale
    glm::vec3 position, scale, skew;
    glm::vec4 perspective;
    glm::quat rotationQuat;
    
    glm::decompose(mTransformMat_, scale, rotationQuat, position, skew, perspective);
    
    // Convert quaternion rotation to Euler angles
    glm::vec3 rotation = glm::eulerAngles(rotationQuat); 
    rotation = glm::degrees(rotation); // Convert to degrees for UI

    float positionArr[3] = { position.x, position.y, position.z };
    float rotationArr[3] = { rotation.x, rotation.y, rotation.z };
    float scaleArr[3] = { scale.x, scale.y, scale.z };

    if (ImGui::SliderFloat3("Position##Transform", positionArr, -10.f, 10.f, "%.2f")) {
        // Update position in transformation matrix
        mTransformMat_[3] = glm::vec4(positionArr[0], positionArr[1], positionArr[2], 1.0f);
        mScene_.setTransformMat(mTransformMat_);
    }

    if (ImGui::SliderFloat3("Rotation##Transform", rotationArr, -180.f, 180.f, "%.2f")) {
        // Convert back to radians
        glm::vec3 newRotation = glm::radians(glm::vec3(rotationArr[0], rotationArr[1], rotationArr[2]));

        // Construct a new rotation matrix
        glm::mat4 rotationMat = glm::eulerAngleXYZ(newRotation.x, newRotation.y, newRotation.z);

        // Preserve position and scale while applying new rotation
        glm::vec3 prevPosition(mTransformMat_[3]);
        glm::mat4 scaleMat = glm::scale(glm::mat4(1.0f), scale);
        mTransformMat_ = glm::translate(glm::mat4(1.0f), prevPosition) * rotationMat * scaleMat;
        mScene_.setTransformMat(mTransformMat_);
    }

    if (ImGui::SliderFloat3("Scale##Transform", scaleArr, 0.1f, 10.f, "%.2f")) {
        // Apply scale to transformation matrix
        glm::vec3 prevPosition(mTransformMat_[3]);
        glm::mat4 rotationMat = glm::mat4_cast(rotationQuat); // Convert quaternion to matrix
        mTransformMat_ = glm::translate(glm::mat4(1.0f), prevPosition) * rotationMat * glm::scale(glm::mat4(1.0f), glm::vec3(scaleArr[0], scaleArr[1], scaleArr[2]));
        mScene_.setTransformMat(mTransformMat_);
    }
}

void ShaderToolSceneGUI::saveShaders(const std::string shaderName) {
    auto save = [](const std::string& filename, const char* buffer) {
        std::ofstream file(filename, std::ios::binary); // Open file in binary mode
        if (!file) {
            std::cerr << "Error: Unable to open file for writing: " << filename << std::endl;
            return;
        }

        // Determine the actual size of content in the buffer
        size_t length = std::strlen(buffer);
        file.write(buffer, length);
        file.close();

        if (!file) {
            std::cerr << "Error: Failed to write to file: " << filename << std::endl;
        }
    };

    // Save different shader types
    save(shaderName + ".vert", vertexBuffer);
    save(shaderName + ".frag", fragmentBuffer);
    if (!tesselationControlDefault) {
        save(shaderName + ".tesc", tesselationControlBuffer);
    }
    if (!tesselationEvaluationDefault) {
        save(shaderName + ".tese", tesselationEvaluationBuffer);
    }
    if (!geometryDefault) {
        save(shaderName + ".geom", geometryBuffer);
    }
}

std::vector<float> ShaderToolSceneGUI::parseFloatString(const std::string& input) {
    std::vector<float> result;
    std::istringstream iss(input);
    float value;
    std::string token;
    
    // Make a copy of the input to validate
    std::istringstream validateStream(input);
    while (validateStream >> token) {
        try {
            std::stof(token); // Try to convert each token to a float
        } catch (const std::exception&) {
            return {}; // Return empty vector if conversion fails
        }
    }

    // If validation passed, parse the actual values
    while (iss >> value) {
        result.push_back(value);
    }

    return result;
}

} // namespace shader_tool_scene