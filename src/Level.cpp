//
// Created by s5417041 on 17/07/24.
//

#include "Level.h"

// Constructor to initialize levelNum to 1
Level::Level() : levelNum(1) {
    difficultySetter(levelNum);
}


int Level::incrementLevel()
{
    levelNum+= 1;
    difficultySetter(levelNum);
    return levelNum;
}

void Level::difficultySetter(int levelNum)
{
    float maxHeightFloat = levelNum*1.5;
    maxHeight = static_cast<int>(std::round(maxHeightFloat));
    std::cout << "max height rounded: " << maxHeight << "max height: " << maxHeightFloat<< std::endl;
    float obsFloat = levelNum*1.4+10;
    obs = static_cast<int>(std::round(obsFloat));

}

int Level::getLevelNum()
{
    return levelNum;
}


float Level::distance(const ngl::Vec3 &a, const ngl::Vec3 &b) {
    ngl::Vec3 diff = a - b;
    return std::sqrt(diff.dot(diff));
}

bool Level::isPositionValid(const ngl::Vec3 &newPos, const std::map<int, obsData> &mapData, float minDistance) {
    for (const auto &pair : mapData) {
        if (distance(newPos, pair.second.position) < minDistance) {
            return false;
        }
    }
    return true;
}
void Level::resetLevel()
{
    levelNum = 1;
    difficultySetter(levelNum);
}


std::map<int, obsData> Level::loadMap() {
    mapData.clear(); // Clear existing data if any

    for (int i = 1; i < obs; ++i) {
        ngl::Vec3 pos;
        std::string obj;
        do {
            pos = ngl::Random::getRandomVec3() * ngl::Vec3{3.0f, 3.0f, 3.0f};
        } while (!isPositionValid(pos, mapData, minDistance));

        int height = 1+ static_cast<int>(ngl::Random::randomPositiveNumber(maxHeight));

        float randomNum = ngl::Random::randomPositiveNumber(1.0f); // Generate random number between 0 and 1

        obj = (randomNum < 0.5f) ? "box" : "sphere";

        mapData[i] = obsData{height, pos, obj};
    }

    return mapData;
}

