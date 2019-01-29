#pragma once

#include "DXCore.h"
#include "SimpleShader.h"
#include <DirectXMath.h>
#include "Vertex.h"
#include <d3d11.h>
#include "Mesh.h"

class GameEntity
{
public:
	GameEntity(Mesh* object);
	~GameEntity();

	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();

	//Movement Methods
	void SetWorldMatrix();
	DirectX::XMFLOAT4X4 GetWorldMatrix();
	void SetTranslation(float x, float y, float z);
	void SetRotation(float x, float y, float z);
	void SetScale(float x, float y, float z);
	void Move(float x, float y, float z);
	void MoveForward(float x, float y, float z);
	//Movement Methods


private:
	DirectX::XMFLOAT4X4 translation;
	DirectX::XMFLOAT4X4 rotation;
	DirectX::XMFLOAT4X4 scale;
	DirectX::XMFLOAT4X4 worldMatrix;
	Mesh* gameObj;


};

