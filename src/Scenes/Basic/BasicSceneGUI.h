#pragma once
// ClayEngine
#include <clay/gui/desktop/ImGuiComponent.h>

namespace basic_scene {
// Forward declare Scene
class BasicScene;

class BasicSceneGUI: public clay::ImGuiComponent {
public:
    /**
     * Constructor
     * @param theScene The scene this gui is for
     */
    BasicSceneGUI(BasicScene& theScene);

    /** Destructor */
    ~BasicSceneGUI();

    /** Build the GUI ImGui components every frame */
    void buildImGui() override;

private:
    /** Build the section to list/control the camera of this scene */
    void buildCameraSection();

    /** Build the section to list/control the Entities of the Scene*/
    void buildEntitySection();

    /** The Scene this GUI is for */
    BasicScene& mScene_;
    /** If the GUI is set to enable VSync */
    bool mVSyncEnabled_;
    /** The Camera Mode this GUI applies*/
    int mCameraMode_;
    /** The Entity index selected from the Entity List */
    int mSelectedEntityIndex_ = 0;
    /** The Renderable index selected from the Entity List */
    int mSelectedRenderableIndex_ = 0;
};

} // namespace basic_scene