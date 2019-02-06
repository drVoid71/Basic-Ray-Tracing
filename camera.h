#ifndef CAMERA_H
#define CAMERA_H

#include "vectormath.h"
#include "ray.h"

class Camera
{
public:
	virtual ~Camera() { }
	virtual void moveForward(float amount, Vector target, Vector upguide, float fov, float aspectRatio) = 0;
	virtual void moveRight(float amount, Vector target, Vector upguide, float fov, float aspectRatio) = 0;
	virtual Ray makeRay(Vector2 point) const = 0;
};

class PerspectiveCamera : public Camera
{
protected:
	Point origin;
	Vector forward;
	Vector up;
	Vector right;

	float h, w;

public:
	PerspectiveCamera(Point origin, Vector target,
		Vector upguide, float fov, float aspectRatio);
	virtual void moveForward(float amount, Vector target, Vector upguide, float fov, float aspectRatio);
	virtual void moveRight(float amount, Vector target, Vector upguide, float fov, float aspectRatio);
	virtual Ray makeRay(Vector2 point) const;
};

#endif // CAMERA_H
