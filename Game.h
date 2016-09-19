#pragma once
#include "Headers.h"
#include "Timer.h"
#include "Data.h"
#include "Sprite.h"


extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;
extern ComPtr<ID3D11DeviceContext>		gDContext;
extern HWND								hWnd;
extern ComPtr<ID3D11Buffer>				gcbPerMesh;


class Game {
public:

			Game();
	void	Load();
	void	Update(double deltaTime);
	void	Draw();

	Sprite spr01;


};