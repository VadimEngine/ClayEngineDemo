#pragma once
// ClayEngine
#include <clay/gui/desktop/ImGuiComponent.h>

namespace scene_2d {
// Forward declare Scene
class Scene2d;

class Scene2dGUI : public clay::ImGuiComponent {
public:
    /**
     * Constructor
     * @param theScene The scene this gui is for
     */
    Scene2dGUI(Scene2d& theScene);

    /** Destructor */
    ~Scene2dGUI();

    /** Build the GUI ImGui components every frame */
    void buildImGui() override;

private:
    /** Build the section to list/control the camera of this scene */
    void buildCameraSection();

    /** Build the section to list/control the Entities of the Scene*/
    void buildEntitySection();

    /** The Scene this GUI is for */
    Scene2d& mScene_;
    /** If the GUI is set to enable VSync */
    bool mVSyncEnabled_;
    /** The Camera Mode this GUI applies*/
    int mCameraMode_;
    /** The Entity index selected from the Entity List */
    int mSelectedEntityIndex_ = 0;
    /** The Renderable index selected from the Entity List */
    int mSelectedRenderableIndex_ = 0;
};
} // namespace scene_2d