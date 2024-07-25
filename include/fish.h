//
// Created by s5417041 on 05/07/24.
//

#ifndef BULLETNGLBUILD_FISH_H
#define BULLETNGLBUILD_FISH_H

#include <iostream>
#include "WindowParams.h"
#include "ngl/Vec3.h"
#include <ngl/Mat4.h>

using namespace ngl;
class Player {
public:
    Player();
    //-----------------------------------------------
    ///@brief sets position of the player
    void setPosition(float x, float y, float z);
    //-----------------------------------------------
    ///@brief overloaded function to accept ngl::Vec3
    void setPosition(const ngl::Vec3& pos)
    {
        setPosition(pos.m_x, pos.m_y, pos.m_z);
    }
    ngl::Vec3 getPosition();
    //-----------------------------------------------
    ///@brief retrieves the health of the player
    float getHealth();
    //-----------------------------------------------
    ///@brief decreases the health of the player and returns if alive (1) or dead (0)
    bool decreaseHealth(float);
    //-----------------------------------------------
    ///@brief resets the health
    void resetHealth();
    //-----------------------------------------------


private:
    ngl::Vec3  myPos;
    float health;

};

#endif // BULLETNGLBUILD_FISH_H
