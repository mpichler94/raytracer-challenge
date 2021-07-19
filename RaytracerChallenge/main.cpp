#include <iostream>
#include <iomanip>
#include <fstream>

#include <Shlwapi.h>

#include "tuple.h"
#include "canvas.h"
#include "color.h"
#include "math.h"
#include "ray.h"
#include "shape.h"
#include "intersection.h"
#include "camera.h"
#include "world.h"
#include "pattern.h"

struct projectile
{
	Tuple position; // point
	Tuple velocity;	// vector
};

struct environment
{
	Tuple gravity;	// vector
	Tuple wind;		// vector
};

// chapter 1
projectile tick(environment env, projectile proj)
{
	auto pos = proj.position + proj.velocity;
	auto vel = proj.velocity + env.gravity + env.wind;
	return projectile(pos, vel);
}

// chapter 2
void projectileLaucher()
{
	// projectile starts one unit above the origin.
	// velocity is normalized to 1 unit / tick.
	auto p = projectile(Tuple::point(0, 1, 0), normalize(Tuple::vector(1, 1.8f, 0)) * 11.25f);

	// gravity -0.1 unit / tick, and wind is -0.01 unit / tick.
	auto e = environment(Tuple::vector(0, -0.1f, 0), Tuple::vector(-0.01f, 0, 0));

	auto canvas = Canvas(900, 550);

	int count = 0;
	while (p.position.y >= 0.f)
	{
		std::cout << std::fixed << std::setprecision(2);
		std::cout << "Projectile at (" << std::setw(7) << p.position.x << " " << std::setw(7) << p.position.y << " " << std::setw(7) << p.position.z;
		std::cout << ") with velocity (" << std::setw(7) << p.velocity.x << " " << std::setw(7) << p.velocity.y << " " << std::setw(7) << p.velocity.z << ")" << std::endl;
		canvas.writePixel((int)p.position.x, canvas.height - (int)p.position.y, Color(1, 0, 0));

		p = tick(e, p);
		count++;

		if (count > 1000)
			break;
	}

	std::cout << "Projectile at (" << std::setw(7) << p.position.x << " " << std::setw(7) << p.position.y << " " << std::setw(7) << p.position.z;
	std::cout << ") with velocity (" << std::setw(7) << p.velocity.x << " " << std::setw(7) << p.velocity.y << " " << std::setw(7) << p.velocity.z << ")" << std::endl;
	std::cout << "Projectile hit ground after " << count << " ticks." << std::endl;
	canvas.writePixel((int)p.position.x, canvas.height - (int)p.position.y, Color(1, 0, 0));

	canvas.savePPM("canvas.ppm");
}

void analogClock()
{
	auto canvas = Canvas(50, 50);

	for (int i = 0; i < 12; i++)
	{
		auto p = Tuple::point(0, 0, 0);
		auto t = translation(0, 20, 0);
		auto r = rotationZ((float)i * pi / 6);
		auto t2 = translation(22, 22, 0);
		p = t2 * r * t * p;
		canvas.writePixel(floorf(p.x), floorf(p.y), Color(1, 1, 1));
	}
	canvas.savePPM("canvas.ppm");
}

// chapter 5
void silhouetteRayCaster()
{
	auto rayOrigin = Tuple::point(0, 0, -5);
	float wallZ = 10;
	float wallSize = 7;
	int canvasPixels = 200;
	float pixelSize = wallSize / canvasPixels;
	float half = wallSize / 2.f;

	auto canvas = Canvas(canvasPixels, canvasPixels);
	auto color = Color(1, 0, 0);
	auto shape = Sphere();
	//shape.transform = scaling(1, 0.5, 1);
	//shape.transform = scaling(0.5, 1, 1);
	//shape.transform = rotationZ(pi / 4) * scaling(0.5, 1, 1);
	//shape.transform = shearing(1, 0, 0, 0, 0, 0) * scaling(0.5, 1, 1);

	for (int y = 0; y < canvasPixels; y++)
	{
		float worldY = half - pixelSize * y;
		for (int x = 0; x < canvasPixels; x++)
		{
			float worldX = -half + pixelSize * x;
			auto pos = Tuple::point(worldX, worldY, wallZ);
			auto ray = Ray(rayOrigin, normalize(pos - rayOrigin));
			auto xs = shape.intersect(ray).hit();
			if (xs != nullptr)
			{
				canvas.writePixel(x, y, color);
			}
		}
	}
	canvas.savePPM("canvas.ppm");
}

