#include "physics.h"

bool DetectCollisionAABB(glm::vec3 positionOne, glm::vec3 sizeOne, glm::vec3 positionTwo, glm::vec3 sizeTwo) {
    // collision x-axis?
    bool collisionX = positionOne.x + sizeOne.x >= positionTwo.x &&
        positionTwo.x + sizeTwo.x >= positionOne.x;
    // collision y-axis?
    bool collisionY = positionOne.y + sizeOne.y >= positionTwo.y &&
        positionTwo.y + sizeTwo.y >= positionOne.y;
    // collision only if on both axes
    return collisionX && collisionY;
}
