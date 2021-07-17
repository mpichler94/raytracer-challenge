#include "world.h"

#include "math.h"
#include "intersection.h"
#include "ray.h"

World::World()
    : objects(), light()
{
}


World World::Default()
{
    World w = World();
    w.light = PointLight(Tuple::point(-10, 10, -10), Color(1, 1, 1));
    auto s1 = new Sphere();
    s1->material.color = Color(0.8, 1.0, 0.6);
    s1->material.diffuse = 0.7;
    s1->material.specular = 0.2;
    auto s2 = new Sphere();
    s2->transform = scaling(0.5, 0.5, 0.5);
    w.addObject(s1);
    w.addObject(s2);
    return w;
}

void World::dispose()
{
    for (auto o : objects)
    {
        delete o;
        o = nullptr;
    }
    objects.clear();
}

size_t World::getObjectCount() const
{
    return objects.size();
}

bool World::contains(const Shape& p) const
{
    for (auto it = objects.begin(); it != objects.end(); it++)
    {
        if (**it == p)
            return true;
    }

    return false;
}

void World::addObject(Shape* p)
{
    objects.push_back(p);
}

Shape* World::getObject(size_t index)
{
    return objects[index];
}

Intersections World::intersect(const Ray& ray) const
{
    auto ret = Intersections();
    for (auto o : objects)
    {
        auto xs = o->intersect(ray);
        ret += xs;
    }
    return ret;
}

Color World::colorAt(const Ray& ray) const
{
    auto xs = intersect(ray);
    auto hit = xs.hit();
    if (hit == nullptr)
        return Color(0, 0, 0);
    auto comps = hit->prepare(ray);
    return comps.shade(*this);
}

bool World::isShadowed(const Tuple& point) const
{
    auto direction = light.position - point;
    auto distance = length(direction);
    auto ray = Ray(point, normalize(direction));

    auto xs = intersect(ray);
    auto hit = xs.hit();

    return hit != nullptr && hit->t < distance;
}
