#include "light.h"

light* createLight(int type, glm::vec3 pos, glm::vec3 dir, glm::vec4 color)
{
    light* l = new light;
    l->type = type;
    l->pos = pos;
    l->dir = dir;
    l->color = color;
    return l;
}
