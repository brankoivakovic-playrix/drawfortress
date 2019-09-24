#pragma once

#include "Common.h"
#include "Color.h"

struct ClipRect
{
	Vector2di leftTop;
	Vector2di rightBottom;
};

class IRender
{
public:
	// postavlja velicinu vidljivog dela za iscrtavanje, sve izvan tog podrucja ce bude iseceno
	virtual void ViewSize(Vector2di size) = 0;

	// vraca velicinu vidljivog dela za iscrtavanje
	virtual Vector2di GetViewSize() const = 0;

	// postavlja poziciju kamere
	virtual void CameraPos(Vector2di position) = 0;

	// vraca poziciju kamere
	virtual Vector2di GetCameraPos() const = 0;

	// iscrtava tekst
	virtual void DrawText(Vector2di pos, Color color, string text) = 0;

	// iscrtava jedan znak
	virtual void Draw(Vector2di pos, Color color, char viewChar) = 0;

	// brise sadrzaj medjuspremnika u dozvoljenom regionu za iscrtavanje
	virtual void Clear() = 0;

	// iscrtavanje sadrzaja iz medjuspremnika na ekran
	virtual void Flush() = 0;

	// postavlja dozvoljeni region za iscrtavanje, sve izvan njega ce bude iseceno
	virtual void SetClipRect(ClipRect clipRect) = 0;

	// vraca dozvoljeni region za iscrtavanje
	virtual ClipRect GetClipRect() const = 0;

	virtual ~IRender() = default;
};