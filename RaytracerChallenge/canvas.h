#pragma once
#include <vector>
#include <string>

class Color;

class Canvas
{
private:
	std::vector<Color> buffer;

public:
	const size_t width;
	const size_t height;

public:
	Canvas(const size_t width, const size_t height);


	void writePixel(size_t x, size_t y, const Color& c);
	const Color& at(size_t x, size_t y) const;


	std::string getPPM() const;
	void savePPM(const std::string& path) const;

private:
	void writePPM(std::ostream& stream) const;
};

