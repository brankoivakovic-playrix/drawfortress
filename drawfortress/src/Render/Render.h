#pragma once
// WinUser.h ima definisan makro DrawText koji se sudara sa imenom metode u render klasi
#undef DrawText

#include "Common.h"
#include "IRender.h"



// SINGLETON Class
class Render final : public IRender
{
	// privatna struktura koja onemogucava pozivanje konstruktora izvan same render klase
	// kostruktor je javan zbog std::make_unique funkcije koju nije moguce proglasiti za friend funkciju, jer ona sama ne poziva konstruktor
	struct PermissionToken{ explicit PermissionToken(int){} };
	
public:
	explicit Render(PermissionToken&&);

	static Render& Instance();

	// postavlja velicinu vidljivog dela za iscrtavanje, sve izvan tog podrucja ce bude iseceno
	// velicina prozora od konzole ce bude isto postavljena prema toj velicini ako je moguce
	void ViewSize(Vector2di size) override;

	// vraca velicinu vidljivog dela za iscrtavanje
	Vector2di GetViewSize() const override;

	// postavlja poziciju kamere
	void CameraPos(Vector2di position) override;

	// vraca poziciju kamere
	Vector2di GetCameraPos() const override;

	// iscrtava tekst
	void DrawText(Vector2di pos, Color color, string text) override;

	// iscrtava jedan znak
	void Draw(Vector2di pos, Color color, char viewChar) override;

	// brise sadrzaj medjuspremnika u dozvoljenom regionu za iscrtavanje
	void Clear() override;

	// iscrtavanje sadrzaja iz medjuspremnika na ekran konzole
	void Flush() override;

	// postavlja dozvoljeni region za iscrtavanje, sve izvan njega ce bude iseceno
	void SetClipRect(ClipRect clipRect) override;

	// vraca dozvoljeni region za iscrtavanje
	ClipRect GetClipRect() const override;

private:
	bool ClipCoordinates(Vector2di& pos, int_t& left, int_t& size) const;

	static string ForegroundColor(Color color);
	
	static string BackgroundColor(Color color);
	
	Vector2di  _viewSize;
	
	Vector2di  _cameraPosition;

	Vector2di  _clipLeftTop;

	Vector2di  _clipRightBottom;
	
	void*      _consoleOutputHandle = nullptr; // HANDLE
	void*      _consoleInputHandle  = nullptr;
	
	static std::unique_ptr<Render> s_render;

	static std::mutex              s_renderLock;
	
};
