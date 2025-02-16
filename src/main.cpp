// standard lib
#include <filesystem>
// ClayEngine
#include <clay/application/desktop/AppDesktop.h>
#include <clay/utils/desktop/UtilsDesktop.h>
#include <clay/gui/desktop/WindowDesktop.h>
// project
#include "Scenes/Menu/MenuScene.h"

int main() {
    LOG_IV("Starting Application from %s", std::filesystem::current_path().string().c_str());
    // Set resource path
    clay::Resources::RESOURCE_PATH = DEMO_RESOURCE_PATH;
    // Set resource load method to desktop mode
    clay::Resources::loadFileToMemory = clay::utils::loadFileToMemory_desktop; 

    clay::AppDesktop theApp;

    // Create Desktop window
    std::unique_ptr<clay::WindowDesktop> pWindow = std::make_unique<clay::WindowDesktop>("ClayEngine Demo", 800, 600);

    // TODO set input handler

    theApp.setWindow(std::move(pWindow));

    // TODO Load app resources
    theApp.initialize();
    theApp.setScene(new menu_scene::MenuScene(theApp));
    // start application
    theApp.run();

    return 0;
}