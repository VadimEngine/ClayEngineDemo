// standard lib
#include <filesystem>
// ClayEngine
#include <Clay/Application/App.h>
// project
#include "Scenes/Menu/MenuScene.h"

int main() {
    LOG_IV("Starting Application from %s", std::filesystem::current_path().string().c_str());
    clay::Resource::SRC_PATH = std::filesystem::current_path() / "res";
    clay::Resource::RESOURCE_PATH = std::filesystem::current_path() / "res";
    clay::App theApp;
    theApp.setScene(new menu_scene::MenuScene(theApp));
    theApp.run();

    return 0;
}