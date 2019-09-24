#include <windows.h>

#include "Render.h"


#include "ThirdParty/ColorPalete.h"



std::unique_ptr<Render> Render::s_render;
std::mutex              Render::s_renderLock;


unique_ptr<CHAR_INFO[]> _frameBuffer;



  COLORREF palette[16] = 
  {
    /*Black*/0x00000000, /*Blue*/0x00FF0000, /*Green*/ 0x0000FF00, /*Aqua*/0x00FFFF00,
    /*Red*/  0x000000FF, /*Pink*/0x00FF00FF, /*Yellow*/0x0000FFFF,         0x00c0c0c0, 0x00808080,
    /*Blue Intensity*/0x00ff0000, /*Green Intensity*/0x00'22'22'22, /*Aqua Intensity*/0x00'ff'ff'00, /*Red Intensity*/0x00'33'33'33, 0x00ff00ff, 0x0000ffff, 0x00ffffff
  };



Render::Render(PermissionToken &&)
{
	_consoleOutputHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	_consoleInputHandle  = GetStdHandle(STD_INPUT_HANDLE );
	
	SetConsolePalette(palette, 8, 14, L"Lucida Console");
}

Render& Render::Instance()
{
	if(!s_render)
	{
		s_renderLock.lock();
		
		if(!s_render)
		{
			s_render = make_unique<Render>(PermissionToken(0));
		}

		s_renderLock.unlock();
	}
	return  *(s_render.get());
}

void Render::ViewSize(Vector2di size)
{
	_viewSize = size;
	
	_frameBuffer = make_unique<CHAR_INFO[]>(size.x * size.y);

	
	// velicina prozora konzole mora biti manja od screen buffer-a
	SMALL_RECT sRect {0, 0, static_cast<SHORT>(10), static_cast<SHORT>(4) };

	// velicina prozora konzole i screen buffer-a kozole su ovisni jedan o drugom
	// pa je racunica za odredjivanje koja funkcija treba pre da se pozove komplikovanija od duplog pisanja koda
	if (!SetConsoleWindowInfo(_consoleOutputHandle, TRUE, &sRect))
	{
		auto e = GetLastError();
		if(!SetConsoleScreenBufferSize(_consoleOutputHandle, { static_cast<SHORT>(_viewSize.x), static_cast<SHORT>(_viewSize.y) }))
		{
			auto e = GetLastError();
			if(!SetConsoleWindowInfo(_consoleOutputHandle, TRUE, &sRect))
			{
				auto e = GetLastError();
				exit(0);
			}
		}
	}
	else if(SetConsoleScreenBufferSize(_consoleOutputHandle, { static_cast<SHORT>(_viewSize.x), static_cast<SHORT>(_viewSize.y) }))
	{
		sRect =  {0, 0, static_cast<SHORT>(size.x - 1), static_cast<SHORT>(size.y - 1) };
			if(!SetConsoleWindowInfo(_consoleOutputHandle, TRUE, &sRect))
			{
				auto e = GetLastError();
				exit(0);
			}
	}


	// sakrivanje kursora u konzoli
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(_consoleOutputHandle, &cursorInfo);
    cursorInfo.bVisible = 0;
    SetConsoleCursorInfo(_consoleOutputHandle, &cursorInfo);

	// onemogucavanje selektovanje texta u konzoli
	DWORD prev_mode;
    GetConsoleMode(_consoleInputHandle, &prev_mode);
	SetConsoleMode(_consoleInputHandle, ENABLE_EXTENDED_FLAGS | (prev_mode & ~ENABLE_QUICK_EDIT_MODE));
	
}

Vector2di Render::GetViewSize() const
{
	return _viewSize;
}


void Render::CameraPos(Vector2di position)
{
	_cameraPosition = position;
}

Vector2di Render::GetCameraPos() const
{
	return _cameraPosition;
}

void Render::DrawText(Vector2di pos, Color color, string text)
{
	int_t size = text.length();

	const auto originalPos = pos;

	int_t left = 0;
	
	if(ClipCoordinates(pos, left, size))
	{
		//if(static_cast<size_t>(size) < text.length())
		//{
		//	if(left > 0)
		//	{
		//		text = text.substr(left, size);
		//	}
		//	else if(static_cast<size_t>(size) < text.size())
		//	{
		//		text.resize(size);
		//	}
		//	//text = text.substr(pos.x - originalPos.x, size);
		//}

		//if(color != _lastColor)
		//{
		//	text = ForegroundColor(color) + text;
		//	
		//	_lastColor = color;
		//}

		auto* buffer = &_frameBuffer[pos.x + pos.y * _viewSize.x];
		
		for(int_t i = 0; i < size; ++i)
		{
			buffer[i].Char.AsciiChar = text[left + i];
			buffer[i].Attributes     = static_cast<WORD>(color);
		}
		//cout << text;
	}
}

