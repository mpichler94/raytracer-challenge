#pragma once

#include "math.h"
#include "ray.h"
#include "canvas.h"

class World;

class Camera
{
private:
	unsigned int width;
	unsigned int height;
	float fov;
	Matrix<4, 4> transform;
	float pixelSize;
	float halfWidth;
	float halfHeight;
	unsigned int maxBounces;

public:
	Camera(unsigned int width, unsigned int height, float fov);

	unsigned int getWidth() const;
	unsigned int getHeight() const;
	float getFov() const;
	const Matrix<4, 4>& getTransform() const;
	void setTransform(const Matrix<4, 4>& transform);
	float getPixelSize() const;
	Ray getRay(unsigned int x, unsigned int y) const;
	Canvas render(const World& world) const;
	void setMaxBounces(unsigned int maxBounces);
};

