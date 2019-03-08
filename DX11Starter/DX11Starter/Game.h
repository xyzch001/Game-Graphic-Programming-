#pragma once

#include "DXCore.h"
#include "GameEntity.h"
#include "Camera.h"
#include "Lights.h"
#include "BoundingSphere.h"
#include "AABB.h"
#include "plane.h"
#include "PhysicsEngine.h"
#include <iostream>

using namespace DirectX;

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
	Mesh* sphere;
	Mesh* torus;
	Mesh* helix;
	Mesh* cube;
	Mesh* cone;
	Mesh* cylinder;
	Mesh* geometry;

	//Five new gameentities
	GameEntity* entity1;
	GameEntity* entity2;
	GameEntity* entity3;
	GameEntity* entity4;
	GameEntity* entity5;
	GameEntity* entity6;
	
	


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
	Material* metal;
	
	//The DirectionalLight
	DirectionalLight light1;
	DirectionalLight light2;

	//The PointLight
	PointLight light3;

	// Texture SRV pointer
	ID3D11ShaderResourceView* srv;
	ID3D11ShaderResourceView* srv1;

	ID3D11SamplerState* sampleState;
	
	D3D11_SAMPLER_DESC sampleDesc = {};

	PhysicsEngine* phyEngine;
};

