#include "Camera.h"

using namespace DirectX;

Camera::Camera()
{
}


Camera::~Camera()
{
}

void Camera::Update()
{
	XMMATRIX cameraRotationX = DirectX::XMMatrixRotationX(aroundX);
	XMMATRIX cameraRotationY = DirectX::XMMatrixRotationY(aroundY);
	XMVector3Transform(cameraRotation, cameraRotationX * cameraRotationY);
	XMStoreFloat4x4(&view, XMMatrixTranspose(XMMatrixLookToLH(cameraPosition, cameraRotation, cameraUp)));
}
