#include "light.h"

#include <sstream>

Light::Light(const Tuple& position, const Color& intensity)
	: position(position), intensity(intensity)
{
}

bool Light::operator==(const Light& rhs) const
{
	return intensity == rhs.intensity && position == rhs.position;
}

PointLight::PointLight(const Tuple& position, const Color& intensity)
	: Light(position, intensity)
{
}

bool PointLight::operator==(const Light& rhs) const
{
	return Light::operator==(rhs);
}

std::wstring ToString(const PointLight& l)
{
	std::wstringstream ss;
	ss << "PointLight at " << ToString(l.position) << " with intensity " << ToString(l.intensity);
	return std::wstring();
}
