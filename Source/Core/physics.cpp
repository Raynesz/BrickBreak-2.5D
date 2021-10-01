#include "Viewer.h"

Direction Physics::VectorDirection(glm::vec2 target)
{
    glm::vec2 compass[] = {
        glm::vec2(0.0f, 1.0f),	// up
        glm::vec2(1.0f, 0.0f),	// right
        glm::vec2(0.0f, -1.0f),	// down
        glm::vec2(-1.0f, 0.0f)	// left
    };
    float max = 0.0f;
    unsigned int best_match = -1;
    for (unsigned int i = 0; i < 4; i++)
    {
        float dot_product = glm::dot(glm::normalize(target), compass[i]);
        if (dot_product > max)
        {
            max = dot_product;
            best_match = i;
        }
    }
    return (Direction)best_match;
}

Physics::Collision Physics::CheckBallCollision(glm::vec3 ballPos, float ballRadius, glm::vec3 objectPos, glm::vec3 objectSize)
{
    // get center point circle first 
    glm::vec2 center(ballPos.x, ballPos.y);
    // calculate AABB info (center, half-extents)
    glm::vec2 aabb_half_extents(objectSize.x, objectSize.y);
    glm::vec2 aabb_center(objectPos.x, objectPos.y);
    // get difference vector between both centers
    glm::vec2 difference = center - aabb_center;
    glm::vec2 clamped = glm::clamp(difference, -aabb_half_extents, aabb_half_extents);
    // add clamped value to AABB_center and we get the value of box closest to circle
    glm::vec2 closest = aabb_center + clamped;
    // retrieve vector between center circle and closest point AABB and check if length <= radius
    difference = closest - center;
    if (glm::length(difference) <= ballRadius) return std::make_tuple(true, VectorDirection(difference), difference);
    else return std::make_tuple(false, UP, glm::vec2(0.0f, 0.0f));
}
