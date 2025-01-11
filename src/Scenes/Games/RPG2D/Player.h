#pragma once
// project
#include <clay/entity/Entity.h>
#include <clay/entity/physics/Collider2.h>
#include <clay/entity/render/BaseRenderable.h>
#include <clay/entity/render/SpriteRenderable.h>
#include <clay/graphics/common/Renderer.h>
#include <clay/graphics/common/SpriteSheet.h>

namespace rpg_2d {

class Player : public clay::Entity {
private:
    float speed = 5.0f;
public:
    // TODO try Collider2.h

    clay::Collider2* mpCollider_ = nullptr;

    clay::BoxCollider2D* mpBoxCollider_ = nullptr;

    clay::SpriteSheet::Sprite mSprite_;

    Player(clay::BaseScene& scene);

    ~Player();

    void update(float dt) override;

    void render(const clay::Renderer& theRenderer) const override;

    void move(glm::vec3 direction, float dt);

    clay::Collider2& getCollider();

    clay::Collider& getColliderNew();


    void separateFromMOB2(clay::Collider2& thisCollider, clay::Collider2& otherCollider);

    void separateFromMOB(clay::Collider& thisCollider, clay::Collider& otherCollider);

};

} // namespace rpg_2d