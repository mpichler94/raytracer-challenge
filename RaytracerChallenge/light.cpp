#include "light.h"

Light::Light(const Tuple& position, const Color& intensity)
	: position(position), intensity(intensity)
{
}

PointLight::PointLight(const Tuple& position, const Color& intensity)
	: Light(position, intensity)
{
}
