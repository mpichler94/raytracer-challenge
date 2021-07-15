#include "camera.h"

Camera::Camera(unsigned int width, unsigned int height, float fov)
	: width(width), height(height), fov(fov), transform(Matrix<4, 4>::identity())
{
	float halfView = tanf(fov / 2.f);
	float aspect = (float) width / height;
	if (aspect >= 1.f)
	{
		halfWidth = halfView;
		halfHeight = halfView / aspect;
	}
	else
	{
		halfWidth = halfView * aspect;
		halfHeight = halfView;
	}

	pixelSize = halfWidth * 2.f / width;
}

unsigned int Camera::getWidth() const
{
	return width;
}

unsigned int Camera::getHeight() const
{
	return height;
}

float Camera::getFov() const
{
	return fov;
}

const Matrix<4, 4>& Camera::getTransform() const
{
	return transform;
}

void Camera::setTransform(const Matrix<4, 4>& transform)
{
	this->transform = transform;
}

float Camera::getPixelSize() const
{
	return pixelSize;
}

Ray Camera::getRay(unsigned int x, unsigned int y) const
{
	// Offset from the edge of the canvas to the pixel's center
	float xOffset = (x + 0.5) * pixelSize;
	float yOffset = (y + 0.5) * pixelSize;
	// untranssformed coordinates of the pixel in world space.
	float worldX = halfWidth - xOffset;
	float worldY = halfHeight - yOffset;

	auto invTransform = inverse(transform);
	Tuple pixel = invTransform * Tuple::point(worldX, worldY, -1);
	Tuple origin = invTransform * Tuple::point(0, 0, 0);
	Tuple direction = normalize(pixel - origin);
	return Ray(origin, direction);
}

Canvas Camera::render(const World& world) const
{
	Canvas c = Canvas(width, height);

	for(unsigned int y = 0; y < height; y++)
		for (unsigned int x = 0; x < width; x++)
		{
			auto ray = getRay(x, y);
			auto color = world.colorAt(ray);
			c.writePixel(x, y, color);
		}
	return c;
}
