#ifndef LEVELS_H
#define LEVELS_H
#include "foxsdf.h"

struct SDFLevel{
    SDFObject *objects;
    int size;    
}; 
typedef struct SDFLevel SDFLevel;

SDFLevel* initLevels();
#endif