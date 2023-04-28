#include "foxsdf.h"

float boxcheapSDF(Vector3 point, Vector3 center, Vector3 scale)
{
    return vmax(subVec3(absVec3(subVec3(point, center)), scale));
}
float sphereSDF(Vector3 point, Vector3 sphere, float radius)
{
    //float c= 15;
    //point.x = fmod(point.x + 0.5*c, 5) - 0.5*c;
    //point.y = fmod(point.y + 0.5*c, 5) - 0.5*c;
    float distX = powf(sphere.x - point.x, 2);
    float distY = powf(sphere.y - point.y, 2);
    float distZ = powf(sphere.z - point.z, 2);
    return sqrt(distX + distY + distZ) - radius;
}
float planeSDF(Vector3 point, float y)
{
    return fabs(point.y - y)-0.5;
}

float wallinfSDF(Vector3 point, float x)
{
    return fabs(point.x - x)-0.5;
}
float torusSDF(Vector3 point, Vector3 position, Vector2 size)
{
    point = subVec3(point, position);
    Vector2 q = (Vector2){length2d((Vector2){point.x, point.y}) - size.x, point.z};
    return length2d(q) - size.y;
}
float mandelbulbSDF(Vector3 point, Vector3 position) {
    point = subVec3(point, position);
    point = mulVec3(point, 0.9);
	Vector3 z = point;
	float dr = 1.0;
	float r = 0.0;
    const int iter = 42;
    const int top = 47;
    const int power = 8.0;
	for (int i = 0; i < iter ; i++) {
		r = length(z);
		if (r>top) break;
		
		// convert to polar coordinates
		float theta = acos(z.z/r);
		float phi = atan(z.y+z.x);
		dr =  pow( r, power-1.0)*power*dr + 1.0;
		
		// scale and rotate the point
		float zr = pow( r,power);
		theta = theta*power;
		phi = phi*power;
		
		// convert back to cartesian coordinates
		z = mulVec3((Vector3){sin(theta)*cos(phi), sin(phi)*sin(theta), cos(theta)}, zr);
		z =addVec3(point, z);
	}
	return 0.5*log(r)*r/dr;
}
