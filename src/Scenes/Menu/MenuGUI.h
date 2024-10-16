#pragma once
// ClayEngine
#include <Clay/GUI/ImGuiComponent.h>

namespace menu_scene {
// Forward declare Scene
class MenuScene;

class MenuGUI: public clay::ImGuiComponent {
public:
    /**
     * Constructor
     * @param theScene The scene this gui is for
     */
    MenuGUI(MenuScene& theScene);

    /** Destructor */
    ~MenuGUI();

    /** Build the GUI ImGui components every frame */
    void buildImGui() override;

private:
    /** The Scene this GUI is for */
    MenuScene& mScene_;
};
} // namespace menu_scene