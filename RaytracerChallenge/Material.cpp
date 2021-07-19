#include "material.h"

#include <sstream>

#include "math.h"
#include "tuple.h"
#include "light.h"
#include "pattern.h"
#include "shape.h"

Material::Material()
	: ambient(0.1f), diffuse(0.9f), specular(0.9f), shininess(200.f), reflective(0.f), color(1, 1, 1), pattern(nullptr)
{
}

Color Material::lighting(const Shape& object, const Light& light, const Tuple& pos, const Tuple& eye, const Tuple& normal, const bool inShadow) const
{
	Color color;
	if (pattern != nullptr)
		color = pattern->colorAtShape(object, pos);
	else
		color = this->color;
	// combine surface color with light color/intensity
	const Color effectiveColor = color * light.intensity;
	const Color ambientColor = effectiveColor * ambient;

	if (inShadow)
	{
		return ambientColor;
	}

	// directon TO the light source
	const Tuple l = normalize(light.position - pos);

	const float lightDotNormal = dot(l, normal);

	if (lightDotNormal < 0)	// light is on the other side
	{
		return ambientColor;
	}

	Color diffuseColor = effectiveColor * diffuse * lightDotNormal;
	// light reflection vector
	Tuple r = reflect(-l, normal);
	float rDotEye = dot(r, eye);

	Color specularColor = Color();
	if (rDotEye > 0)
	{
		float factor = powf(rDotEye, shininess);
		specularColor = light.intensity * specular * factor;
	}

	return ambientColor + diffuseColor + specularColor;
}

bool Material::operator==(const Material& rhs) const
{
	return color == rhs.color && areEqual(ambient, rhs.ambient) && areEqual(diffuse, rhs.diffuse) && areEqual(specular, rhs.specular) && areEqual(shininess, rhs.shininess);
}

std::wstring ToString(const Material& m)
{
	std::wstringstream ss;
	ss << "Material: Color" << ToString(m.color) << " ambient " << m.ambient << " diff " << m.diffuse << " spec " << m.specular << " shine " << m.shininess << std::endl;
	return ss.str();
}
