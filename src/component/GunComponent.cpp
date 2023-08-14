#include "GunComponent.h"

static constexpr auto NORMAL_AMMO_PATH = "../../../res/red-dot.png";
static constexpr auto NORMAL_AMMO_COOLDOWN = 10;
static constexpr auto NORMAL_AMMO_SPEED = 10;
static constexpr auto NORMAL_AMMO_WIDTH = 8;
static constexpr auto NORMAL_AMMO_HEIGHT = 8;

const Ammo Ammo::Normal = {NORMAL_AMMO_PATH, NORMAL_AMMO_COOLDOWN,
                           NORMAL_AMMO_SPEED, NORMAL_AMMO_WIDTH,
                           NORMAL_AMMO_HEIGHT};