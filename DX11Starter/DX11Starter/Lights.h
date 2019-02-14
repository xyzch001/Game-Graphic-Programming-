#pragma once
#include <DirectXMath.h>

// The light struct

struct DirectionalLight
{
	DirectX::XMFLOAT4 AmbientColor;
	DirectX::XMFLOAT4 DiffuseColor;
	DirectX::XMFLOAT3 Direction;
};

struct PointLight 
{
	DirectX::XMFLOAT3 position;
	float junk = 0.0f;          //This junk is to fill the 4bit to 16bit before copy this data to GPU
	DirectX::XMFLOAT3 color;
};