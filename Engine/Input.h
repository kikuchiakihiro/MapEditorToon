#pragma once



#include <dInput.h>
#include <DirectXMath.h>
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "dInput8.lib")

#define SAFE_RELEASE(p) if(p != nullptr){ p->Release(); p = nullptr;}

namespace Input
{
	void Initialize(HWND hWnd);
	void Update();
	bool IsKey(int keyCode);
	bool IsKeyDown(int keyCode);
	bool IsKeyUp(int keyCode);
	void Release();
	
	DirectX::XMVECTOR GetMousePosition();
	void SetMousePosition(int x, int y);
};