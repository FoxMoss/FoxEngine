#include "levels.h"


SDFLevel *initLevels() {
    SDFLevel *levels = malloc(sizeof(SDFLevel));
    SDFObject *objects = malloc(sizeof(SDFObject) * 3);

    objects[0] = (SDFObject) {SDF_PLANE, {2, 0, 10}, WHITE, {0, 0, 0}, (rayModifer){false}, false};
    objects[1] = (SDFObject) {SDF_BOX, {8, 4, 10}, BLUE, {2, 2, 2}, (rayModifer){true, {0, 5, 0}, {0, 0, 0}, 1}, false};
    objects[2] = (SDFObject) {SDF_TORUS, {-8, 4, 10}, RED, {9, 2, 3}, (rayModifer) { false }, false};

    levels[0].objects = objects;
    levels[0].size = 3;
    
    return levels;
}