// chapter 6
void rayCaster()
{
	auto rayOrigin = Tuple::point(0, 0, -5);
	float wallZ = 10;
	float wallSize = 7;
	int canvasPixels = 800;
	float pixelSize = wallSize / canvasPixels;
	float half = wallSize / 2.f;

	auto canvas = Canvas(canvasPixels, canvasPixels);

	auto shape = Sphere();
	shape.material = Material();
	shape.material.color = Color(1, 0.2f, 1);
	//shape.transform = scaling(1, 0.5, 1);
	//shape.transform = scaling(0.5, 1, 1);
	//shape.transform = rotationZ(pi / 4) * scaling(0.5, 1, 1);
	//shape.transform = shearing(1, 0, 0, 0, 0, 0) * scaling(0.5, 1, 1);

	auto lightPos = Tuple::point(-10, 10, -10);
	auto lightColor = Color(1, 1, 1);
	auto light = PointLight(lightPos, lightColor);

	for (int y = 0; y < canvasPixels; y++)
	{
		float worldY = half - pixelSize * y;
		for (int x = 0; x < canvasPixels; x++)
		{
			float worldX = -half + pixelSize * x;
			auto pos = Tuple::point(worldX, worldY, wallZ);
			auto ray = Ray(rayOrigin, normalize(pos - rayOrigin));
			auto xs = shape.intersect(ray);
			auto hit = xs.hit();
			if (hit != nullptr)
			{
				auto point = ray.pos(hit->t);
				auto normal = hit->primitive->normal(point);
				auto eye = -ray.direction;
				Color color = hit->primitive->material.lighting(*hit->primitive, light, point, eye, normal, false);
				canvas.writePixel(x, y, color);
			}
		}
	}
	canvas.savePPM("canvas.ppm");
}

// chapter 7
void simpleWorld()
{
	auto floor = Sphere();
	floor.transform = scaling(10, 0.01f, 10);
	floor.material = Material();
	floor.material.color = Color(1, 0.9f, 0.9f);
	floor.material.specular = 0;

	auto leftWall = Sphere();
	leftWall.transform = translation(0, 0, 5) * rotationY(-pi / 4) * rotationX(pi / 2) * scaling(10, 0.1f, 10);
	leftWall.material = floor.material;

	auto rightWall = Sphere();
	rightWall.transform = translation(0, 0, 5) * rotationY(pi / 4) * rotationX(pi / 2) * scaling(10, 0.1f, 10);
	rightWall.material = floor.material;

	auto middle = Sphere();
	middle.transform = translation(-0.5f, 1, 0.5f) * scaling(0.6f, 0.4f, 2.0f);
	middle.material = Material();
	middle.material.color = Color(0.1f, 1, 0.5f);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;

	auto right = Sphere();
	right.transform = translation(1.5f, 0.5f, -0.5f) * scaling(0.5f, 0.5f, 0.5f);
	right.material = Material();
	right.material.color = Color(0.5f, 1, 0.1f);
	right.material.diffuse = 0.7f;
	right.material.specular = 0.3f;

	auto left = Sphere();
	left.transform = translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33);
	left.material = Material();
	left.material.color = Color(1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;

	auto world = World();
	world.light = PointLight(Tuple::point(-10, 10, -10), Color(1, 1, 1));
	world.addObject(&floor);
	world.addObject(&leftWall);
	world.addObject(&rightWall);
	world.addObject(&middle);
	world.addObject(&left);
	world.addObject(&right);

	auto camera = Camera(800, 400, pi / 3);
	camera.setTransform(viewTransform(Tuple::point(0, 1.5f, -5), Tuple::point(0, 1, 0), Tuple::point(0, 1, 0)));

	auto canvas = camera.render(world);
	canvas.savePPM("canvas.ppm");
}

