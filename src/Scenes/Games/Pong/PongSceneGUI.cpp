// ClayEngine
#include <clay/application/App.h>
// project
#include "Scenes/Games/GamesScene.h"
#include "Scenes/Games/Pong/PongScene.h"
// class
#include "Scenes/Games/Pong/PongSceneGUI.h"

namespace pong {

PongSceneGUI::PongSceneGUI(PongScene& theScene)
    : mScene_(theScene) {
    mVSyncEnabled_ = mScene_.getApp().getWindow().getGLFWSwapInterval();
    mVolume_ = mScene_.getApp().getAudioManger().getGain();
}

PongSceneGUI::~PongSceneGUI() {}

void PongSceneGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Settings");
    ImGui::SetWindowCollapsed(true, ImGuiCond_FirstUseEver);
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 0.40f));
    if (ImGui::Button("Back")) {
        mScene_.getApp().setScene(new GamesScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    ImGui::PopStyleColor();
    ImGui::Text("Pong Scene");
    ImGui::Text("FPS: %.1f", double(ImGui::GetIO().Framerate));
    if (ImGui::Checkbox("vSync", &mVSyncEnabled_)) {
        mScene_.getApp().getWindow().setVSync(mVSyncEnabled_);
    }
    if (ImGui::SliderFloat("Volume", &mVolume_, 0.f, 1.f)) {
        mScene_.getApp().getAudioManger().setGain(mVolume_);
    }

    ImGui::Text("Controls:");
    ImGui::Text("Left Paddle: Numpad 7,1");
    ImGui::Text("Right Paddle: Numpad 9,3");

    ImGui::End();
}

} // namespace pong