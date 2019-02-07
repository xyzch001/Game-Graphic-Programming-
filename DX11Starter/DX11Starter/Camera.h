#pragma once

#include <DirectXMath.h>
#include <vector>
#include <string>
#include <Windows.h>

class Camera
{
public:
	Camera(float screenWidth, float screenHeight);
	~Camera();
	
	void Update(float deltaTime);
	void cameraMovement(float detlaTime);
	DirectX::XMFLOAT4X4 getView();
	DirectX::XMFLOAT4X4 getProjection();
	void setProjection(float width, float height, float fov);
	void setRotationX(float x);
	void setRotationY(float y);

private:
	DirectX::XMFLOAT4X4 view;
	DirectX::XMFLOAT4X4 projection;
	
	DirectX::XMVECTOR cameraPosition;
	DirectX::XMVECTOR cameraDirection;
	DirectX::XMVECTOR cameraUp;
	float aroundX;
	float aroundY;


};

