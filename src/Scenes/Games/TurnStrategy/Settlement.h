#pragma once
// standard lib
#include <array>
#include <string>
#include <unordered_set>
// ClayEngine
#include <clay/entity/Entity.h>
#include <clay/entity/render/ModelRenderable.h>
#include <clay/entity/render/SpriteRenderable.h>
#include <clay/entity/render/TextRenderable.h>
#include <clay/graphics/common/SpriteSheet.h>
#include <clay/utils/common/Utils.h>

namespace turn_strategy {
// forward declare TurnStrategyGame
class TurnStrategyGame;

class Settlement : public clay::Entity {
public:
    /**
     * @brief Construct a new Settlement
     *
     * @param theGame The game this Settlement is in
     * @param pSprite Sprite for this settlement
     * @param tilePosition Position (world grid) of this settlement
     */
    Settlement(TurnStrategyGame& theGame, clay::SpriteSheet::Sprite* pSprite, glm::ivec2 tilePosition);

    /**
     * Update Settlement
     * @param dt Time since last update
     */
    void update(const float dt) override;

    /**
     * @brief Render Settlement
     *
     * @param theRenderer
     * @param theCamera
     */
    void render(const clay::Renderer& theRenderer) const override;

    /**
     * @brief Update name of this settlement
     *
     * @param newName New Name
     */
    void setName(const std::string& newName);

    /**
     * @brief Get the Name of this settlement
     */
    std::string getName() const;

    /**
     * @brief Add a tile as a territory for this settlement
     *
     * @param tilePosition tile grid position
     */
    void addTerritory(glm::ivec2 tilePosition);

    /**
     * @brief Reset this settlement for the next turn
     */
    void resetForTurn();

    /**
     * @brief Get the Size of this settlement (Number of territory tiles)
     */
    int getSize() const;

    /**
     * @brief Get the population of this settlement
     */
    int getPopulation() const;

    /**
     * @brief Update hte population of this settlement
     *
     * @param newPopulation
     */
    void setPopulation(int newPopulation);

    /**
     * @brief If this settlement can spawn a new unit no unit currently on settlement and enough population)
     */
    bool canSpawnUnit() const;

private:
    /** Set of territory tiles */
    std::unordered_set<glm::ivec2, clay::utils::Vec2Hash> territoryTiles;
    /** Settlement name */
    std::string mName_;
    /** Settlement size that grows ever few turns */
    int population = 1;
    /** how many tiles this settlement has (proportionate to population) */
    int size = 1;
    /** Renderable to shade in territory tiles */
    clay::ModelRenderable borderRenderable;
    /** Reference to the Label Text renderable */
    clay::TextRenderable* mLabelTextRenderable_ = nullptr;
    /** Game this Settlement is in */
    TurnStrategyGame& mGame_;
};
} // namespace turn_strategy