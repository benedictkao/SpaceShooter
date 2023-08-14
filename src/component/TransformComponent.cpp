#include "TransformComponent.h"

int TransformComponent::centerX() const { return position.x + width / 2; }

int TransformComponent::centerY() const { return position.y + height / 2; }