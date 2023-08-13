#pragma once

struct Vector2D {
	int x;
	int y;
};

struct TransformComponent {
	int entity;
	Vector2D position;
	Vector2D speed;
	int width;
	int height;
};