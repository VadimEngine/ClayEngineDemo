// ClayEngine
#include <clay/application/App.h>
// project
#include "Scenes/Basic/BasicScene.h"
#include "Scenes/Galaxy/GalaxyScene.h"
#include "Scenes/Games/GamesScene.h"
#include "Scenes/Lighting/LightingScene.h"
#include "Scenes/Menu/MenuScene.h"
#include "Scenes/PhysicsScene/PhysicsScene.h"
#include "Scenes/Scene2d/Scene2d.h"
// class
#include "Scenes/Menu/MenuGUI.h"

namespace menu_scene {
MenuGUI::MenuGUI(MenuScene& theScene)
    : mScene_(theScene) {}

MenuGUI::~MenuGUI() {}

void MenuGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Menu", NULL, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoTitleBar);
    ImGui::Text("OpenGL Sandbox");

    if (ImGui::Button("Basic Scene")) {
        mScene_.getApp().setScene(new basic_scene::BasicScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    if (ImGui::Button("Lighting Scene")) {
        mScene_.getApp().setScene(new lighting_scene::LightingScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    if (ImGui::Button("Scene 2d")) {
        mScene_.getApp().setScene(new scene_2d::Scene2d(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    if (ImGui::Button("Physics Scene")) {
        mScene_.getApp().setScene(new physics_scene::PhysicsScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    if (ImGui::Button("Galaxy")) {
        mScene_.getApp().setScene(new galaxy::GalaxyScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    if (ImGui::Button("Games")) {
        mScene_.getApp().setScene(new GamesScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 0.40f));
    if (ImGui::Button("Exit")) {
        mScene_.getApp().quit();
        mScene_.setRemove(true);
    }
    // Restore the default color
    ImGui::PopStyleColor();

    ImGui::End();
}
} // namespace menu_scene