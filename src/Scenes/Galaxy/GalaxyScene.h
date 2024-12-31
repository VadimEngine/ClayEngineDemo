 #pragma once
// ClayEngine
#include <clay/application/CameraController.h>
#include <clay/application/Resource.h>
#include <clay/application/Scene.h>
#include <clay/entity/Entity.h>
#include <clay/entity/render/ModelRenderable.h>
// project
#include "Scenes/Galaxy/GalaxySceneGUI.h"
#include "Scenes/Galaxy/MoonEntity.h"
#include "Scenes/Galaxy/PlanetEntity.h"
#include "Scenes/Galaxy/SunEntity.h"

namespace galaxy {
class GalaxyScene : public clay::Scene {
public:
    /**
     * Constructor
     * @param theApp Parent app handling this Scene
     */
    GalaxyScene(clay::App& theApp);

    /** Destructor */
    ~GalaxyScene();

    /**
     * Update the Scene
     * @param dt Time since last update in seconds
     */
    void update(const float dt) override;

    /**
     * Render this scene
     * @param renderer Rendering helper
     */
    void render(clay::Renderer& renderer) override;

    /**
     * Render just the gui for this scene
     */
    void renderGUI() override;

    /** Get the Sun Entity of this scene*/
    SunEntity* getSunEntity();
    /** Get the Planet Entity of this scene */
    PlanetEntity* getPlanetEntity();
    /** Get the Moon Entity of this scene */
    MoonEntity* getMoonEntity();

    /** Build/load the resources for this scene*/
    void assembleResources() override;

    /** Get this scene resources */
    clay::Resource& getResources();

    /**
     * @brief Respond to mouse wheel events
     *
     * @param mouseEvent Mouse Wheel event
     */
    void onMouseWheel(const clay::InputHandler::MouseEvent& mouseEvent) override;

private:
    /** GUI for this scene*/
    GalaxySceneGUI mGui_;
    /** Camera Controller */
    clay::CameraController mCameraController_;
    /** Entities rendered in this Scene */
    std::vector<clay::Entity*> mEntities_;
    /** Pointer to the Sun Entity of this Scene */
    SunEntity* sunEntity_ = nullptr;
    /** Pointer to the planet Entity of this Scene*/
    PlanetEntity* planetEntity_ = nullptr;
    /** Pointer to the moon Entity of this Scene*/
    MoonEntity* moonEntity_ = nullptr;
};

} // namespace galaxy