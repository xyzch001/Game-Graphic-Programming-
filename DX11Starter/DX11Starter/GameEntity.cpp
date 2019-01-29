#include "GameEntity.h"



GameEntity::GameEntity(Mesh* object)
{
	gameObj = object;

	//Set default vaules for the matrix
	translation =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	rotation =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	scale =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	worldMatrix =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

}


GameEntity::~GameEntity()
{
}

ID3D11Buffer * GameEntity::GetVertexBuffer()
{
	return gameObj->GetVertexBuffer();
}

void GameEntity::SetWorldMatrix()
{
}

DirectX::XMFLOAT4X4 GameEntity::GetWorldMatrix()
{
	return DirectX::XMFLOAT4X4();
}

void GameEntity::SetTranslation(float x, float y, float z)
{
}

void GameEntity::SetRotation(float x, float y, float z)
{
}

void GameEntity::SetScale(float x, float y, float z)
{
}

void GameEntity::Move(float x, float y, float z)
{
}

void GameEntity::MoveForward(float x, float y, float z)
{
}
