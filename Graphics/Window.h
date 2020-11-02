#pragma once
#include <string>

class Window
{
public:
	Window(int width, int height, std::string title);

	virtual int getWidth() = 0;
	virtual int getHeight() = 0;
	virtual std::string getTitle() = 0;

private:
	int _width;
	int _height;
	std::string _title;
};

