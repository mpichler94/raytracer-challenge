#include <sstream>
#include <algorithm>
#include <fstream>

#include "canvas.h"
#include "color.h"

Canvas::Canvas(const size_t width, const size_t height)
	: width(width), height(height), buffer(width * height)
{
}

void Canvas::writePixel(size_t x, size_t y, const Color& c)
{
	if (x >= width || y >= height)
		return;
	buffer.at(y * width + x) = c;
}

const Color& Canvas::at(size_t x, size_t y) const
{
	if (x >= width || y >= height)
		return Color();
	return buffer.at(y * width + x);
}

std::string Canvas::getPPM() const
{
	std::stringstream ss;
	writePPM(ss);

	return ss.str();
}

void Canvas::savePPM(const std::string& path) const
{
	std::ofstream file;
	file.open("canvas.ppm");
	writePPM(file);
	file.close();
}

void Canvas::writePPM(std::ostream& stream) const
{
	stream << "P3" << std::endl;
	stream << width << " " << height << std::endl;
	stream << 255 << std::endl;

	size_t column = 0;
	std::stringstream row;
	for (auto& c : buffer)
	{
		if (column++ >= width)
		{
			stream << row.str().substr(0, row.str().size() - 1) << std::endl;
			row.str(std::string());
			column = 1;
		}

		row << std::clamp((int)std::rintf(c.r * 255.f), 0, 255) << " ";

		if (row.str().size() > 66)
		{
			stream << row.str().substr(0, row.str().size() - 1) << std::endl;
			row.str(std::string());
		}

		row << std::clamp((int)std::rintf(c.g * 255.f), 0, 255) << " ";

		if (row.str().size() > 66)
		{
			stream << row.str().substr(0, row.str().size() - 1) << std::endl;
			row.str(std::string());
		}

		row << std::clamp((int)std::rintf(c.b * 255.f), 0, 255) << " ";

		if (row.str().size() > 66)
		{
			stream << row.str().substr(0, row.str().size() - 1) << std::endl;
			row.str(std::string());
		}
	}

	stream << row.str() << std::endl;
}


