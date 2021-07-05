#include "primitive.h"

#include <sstream>
#include <iomanip>

#include "intersection.h"
#include "math.h"
#include "ray.h"

Primitive::Primitive()
    : transform(Matrix<4, 4>::identity()), material()
{
}

Sphere::Sphere()
    : center(Tuple::point(0, 0, 0)), radius(1)
{
}

Intersections Sphere::intersect(const Ray& ray) const
{
    auto r = ray.transform(inverse(transform));
    // vector from center to ray origin
    auto sphereToRay = r.origin - center;
    auto a = dot(r.direction, r.direction);
    auto b = 2 * dot(r.direction, sphereToRay);
    auto c = dot(sphereToRay, sphereToRay) - radius;

    auto discriminant = powf(b, 2) - 4 * a * c;
    if(discriminant < 0)
        return Intersections();

    auto t1 = (-b - sqrtf(discriminant)) / (2 * a);
    auto t2 = (-b + sqrtf(discriminant)) / (2 * a);
    Intersection i1(t1, *this);
    Intersection i2(t2, *this);
    return Intersections{i1, i2};
}

Tuple Sphere::normal(const Tuple& point) const
{
    auto n = normalize(transpose(inverse(transform)) * (inverse(transform) * (point - center)));
    n.w = 0.f;
    return n;
}

template<typename Base, typename T>
inline bool instanceof(const T*)
{
    return std::is_base_of<Base, T>::value;
}

bool Sphere::operator==(const Primitive& rhs) const
{
    if (!instanceof<Sphere>(&rhs))
        return false;
    const Sphere& s = dynamic_cast<const Sphere&>(rhs);
    return center == s.center && areEqual(radius, s.radius);
}

std::wstring Sphere::toString() const
{
    return ToString(*this);
}

//bool operator==(const Sphere& lhs, const Sphere& rhs)
//{
//    return lhs.center == rhs.center && areEqual(lhs.radius, rhs.radius);
//}

std::wstring ToString(const Primitive& p)
{
    const auto& s = static_cast<const Sphere&>(p);
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "Sphere at (" << s.center.x << ", " << s.center.y << ", " << s.center.z << ") with radius " << s.radius << std::endl;
    return ss.str();
}

std::wstring ToString(const Sphere& s)
{
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "Sphere at (" << s.center.x << ", " << s.center.y << ", " << s.center.z << ") with radius " << s.radius << std::endl;
    return ss.str();
}

Intersections Primitive::intersect(const Ray& r) const
{
    return Intersections();
}
