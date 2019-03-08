#pragma once

#include "Mesh.h"
#include "Material.h"


class GameEntity
{
public:
	GameEntity(Mesh* meshObject, Material* materialObj, bool isControled);
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

	inline float GetDirection() { return direction; }
	inline float ChangeDirection() { 
		direction = -direction;
		return direction; }
	inline DirectX::XMMATRIX getWorldMatrix() {
		DirectX::XMMATRIX collider = DirectX::XMLoadFloat4x4(&worldMatrix);
		collider = DirectX::XMMatrixTranspose(collider);
		return collider;
	}
	//Material pass the view, projection and cameraPosition to the Shader
	void prepareMaterial(DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix, DirectX::XMFLOAT3 cameraPosition);

	inline Mesh* GetMesh() {
		return gameObj;
	}

	DirectX::BoundingSphere collider;
	inline DirectX::BoundingSphere* GetCollider() { return &collider; }
	inline bool GetIsControl() { return m_isControled; }

	void Movement();

	float x_velocity = 0;
	float y_velocity = 0;
	float z_velocity = 0;

private:
	//the translation, rotation and scale of this entity
	DirectX::XMFLOAT4X4 translation;
	DirectX::XMFLOAT4X4 rotation;
	DirectX::XMFLOAT4X4 scale;
	DirectX::XMFLOAT4X4 worldMatrix;

	//Mesh object to store the vertex buffer and index buffer
	Mesh* gameObj;

	//Material object to store the vertex shader and pixel shader
	Material* material;

	float direction = 1;

	bool m_isControled;
	

};

