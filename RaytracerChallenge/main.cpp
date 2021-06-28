#include "tuple.h"
#include <iostream>
#include <iomanip>

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

int main(char* ars[])
{
	// projectile starts one unit above the origin.
	// velocity is normalized to 1 unit / tick.
	auto p = projectile(Tuple::point(0, 1, 0), normalize(Tuple::vector(1, 1, 0)) * 5.f);

	// gravity -0.1 unit / tick, and wind is -0.01 unit / tick.
	auto e = environment(Tuple::vector(0, -0.1, 0), Tuple::vector(-0.01, 0, 0));
	
	int count = 0;
	while (p.position.y >= 0.f)
	{
		std::cout << std::fixed << std::setprecision(2);
		std::cout << "Projectile at (" << std::setw(7) << p.position.x << " " << std::setw(7) << p.position.y << " " << std::setw(7) << p.position.z;
		std::cout << ") with velocity (" << std::setw(7) << p.velocity.x << " " << std::setw(7) << p.velocity.y << " " << std::setw(7) << p.velocity.z << ")" << std::endl;
		p = tick(e, p);
		count++;

		if (count > 1000)
			break;
	}

	std::cout << "Projectile at (" << std::setw(7) << p.position.x << " " << std::setw(7) << p.position.y << " " << std::setw(7) << p.position.z;
	std::cout << ") with velocity (" << std::setw(7) << p.velocity.x << " " << std::setw(7) << p.velocity.y << " " << std::setw(7) << p.velocity.z << ")" << std::endl;
	std::cout << "Projectile hit ground after " << count << " ticks." << std::endl;
}