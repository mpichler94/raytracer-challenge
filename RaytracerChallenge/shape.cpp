#include "shape.h"

#include <sstream>
#include <iomanip>

#include "intersection.h"
#include "math.h"
#include "ray.h"

Shape::Shape()
    : transform(Matrix<4, 4>::identity()), material()
{
}

Sphere::Sphere()
    : center(Tuple::point(0, 0, 0)), radius(1)
{
}

Sphere Sphere::glass()
{
    Sphere s;
    s.material.transparency = 1.f;
    s.material.refractiveIndex = 1.5f;
    return s;
}

Intersections Shape::intersect(const Ray& ray) const
{
    auto r = ray.transform(inverse(transform));
    return intersectIntenal(r);
}

Tuple Shape::normal(const Tuple& point) const
{
    auto invTransform = inverse(transform);
    auto localPoint = invTransform * point;
    auto localNormal = normalInternal(localPoint);
    auto worldNormal = transpose(invTransform) * localNormal;
    worldNormal.w = 0.f;

    return normalize(worldNormal);
}

std::wstring ToString(const Shape* p)
{
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "Plane" << std::endl;
    return ss.str();
}

std::wstring ToString(const Shape& p)
{
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "Plane" << std::endl;
    return ss.str();
}

template<typename Base, typename T>
inline bool instanceof(const T*)
{
    return std::is_base_of<Base, T>::value;
}

bool Sphere::operator==(const Shape& rhs) const
{
    //if (!instanceof<Sphere>(&rhs))
        //return false;
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

std::wstring ToString(const Sphere& s)
{
    std::wstringstream ss;
    ss << std::fixed << std::setprecision(2);
    ss << "Sphere at (" << s.center.x << ", " << s.center.y << ", " << s.center.z << ") with radius " << s.radius << std::endl;
    return ss.str();
}

Intersections Sphere::intersectIntenal(const Ray& r) const
{
    // vector from center to ray origin
    auto sphereToRay = r.origin - center;
    auto a = dot(r.direction, r.direction);
    auto b = 2 * dot(r.direction, sphereToRay);
    auto c = dot(sphereToRay, sphereToRay) - radius;

    auto discriminant = powf(b, 2) - 4 * a * c;
    if (discriminant < 0)
        return Intersections();

    auto t1 = (-b - sqrtf(discriminant)) / (2 * a);
    auto t2 = (-b + sqrtf(discriminant)) / (2 * a);
    Intersection i1(t1, this);
    Intersection i2(t2, this);
    return Intersections{ i1, i2 };
}

Tuple Sphere::normalInternal(const Tuple& point) const
{
    return point - center;
}

Plane::Plane()
{
}

bool Plane::operator==(const Shape& rhs) const
{
    return transform == rhs.transform && material == rhs.material;
}

std::wstring Plane::toString() const
{
    std::wstringstream ss;
    ss << "Plane" << std::endl;
    return ss.str();
}

Intersections Plane::intersectIntenal(const Ray& r) const
{
    if (fabsf(r.direction.y) < EPSILON)
        return Intersections();

    float t = -r.origin.y / r.direction.y;

    return Intersections{ Intersection(t, this) };
}

Tuple Plane::normalInternal(const Tuple& point) const
{
    return Tuple::vector(0, 1, 0);
}
