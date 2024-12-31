#pragma once
// ClayEngine
#include <clay/gui/ImGuiComponent.h>

// Forward declare Scene
class GamesScene;

class GamesSceneGUI : public clay::ImGuiComponent {
public:
    /**
     * Constructor
     * @param theScene The scene this gui is for
     */
    GamesSceneGUI(GamesScene& theScene);

    /** Destructor */
    ~GamesSceneGUI();

    /** Build the GUI ImGui components every frame */
    void buildImGui() override;

private:
    /** The Scene this GUI is for */
    GamesScene& mScene_;
};