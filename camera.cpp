#include "camera.h"

#include <cmath>

PerspectiveCamera::PerspectiveCamera(Point origin,
	Vector target, Vector upguide, float fov, float aspectRatio)
	: origin(origin)
{
	forward = (target - origin).normalized();
	right = cross(forward, upguide).normalized();
	up = cross(right, forward);

	h = tan(fov);
	w = h * aspectRatio;
}

Ray PerspectiveCamera::makeRay(Vector2 point) const
{
	Vector direction =
		forward + point.u * w * right + point.v * h * up;

	return Ray(origin, direction.normalized());
}

void PerspectiveCamera::moveForward(float amount, Vector target, Vector upguide, float fov, float aspectRatio)
{
	origin = Vector(origin.x, origin.y, origin.z + amount);
	forward = (target - origin).normalized();
	right = cross(forward, upguide).normalized();
	up = cross(right, forward);

	h = tan(fov);
	w = h * aspectRatio;
}

void PerspectiveCamera::moveRight(float amount, Vector target, Vector upguide, float fov, float aspectRatio)
{
	origin = Vector(origin.x + amount, origin.y, origin.z);
	forward = (target - origin).normalized();
	right = cross(forward, upguide).normalized();
	up = cross(right, forward);

	h = tan(fov);
	w = h * aspectRatio;
}