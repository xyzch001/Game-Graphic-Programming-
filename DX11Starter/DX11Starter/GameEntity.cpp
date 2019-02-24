#include "GameEntity.h"



GameEntity::GameEntity(Mesh* meshObject, Material* materialObj)
{
	//accept the pointer of Mesh object
	gameObj = meshObject;

	//accept the pointer of Material object
	material = materialObj;
	
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
	DirectX::XMMATRIX objTranslation = DirectX::XMLoadFloat4x4(&translation);
	DirectX::XMMATRIX objRotation    = DirectX::XMLoadFloat4x4(&rotation);
	DirectX::XMMATRIX objScale       = DirectX::XMLoadFloat4x4(&scale);
	DirectX::XMMATRIX objWorldMatrix = objScale * objRotation * objTranslation * objRotation;
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

void GameEntity::prepareMaterial(DirectX::XMFLOAT4X4 viewMatrix, DirectX::XMFLOAT4X4 projectionMatrix, DirectX::XMFLOAT3 cameraPosition)
{
	// Send data to shader variables
	//  - Do this ONCE PER OBJECT you're drawing
	//  - This is actually a complex process of copying data to a local buffer
	//    and then copying that entire buffer to the GPU.  
	//  - The "SimpleShader" class handles all of that for you.
	material->getVertexShader()->SetMatrix4x4("world", worldMatrix);
	material->getVertexShader()->SetMatrix4x4("view", viewMatrix);
	material->getVertexShader()->SetMatrix4x4("projection", projectionMatrix);

	material->getPixelShader()->SetFloat3("CameraPosition", cameraPosition);

	material->getPixelShader()->SetSamplerState("basicSampler", material->getSamplerState());
	material->getPixelShader()->SetShaderResourceView("diffuseTexture", material->getSRV());

	// Once you've set all of the data you care to change for
	// the next draw call, you need to actually send it to the GPU
	//  - If you skip this, the "SetMatrix" calls above won't make it to the GPU!
	material->getVertexShader()->CopyAllBufferData();
	material->getPixelShader()->CopyAllBufferData();
	// Set the vertex and pixel shaders to use for the next Draw() command
	//  - These don't technically need to be set every frame...YET
	//  - Once you start applying different shaders to different objects,
	//    you'll need to swap the current shaders before each draw
	material->getVertexShader()->SetShader();
	material->getPixelShader()->SetShader();
}