void Render::Draw(Vector2di pos, Color color, char viewChar)
{
	int_t size = 1;
	int_t left = 0;
	if(ClipCoordinates(pos, left, size))
	{
		string out;
		if(left > 0)
			return;
		
		//if(color != _lastColor)
		//{
		//	out += ForegroundColor(color);
		//	
		//	_lastColor = color;
		//}

		//out += viewChar;
		
		auto& buffer = _frameBuffer[pos.x + pos.y * _viewSize.x];
		
		buffer.Char.AsciiChar = viewChar;
		buffer.Attributes     = static_cast<WORD>(color);

		//cout << viewChar;
	}
}

void Render::Clear()
{
	//cout << "\x1B[2J\x1B[H";

	// brisanje medjuspremnika iscrtavanjem sahovske table
	
	bool startBg = !(_cameraPosition.x % 2);
	
	startBg = _cameraPosition.y % 2 ? startBg : !startBg;
	
	for(auto x = _viewSize.x - _clipRightBottom.x - 1; x >= _clipLeftTop.x; --x)
	{
		bool currentBg = startBg = !startBg;
		
		for(auto y = _viewSize.y - _clipRightBottom.y - 1; y >= _clipLeftTop.y; --y)
		{
			auto& buffer = _frameBuffer[x + y * _viewSize.x];
			buffer.Char.AsciiChar = ' ';

			// BACKGROUND_RED i BACKGROUND_GREEN nisu realne boje, obadve su prepisane nijansama sive u paleti boja za kozolu
			buffer.Attributes = (currentBg ? BACKGROUND_RED : BACKGROUND_GREEN ) | BACKGROUND_INTENSITY;
			currentBg = !currentBg;
		}
	}
}

void Render::Flush()
{
	SMALL_RECT consoleWriteArea = {0, 0, static_cast<SHORT>(_viewSize.x), static_cast<SHORT>(_viewSize.y)};
	WriteConsoleOutputA(_consoleOutputHandle, _frameBuffer.get(), {static_cast<SHORT>(_viewSize.x), static_cast<SHORT>(_viewSize.y)}, {0, 0}, &consoleWriteArea);
}

void Render::SetClipRect(ClipRect clipRect)
{
	_clipLeftTop     = clipRect.leftTop;
	_clipRightBottom = clipRect.rightBottom;
}

ClipRect Render::GetClipRect() const
{
	return {_clipLeftTop, _clipRightBottom};
}

bool Render::ClipCoordinates(Vector2di& pos, int_t& left, int_t& size) const
{
	pos -= _cameraPosition;

	if(pos.x >= _viewSize.x - _clipRightBottom.x || pos.y >= _viewSize.y - _clipRightBottom.y || pos.x + size < _clipLeftTop.x || pos.y < _clipLeftTop.y)
	{
		return false;
	}
	
	if(pos.x < _clipLeftTop.x)
	{
		left  = _clipLeftTop.x - pos.x;
		
		size  = size - left;
		
		pos.x = _clipLeftTop.x;
	}
	
	const auto offsetX = pos.x + size - _viewSize.x + _clipRightBottom.x + 1;
	
	if(offsetX > 0)
	{
		size -= offsetX;
	}

	return true;
}

string Render::ForegroundColor(Color color)
{
	stringstream s;

	//s << "\033[38;2;";
	//s << static_cast<unsigned short>(color.r);
	//s << ';';
	//s << static_cast<unsigned short>(color.g);
	//s << ';';
	//s << static_cast<unsigned short>(color.b);
	//s << "m";
	return s.str();
}

string Render::BackgroundColor(Color color)
{
	stringstream s;

	//s << "\033[48;2;";
	//s << static_cast<unsigned short>(color.r);
	//s << ';';
	//s << static_cast<unsigned short>(color.g);
	//s << ';';
	//s << static_cast<unsigned short>(color.b);
	//s << "m";

	return s.str();
}
