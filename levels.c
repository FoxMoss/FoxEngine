#include "levels.h"


SDFLevel *initLevels() {
    SDFLevel *levels = malloc(sizeof(SDFLevel) * 1);

    SDFObject *objects = malloc(sizeof(SDFObject) * 3);
    objects[0] = (SDFObject) {SDF_PLANE, {2, 0, 10}, WHITE, {0, 0, 0}, (rayModifer){false}, false};
    //objects[1] = (SDFObject) {SDF_BOX, {8, 4, 10}, BLUE, {2, 2, 2}, (rayModifer){true, {0, 5, 0}, {0, 0, 0}, 1}, false};
    objects[2] = (SDFObject) {SDF_TORUS, {0, 5, 10}, RED, {2, 1, 2}, (rayModifer) { false }, false};
    objects[1] = (SDFObject) {SDF_TORUS, {0, 5, 10}, BLACK, {1, 1, 2}, (rayModifer) { true, (Vector3){0,0,0}, (Vector3){0,0,0}, 1}, true};

    levels[0].objects = objects;
    levels[0].size = 3;
    
    return levels;
}