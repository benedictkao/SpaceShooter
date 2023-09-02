#include "TextureSystem.h"
#include "utils/Math.h"

#include <iostream>

static constexpr auto ANIMATION_WIDTH{ 4 };
static constexpr auto ANIMATION_HEIGHT{ 4 };
static constexpr auto ANIMATION_FRAMES{ 16 };

TextureSystem::TextureSystem(EntityManager& em) : _em(em), _renderer(0) {}

void TextureSystem::setRenderer(SDL2::Renderer renderer) {
  _renderer = renderer;
}

void TextureSystem::updateAnimations() {
  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities) {
    if (_em.hasComponents(i, ComponentFlag::ANIMATION)) {
      AnimationComponent& animation = _em.getComponent<AnimationComponent>(i);
      TransformComponent& transform = _em.getComponent<TransformComponent>(i);

      SDL2::Rect src;
      src.x = animation.currFrame % ANIMATION_WIDTH * animation.width;
      src.y = animation.currFrame / ANIMATION_HEIGHT * animation.height;
      src.w = animation.width;
      src.h = animation.height;
      if (++animation.currFrame == ANIMATION_FRAMES)
        _em.scheduleRemoval(i);

      SDL2::Rect dest = { transform.position.x - transform.width / 2,
                          transform.position.y - transform.height / 2,
                          transform.width,
                          transform.height };
      SDL2::blit(animation.tex, _renderer, src, dest);
    }
  }
}

void TextureSystem::updateSprites() {
  const auto& activeEntities = _em.getActive();
  for (int i : activeEntities)
    if (_em.hasComponents(i, ComponentFlag::SPRITE))
      updateSprite(i);
}

void TextureSystem::updateSprite(int entity) {
  SDL2::Texture       tex = _em.getComponent<SpriteComponent>(entity).texture;
  TransformComponent& transform = _em.getComponent<TransformComponent>(entity);
  SDL2::Rect          dest      = { transform.position.x - transform.width / 2,
                                    transform.position.y - transform.height / 2,
                                    transform.width,
                                    transform.height };
  SDL2::blit(tex, _renderer, dest);
}