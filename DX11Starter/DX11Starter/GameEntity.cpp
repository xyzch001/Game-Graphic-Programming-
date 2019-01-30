#include "GameEntity.h"



GameEntity::GameEntity(Mesh* object)
{
	//accept the pointer of Mesh object
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

ID3D11Buffer * GameEntity::GetIndexBuffer()
{
	return gameObj->GetIndexBuffer();
}

int GameEntity::GetIndexCount()
{
	return gameObj->GetIndexCount();
}

void GameEntity::SetWorldMatrix()
{
	//Combine the translation, rotation and scale to the worldmatrix, remember the Transpose before storing
	DirectX::XMMATRIX objtranslation = DirectX::XMLoadFloat4x4(&translation);
	DirectX::XMMATRIX objRotation    = DirectX::XMLoadFloat4x4(&rotation);
	DirectX::XMMATRIX objScale       = DirectX::XMLoadFloat4x4(&scale);
	DirectX::XMMATRIX objWorldMatrix = objScale * objRotation * objtranslation;
	DirectX::XMStoreFloat4x4(&worldMatrix, DirectX::XMMatrixTranspose(objWorldMatrix));
}

DirectX::XMFLOAT4X4 GameEntity::GetWorldMatrix()
{
	return worldMatrix;
}

void GameEntity::SetTranslation(float x, float y, float z)
{
	DirectX::XMMATRIX objTranslation = DirectX::XMMatrixTranslation(x, y, z);
	DirectX::XMStoreFloat4x4(&translation, objTranslation);
}

void GameEntity::SetRotation(float x, float y, float z)
{
	DirectX::XMMATRIX objRotationX = DirectX::XMMatrixRotationX(x);
	DirectX::XMMATRIX objRotationY = DirectX::XMMatrixRotationY(y);
	DirectX::XMMATRIX objRotationZ = DirectX::XMMatrixRotationZ(z);
	DirectX::XMStoreFloat4x4(&rotation, objRotationX * objRotationY * objRotationZ);
}

void GameEntity::SetScale(float x, float y, float z)
{
	DirectX::XMMATRIX objScale = DirectX::XMMatrixScaling(x, y, z);
	DirectX::XMStoreFloat4x4(&scale, objScale);
}

void GameEntity::Move(float x, float y, float z)
{
}

void GameEntity::MoveForward(float x, float y, float z)
{
}
