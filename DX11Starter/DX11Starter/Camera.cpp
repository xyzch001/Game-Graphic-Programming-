#include "Camera.h"

using namespace DirectX;

Camera::Camera(float screenWidth, float screenHeight)
{
	view = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	projection = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f,
	};

	cameraPosition = XMVectorSet(0.0f, 0.0f, -5.0f, 0.0f);;
	cameraDirection = XMVectorSet(0.0f, 0.0f, 1.0f, 0.0f);
	cameraUp = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	aroundX = 0.0f;
	aroundY = 0.0f;

	setProjection(screenWidth, screenHeight, 0.25f * 3.1415926535f);
}


Camera::~Camera()
{
}

void Camera::Update(float deltaTime)
{
	XMMATRIX cameraRotationX = DirectX::XMMatrixRotationX(aroundX);
	XMMATRIX cameraRotationY = DirectX::XMMatrixRotationY(aroundY);
	cameraMovement(deltaTime);
	cameraDirection = XMVector3Transform(cameraDirection,  cameraRotationX * cameraRotationY);
	XMStoreFloat4x4(&view, XMMatrixTranspose(XMMatrixLookToLH(cameraPosition, cameraDirection, cameraUp)));
	aroundX = 0.0f;
	aroundY = 0.0f;
}

void Camera::cameraMovement(float deltaTime)
{
	if (GetAsyncKeyState('W') & 0x8000) {
		cameraPosition += cameraDirection * deltaTime;
	}
	else if (GetAsyncKeyState('S') & 0x8000) {
		cameraPosition -= cameraDirection * deltaTime;
	}

	if (GetAsyncKeyState('A') & 0x8000) {
		cameraPosition += XMVector3Cross(cameraDirection, cameraUp) * deltaTime;
		
	}
	else if (GetAsyncKeyState('D') & 0x8000) {
		cameraPosition -= XMVector3Cross(cameraDirection, cameraUp) * deltaTime;
	}

	if (GetAsyncKeyState(' ') & 0x8000) {
		cameraPosition += XMVectorSet(0.0f, deltaTime, 0.0f, 0.0f);
	}
	else if (GetAsyncKeyState('X') & 0x8000) {
		cameraPosition += XMVectorSet(0.0f, -deltaTime, 0.0f, 0.0f);
	}



}

DirectX::XMFLOAT4X4 Camera::getView()
{
	return view;
}

DirectX::XMFLOAT4X4 Camera::getProjection()
{
	return projection;
}

void Camera::setProjection(float width, float height, float fov)
{
	// Create the Projection matrix
	// - This should match the window's aspect ratio, and also update anytime
	//    the window resizes (which is already happening in OnResize() below)
	XMMATRIX P = XMMatrixPerspectiveFovLH(
		0.25f * 3.1415926535f,		// Field of View Angle
		(float)width / height,		// Aspect ratio
		0.1f,						// Near clip plane distance
		100.0f);					// Far clip plane distance
	XMStoreFloat4x4(&projection, XMMatrixTranspose(P)); // Transpose for HLSL!
}

void Camera::setRotationX(float x)
{
	aroundY += x * 0.001f;
}

void Camera::setRotationY(float y)
{
	aroundX += y * 0.001f;
}
