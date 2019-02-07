#pragma once

#include "Mesh.h"
#include "Material.h"

class GameEntity
{
public:
	GameEntity(Mesh* object);
	~GameEntity();

	//Get the Mesh members
	ID3D11Buffer* GetVertexBuffer();
	ID3D11Buffer* GetIndexBuffer();
	int GetIndexCount();

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
	//the translation, rotation and scale of this entity
	DirectX::XMFLOAT4X4 translation;
	DirectX::XMFLOAT4X4 rotation;
	DirectX::XMFLOAT4X4 scale;
	DirectX::XMFLOAT4X4 worldMatrix;

	//Mesh object to store the vertex buffer and index buffer
	Mesh* gameObj;

	Material* material;

};

