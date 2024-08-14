//
// Created by s5417041 on 18/07/24.
//

#ifndef BULLETNGLBUILD_ENEMY_H
#define BULLETNGLBUILD_ENEMY_H
#include "ngl/Vec3.h"
#include <string>


class Enemy {
public:
    //--------------Constructor-------------------------------------------------
    /// @brief Constructor to initialize the enemy with a name, damage, and color
    Enemy(const std::string &name, float dmg, const ngl::Vec3 &col);

    //--------------Methods-----------------------------------------------------
    /// @brief To retrieve damage
    float getDmg() const;

    /// @brief To retrieve color
    ngl::Vec3 getCol() const;

private:
    //--------------Attributes--------------------------------------------------
    const std::string name;
    float damage;
    ngl::Vec3 colour;

};


#endif //BULLETNGLBUILD_ENEMY_H
