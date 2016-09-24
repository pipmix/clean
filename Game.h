#pragma once
#include "Headers.h"
#include "Timer.h"
#include "Data.h"
#include "CollisionManager.h"
#include "Camera.h"
#include "Input.h"
#include "UI.h"
#include "Map.h"
#include "Model.h"

extern ComPtr<ID3D11Device>				gDevice;
extern ComPtr<ID3D11DeviceContext>		gContext;
extern ComPtr<ID3D11DeviceContext>		gDContext;
extern HWND								ghWnd;
extern ComPtr<ID3D11Buffer>				gcbPerMesh;
extern ComPtr<ID3D11Buffer>				gcbPerFrame;
extern Camera gCam;
extern Input gInput;

class Dx;

class Game {
public:

			Game();
	void	Load();
	void	Update(double deltaTime);
	void	Draw();


	Player player;
	UI		ui;
	Map		map1;


	CollisionManager cm;




};