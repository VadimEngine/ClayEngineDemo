// ClayEngine
#include <clay/application/App.h>
// project
#include "Scenes/Games/GamesScene.h"
#include "Scenes/Games/Pong/PongScene.h"
#include "Scenes/Games/RPG2D/RPG2DScene.h"
#include "Scenes/Games/TurnStrategy/TurnStrategyScene.h"
#include "Scenes/Games/Vessels/VesselsScene.h"
#include "Scenes/Menu/MenuScene.h"
// class
#include "Scenes/Games/GamesSceneGUI.h"

GamesSceneGUI::GamesSceneGUI(GamesScene& theScene)
    : mScene_(theScene) {
}

GamesSceneGUI::~GamesSceneGUI() {}

void GamesSceneGUI::buildImGui() {
    ImGui::SetNextWindowPos(ImVec2(0, 0));
    ImGui::SetNextWindowSize(ImVec2(250, 480), ImGuiCond_FirstUseEver);
    ImGui::Begin("Games");
    if (ImGui::Button("Pong")) {
        mScene_.getApp().setScene(new pong::PongScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    if (ImGui::Button("Turn-Based Strategy")) {
        mScene_.getApp().setScene(new turn_strategy::TurnStrategyScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    if (ImGui::Button("2D-RPG")) {
        mScene_.getApp().setScene(new rpg_2d::RPG2DScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    if (ImGui::Button("Vessels")) {
        mScene_.getApp().setScene(new vessels::VesselsScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(1.f, 0.f, 0.f, 0.40f));
    if (ImGui::Button("Back")) {
        mScene_.getApp().setScene(new menu_scene::MenuScene(mScene_.getApp()));
        mScene_.setRemove(true);
    }
    ImGui::PopStyleColor();
    ImGui::End();
}