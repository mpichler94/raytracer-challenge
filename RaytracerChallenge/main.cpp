#include <iostream>
#include <iomanip>
#include <fstream>
#include "tuple.h"
#include "canvas.h"
#include "color.h"
#include "math.h"
#include "ray.h"
#include "primitive.h"
#include "intersection.h"
#include "camera.h"

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
	auto p = projectile(Tuple::point(0, 1, 0), normalize(Tuple::vector(1, 1.8, 0)) * 11.25f);

	// gravity -0.1 unit / tick, and wind is -0.01 unit / tick.
	auto e = environment(Tuple::vector(0, -0.1, 0), Tuple::vector(-0.01, 0, 0));

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
		canvas.writePixel(p.x, p.y, Color(1, 1, 1));
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
	shape.material.color = Color(1, 0.2, 1);
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
				Color color = hit->primitive->material.lighting(light, point, eye, normal);
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
	floor.transform = scaling(10, 0.01, 10);
	floor.material = Material();
	floor.material.color = Color(1, 0.9, 0.9);
	floor.material.specular = 0;

	auto leftWall = Sphere();
	leftWall.transform = translation(0, 0, 5) * rotationY(-pi / 4) * rotationX(pi / 2) * scaling(10, 0.1, 10);
	leftWall.material = floor.material;

	auto rightWall = Sphere();
	rightWall.transform = translation(0, 0, 5) * rotationY(pi / 4) * rotationX(pi / 2) * scaling(10, 0.1, 10);
	rightWall.material = floor.material;

	auto middle = Sphere();
	middle.transform = translation(-0.5, 1, 0.5);
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
}


int main(char* ars[])
{
	//projectileLaucher();
	//analogClock();
	//silhouetteRayCaster();
	//rayCaster();
	simpleWorld();

}
