#pragma once
// project
#include <Clay/Entity/Entity.h>
#include <Clay/Entity/Physics/Collider2.h>
#include <Clay/Entity/Render/BaseRenderable.h>
#include <Clay/Entity/Render/SpriteRenderable.h>
#include <Clay/Graphics/Renderer.h>
#include <Clay/Graphics/SpriteSheet.h>

namespace rpg_2d {

class Player : public clay::Entity {
private:
    float speed = 5.0f;
public:
    // TODO try Collider2.h

    clay::Collider2* mpCollider_ = nullptr;

    clay::BoxCollider2D* mpBoxCollider_ = nullptr;

    clay::SpriteSheet::Sprite mSprite_;

    Player(clay::Scene& scene);

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