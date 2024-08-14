//
// Created by s5417041 on 17/07/24.
//

#ifndef BULLETNGLBUILD_LEVEL_H
#define BULLETNGLBUILD_LEVEL_H
#include <ngl/Vec3.h>
#include <vector>
#include <iostream>
#include <ngl/Random.h>
#include <utility> // For std::pair
#include <map>
#include <cmath>

//----------------------------------------
///@brief data for the obstacles
struct obsData
{
    int height;
    ngl::Vec3 position;
    std::string obj;
};
//----------------------------------------

class Level {
public:
    //----------------------------------------
    ///@brief Constructor declaration
    Level();
    //----------------------------------------
    ///@brief finds level number
    int getLevelNum();
    //----------------------------------------
    ///@brief map generation
    std::map<int, struct obsData> loadMap();
    //----------------------------------------
    ///@brief increments level
    int incrementLevel();
    //----------------------------------------
    ///@brief increments level
    void difficultySetter(int);
    //----------------------------------------
    float distance(const ngl::Vec3 &a, const ngl::Vec3 &b);
    bool isPositionValid(const ngl::Vec3 &newPos, const std::map<int, obsData> &mapData, float minDistance);
    //----------------------------------------
    ///@brief resets the level
    void resetLevel();
    //----------------------------------------
private:

    //----------------------------------------
    ///@brief current level
    int levelNum;
    //----------------------------------------
    ///@brief build of the map
    std::map<int, obsData> mapData;// Map to store height and position pairs
    //----------------------------------------
    ///@brief the amount of obstacles in the map
    int obs;
    //----------------------------------------
    ///@brief the maximum amount of obstacles on top of each other
    int maxHeight;
    //----------------------------------------
    float minDistance;
    //----------------------------------------


};


#endif //BULLETNGLBUILD_LEVEL_H
