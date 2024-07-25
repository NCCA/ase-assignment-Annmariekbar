//
// Created by s5417041 on 18/07/24.
//

#include "Enemy.h"

// Constructor definition
Enemy::Enemy(const std::string &name, float dmg, const ngl::Vec3 &col)
        : name(name), damage(dmg), colour(col) {}

// Implementation of damage retrieval method
float Enemy::getDmg() const {
    return damage;
}

// Implementation of colour retrieval method
ngl::Vec3 Enemy::getCol() const {
    return colour;
}


