#pragma once

#include <DirectXMath.h>
#include <vector>
#include <string>

class Camera
{
public:
	Camera();
	~Camera();
	void Update();

private:
	DirectX::XMFLOAT4X4 view;
	DirectX::XMVECTOR cameraPosition;
	DirectX::XMVECTOR cameraRotation;
	DirectX::XMVECTOR cameraUp = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	float aroundX;
	float aroundY;


};

