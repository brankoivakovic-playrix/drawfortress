#pragma once

//struct Color
//{
//	Color() = default;
//
//	Color(const Color&) = default;
//
//	Color(Color&&) = default;
//	
//	Color(unsigned char r, unsigned char g, unsigned char b) : r(r), g(g), b(b){}
//
//	~Color() = default;
//
//	
//	
//	Color& operator = (Color&& color) = default;
//
//	Color& operator = (const Color& color) = default;
//	
//	bool operator == (const Color& color) const { return (color.r == r && color.g == g && color.b == b); }
//	bool operator != (const Color& color) const { return (color.r != r || color.g != g || color.b != b); }
//	
//
//	unsigned char r = 0xFF, g = 0xFF, b = 0xFF;
//};


enum class Color : short
{
	Black = 0,
	
	Blue  = 0x0001,
	Green = 0x0002,
	Red   = 0x0004,
	
	Aqua   = Green | Blue,
	Pink   = Red   | Blue,
	Yellow = Green | Blue,

	White = Blue | Green | Red,
};