// chapter 9
void worldWithPlanes()
{
	auto floor = Plane();
	//floor.transform = scaling(10, 0.01, 10);
	floor.material = Material();
	floor.material.color = Color(1, 0.9f, 0.9f);
	floor.material.specular = 0;

	auto leftWall = Plane();
	leftWall.transform = translation(0, 0, 5) * rotationY(-pi / 4) * rotationX(pi / 2);
	leftWall.material = floor.material;

	auto rightWall = Plane();
	rightWall.transform = translation(0, 0, 5) * rotationY(pi / 4) * rotationX(pi / 2);
	rightWall.material = floor.material;

	auto middle = Sphere();
	middle.transform = translation(-0.5, 1, 0.5) * scaling(0.6, 0.4, 2.0);
	middle.material = Material();
	middle.material.color = Color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;

	auto right = Sphere();
	right.transform = translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5);
	right.material = Material();
	right.material.color = Color(0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;

	auto left = Sphere();
	left.transform = translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33);
	left.material = Material();
	left.material.color = Color(1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;

	auto world = World();
	world.light = PointLight(Tuple::point(-10, 10, -10), Color(1, 1, 1));
	world.addObject(&floor);
	world.addObject(&leftWall);
	world.addObject(&rightWall);
	world.addObject(&middle);
	world.addObject(&left);
	world.addObject(&right);

	auto camera = Camera(800, 400, pi / 3);
	camera.setTransform(viewTransform(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::point(0, 1, 0)));

	auto canvas = camera.render(world);
	canvas.savePPM("canvas.ppm");

	ShellExecute(NULL, NULL, L"canvas.ppm", NULL, NULL, SW_SHOW);
}

// chapter 10
void worldWithPatterns()
{
	auto floor = Plane();
	auto fPattern = CheckersPattern(Color(1, 1, 1), Color(0, 0, 0));
	fPattern.transform = translation(0, -0.1, 0) * rotationY(pi / 4) * scaling(2, 2, 2);
	floor.material = Material();
	floor.material.specular = 0;
	floor.material.pattern = &fPattern;

	auto leftWall = Plane();
	auto lwPattern = RingPattern(Color(1, 1, 1), Color(1, 0, 0));
	//lwPattern.transform = rotationX(pi / 2) * translation(0, 0, 5);
	leftWall.transform = translation(0, 0, 4.9) * rotationY(-pi / 4) * rotationX(pi / 2);
	leftWall.material = floor.material;
	leftWall.material.pattern = &lwPattern;

	auto rightWall = Plane();
	rightWall.transform = translation(0, 0, 4.9) * rotationY(pi / 4) * rotationX(pi / 2);
	rightWall.material = floor.material;
	rightWall.material.color = Color(0.7f);
	rightWall.material.pattern = nullptr;

	auto middle = Sphere();
	auto sPattern = StripePattern(Color(1, 0.5, 0), Color(1, 0.3, 0));
	sPattern.transform = rotationZ(pi / 2) * scaling(0.05, 0.05, 0.05);
	middle.transform = translation(-0.5, 1, 0.5) * scaling(0.6, 0.4, 2.0);
	middle.material = Material();
	middle.material.color = Color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;
	middle.material.pattern = &sPattern;

	auto right = Sphere();
	right.transform = translation(1.5, 0.5, -0.5) * scaling(0.5, 0.5, 0.5);
	right.material = Material();
	right.material.color = Color(0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;

	auto left = Sphere();
	left.transform = translation(-1.5, 0.33, -0.75) * scaling(0.33, 0.33, 0.33);
	left.material = Material();
	left.material.color = Color(1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;

	auto world = World();
	world.light = PointLight(Tuple::point(-10, 10, -10), Color(1, 1, 1));
	world.addObject(&floor);
	world.addObject(&leftWall);
	world.addObject(&rightWall);
	world.addObject(&middle);
	world.addObject(&left);
	world.addObject(&right);

	auto camera = Camera(800, 400, pi / 3);
	camera.setTransform(viewTransform(Tuple::point(0, 1.5, -5), Tuple::point(0, 1, 0), Tuple::point(0, 1, 0)));

	auto canvas = camera.render(world);
	canvas.savePPM("canvas.ppm");

	ShellExecute(NULL, NULL, L"canvas.ppm", NULL, NULL, SW_SHOW);
}

int main(char* ars[])
{
	//projectileLaucher();
	//analogClock();
	//silhouetteRayCaster();
	//rayCaster();
	//simpleWorld();
	//orldWithPlanes();
	worldWithPatterns();

}
