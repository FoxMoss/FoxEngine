#include "levels.h"


SDFLevel *initLevels() {
    SDFLevel *levels = malloc(sizeof(SDFLevel) * 3);

    SDFObject *objects1 = malloc(sizeof(SDFObject) * 3);
    //objects1[0] = (SDFObject) {SDF_PLANE, {2, 0, 10}, WHITE, {0, 0, 0}, (rayModifer){false}, false};
    //objects[1] = (SDFObject) {SDF_BOX, {8, 4, 10}, BLUE, {2, 2, 2}, (rayModifer){true, {0, 5, 0}, {0, 0, 0}, 1}, false};
    objects1[1] = (SDFObject) {SDF_TORUS, {0, 5, 10}, RED, {2, 1, 2}, (rayModifer) { false }, false};
    objects1[0] = (SDFObject) {SDF_TORUS, {0, 5, 10}, BLANK, {1, 1, 2}, (rayModifer) { true, (Vector3){0,0,0}, (Vector3){0,0,0}, 1}, true};


    SDFObject *objects2 = malloc(sizeof(SDFObject) * 4);

    //objects2[0] = (SDFObject) {SDF_PLANE, {2, -5, 10}, WHITE, {0, 0, 0}, (rayModifer){false}, false};
    //objects2[0] = (SDFObject) {SDF_MANDELBULB, {0, 5, 5}, RED, {0, 0, 0}, (rayModifer){false}, false};
    //objects[1] = (SDFObject) {SDF_BOX, {8, 4, 10}, BLUE, {2, 2, 2}, (rayModifer){true, {0, 5, 0}, {0, 0, 0}, 1}, false};
    objects2[1] = (SDFObject) {SDF_TORUS, {0, 0, 10}, RED, {2, 1, 2}, (rayModifer) { false }, false};
    objects2[0] = (SDFObject) {SDF_TORUS, {0, 0, 10}, BLANK, {1, 1, 2}, (rayModifer) { true, (Vector3){0,0,0}, (Vector3){0,0,0}, 1}, true};
    objects2[2] = (SDFObject) {SDF_BOX, {0, 5, 11}, RED, {1, 1, 1}, (rayModifer) { true, (Vector3){0,-4,-4}, (Vector3){0,0,0}, 1}, false};

    SDFObject *objects3 = malloc(sizeof(SDFObject) * 5);

    objects3[0] = (SDFObject) {SDF_PLANE, {2, 0, 10}, WHITE, {0, 0, 0}, (rayModifer){true, (Vector3){-4,9,0}, (Vector3){0,0,0}, 1}, false};
    objects3[2] = (SDFObject) {SDF_PLANE, {2, 10, 10}, WHITE, {0, 0, 0}, (rayModifer){true, (Vector3){4,-9,0}, (Vector3){0,0,0}, 1}, false};
    //objects2[0] = (SDFObject) {SDF_MANDELBULB, {0, 5, 5}, RED, {0, 0, 0}, (rayModifer){false}, false};
    //objects[1] = (SDFObject) {SDF_BOX, {8, 4, 10}, BLUE, {2, 2, 2}, (rayModifer){true, {0, 5, 0}, {0, 0, 0}, 1}, false};
    objects3[3] = (SDFObject) {SDF_TORUS, {0, 5, 10}, RED, {2, 1, 2}, (rayModifer) { false }, false};
    objects3[1] = (SDFObject) {SDF_TORUS, {0, 5, 10}, BLANK, {1, 1, 2}, (rayModifer) { true, (Vector3){0,0,0}, (Vector3){0,0,0}, 1}, true};
    //objects3[3] = (SDFObject) {SDF_BOX, {0, 5, 11}, RED, {1, 1, 1}, (rayModifer) { true, (Vector3){0,-4,-4}, (Vector3){0,0,0}, 1}, false};



    levels[0].objects = objects1;
    levels[0].size = 2;

    levels[1].objects = objects2;
    levels[1].size = 3;

    levels[2].objects = objects3;
    levels[2].size = 4;
    
    return levels;
}