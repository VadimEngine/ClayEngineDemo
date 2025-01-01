// standard lib
#include <filesystem>
// ClayEngine
#include <clay/application/App.h>
#include <clay/utils/desktop/DesktopUtils.h>
// project
#include "Scenes/Menu/MenuScene.h"

int main() {
    LOG_IV("Starting Application from %s", std::filesystem::current_path().string().c_str());
    clay::Resource::RESOURCE_PATH = DEMO_RESOURCE_PATH;

    clay::Resource::loadFileToMemory = clay::utils::loadFileToMemory_desktop; 

    clay::App theApp;
    theApp.setScene(new menu_scene::MenuScene(theApp));
    theApp.run();

    return 0;
}