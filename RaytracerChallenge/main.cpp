#include <iostream>
#include <iomanip>
#include <fstream>
#include "tuple.h"
#include "canvas.h"
#include "color.h"
#include "math.h"

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

projectile tick(environment env, projectile proj)
{
	auto pos = proj.position + proj.velocity;
	auto vel = proj.velocity + env.gravity + env.wind;
	return projectile(pos, vel);
}

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

int main(char* ars[])
{
	//projectileLaucher();
	analogClock();

}