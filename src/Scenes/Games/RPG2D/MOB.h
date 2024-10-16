#pragma once
// project
#include <Clay/Entity/Entity.h>
#include <Clay/Entity/Render/BaseRenderable.h>
#include <Clay/Entity/Render/SpriteRenderable.h>
#include <Clay/Entity/Physics/Collider2.h>
#include <Clay/Graphics/Renderer.h>
#include <Clay/Graphics/SpriteSheet.h>

namespace rpg_2d {
class MOB : public clay::Entity {
public:
    // TODO try Collider2.h
    clay::Collider2* mpCollider_ = nullptr;

    clay::BoxCollider2D* mpBoxCollider_ = nullptr;

    clay::SpriteSheet::Sprite mSprite_;


    MOB(clay::Scene& scene);

    ~MOB();

    void update(float dt) override;

    void move(glm::vec3 direction, float dt);

    clay::Collider2& getCollider();

    clay::Collider& getColliderNew();

private:
    float speed = 5.0f;
};

} // namespace rpg_2d