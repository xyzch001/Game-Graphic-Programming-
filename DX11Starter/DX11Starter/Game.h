#pragma once

#include "DXCore.h"
#include "GameEntity.h"
#include "Camera.h"
#include "Lights.h"

class Game 
	: public DXCore
{

public:
	Game(HINSTANCE hInstance);
	~Game();

	// Overridden setup and game loop methods, which
	// will be called automatically
	void Init();
	void OnResize();
	void Update(float deltaTime, float totalTime);
	void Draw(float deltaTime, float totalTime);
	void Shader(GameEntity* entity);

	// Overridden mouse input helper methods
	void OnMouseDown (WPARAM buttonState, int x, int y);
	void OnMouseUp	 (WPARAM buttonState, int x, int y);
	void OnMouseMove (WPARAM buttonState, int x, int y);
	void OnMouseWheel(float wheelDelta,   int x, int y);
private:
	//three new Mesh class
	Mesh* geometry1;
	Mesh* geometry2;
	Mesh* geometry3;
	Mesh* testCube;

	//Five new gameentities
	GameEntity* entity1;
	GameEntity* entity2;
	GameEntity* entity3;
	GameEntity* entity4;
	GameEntity* entity5;
	GameEntity* testEntity;


	// Initialization helper methods - feel free to customize, combine, etc.
	void LoadShaders(); 
	void CreateMatrices();
	void CreateBasicGeometry();

	// Buffers to hold actual geometry data
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;

	// Wrappers for DirectX shaders to provide simplified functionality
	SimpleVertexShader* vertexShader;
	SimplePixelShader* pixelShader;

	// The matrices to go from model space to screen space
	DirectX::XMFLOAT4X4 worldMatrix;
	DirectX::XMFLOAT4X4 viewMatrix;
	DirectX::XMFLOAT4X4 projectionMatrix;

	// Keeps track of the old mouse position.  Useful for 
	// determining how far the mouse moved in a single frame.
	POINT prevMousePos;

	//The pointer of Camera
	Camera* cameraObj;

	//The pointer of Material
	Material* material;
	
	//The DirectionalLight
	DirectionalLight light1;
	DirectionalLight light2;

};

