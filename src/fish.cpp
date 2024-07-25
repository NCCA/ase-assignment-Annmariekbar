
// Created by s5417041 on 05/07/24.

#include "fish.h"

Player::Player()
{
    //Initialize fishPos to (0, 0, 0) in the constructor
    myPos = ngl::Vec3(0.0f, 0.0f, 0.0f);
    health = 100.0f;
}

void Player::setPosition(float x,float y,float z)
{
//    Sets position using the variables in the parameters
    Player::myPos.m_x = x;
    Player::myPos.m_y = y;
    Player::myPos.m_z = z;
}

ngl::Vec3 Player::getPosition()
{
    return myPos;
}

float Player::getHealth()
{
    return health;
};

bool Player::decreaseHealth(float dmge)
{
    health -= dmge;
    if (health <= 0) return 0;
    else return 1;
};

void Player::resetHealth()
{
    health = 100;
}



