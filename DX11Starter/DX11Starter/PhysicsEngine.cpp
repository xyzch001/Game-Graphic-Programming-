#include "PhysicsEngine.h"


#include <iostream>

#define LEFT_ARROW_KEY 0x25
#define UP_ARROW_KEY 0x26
#define RIGHT_ARROW_KEY 0x27
#define DOWN_ARROW_KEY 0x28
#define PI 3.14159265359

PhysicsEngine::PhysicsEngine()
{
}

void PhysicsEngine::AddEntities(GameEntity* entity)
{
	
	m_entities.push_back(entity);
	
}

void PhysicsEngine::Simulate(float time)
{
	//for (unsigned int i = 0; i < m_entities.size(); i++) {
	//	m_entities[i]->SetTranslation(
	//		time * m_entities[i]->GetDirection() + m_entities[i]->GetCollider()->Center.x, 
	//		time * m_entities[i]->GetDirection() + m_entities[i]->GetCollider()->Center.y, 
	//		time * m_entities[i]->GetDirection() + m_entities[i]->GetCollider()->Center.z);
	//	m_entities[i]->SetWorldMatrix();
	//	DirectX::BoundingSphere newSphere;

	//	DirectX::XMMATRIX colliderTransform = DirectX::XMMatrixTranslation(
	//		time * m_entities[i]->GetDirection(),
	//		time * m_entities[i]->GetDirection(), 
	//		time * m_entities[i]->GetDirection());


	//	m_entities[i]->GetCollider()->Transform(newSphere, colliderTransform);
	//	//(*m_entities[i]->GetCollider()) = newSphere;
	//	m_entities[i]->collider = newSphere;
	//}

	for (unsigned int i = 0; i < m_entities.size(); i++) {
		m_entities[i]->SetTranslation(
			time * m_entities[i]->x_velocity + m_entities[i]->GetCollider()->Center.x,
			time * m_entities[i]->y_velocity + m_entities[i]->GetCollider()->Center.y,
			time * m_entities[i]->z_velocity + m_entities[i]->GetCollider()->Center.z);

		m_entities[i]->SetRotation(
			time * m_entities[i]->z_velocity / PI * 30,
			time * m_entities[i]->y_velocity / PI * 30,
			-time * m_entities[i]->x_velocity / PI * 30);
		m_entities[i]->SetWorldMatrix();
		DirectX::BoundingSphere newSphere;

		DirectX::XMMATRIX colliderTransform = DirectX::XMMatrixTranslation(
			time * m_entities[i]->x_velocity,
			time * m_entities[i]->y_velocity,
			time * m_entities[i]->z_velocity);


		m_entities[i]->GetCollider()->Transform(newSphere, colliderTransform);
		
		m_entities[i]->collider = newSphere;
		
		
		DirectX::XMVECTOR velocity = DirectX::XMVectorSet(m_entities[i]->x_velocity, m_entities[i]->y_velocity, m_entities[i]->z_velocity, 1.0f);
		velocity = DirectX::XMVectorLerp(velocity, DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f), time);
		m_entities[i]->x_velocity = DirectX::XMVectorGetX(velocity);
		m_entities[i]->y_velocity = DirectX::XMVectorGetY(velocity);
		m_entities[i]->z_velocity = DirectX::XMVectorGetZ(velocity);
	}
}

void PhysicsEngine::HandleCollisions()
{
	for (unsigned int i = 0; i < m_entities.size(); i++) {
				for (unsigned int j = i + 1; j < m_entities.size(); j++) {
					if (m_entities[i]->GetCollider()->BoundingSphere::Intersects(*m_entities[j]->GetCollider())) {
						float i_x_velocity = m_entities[i]->x_velocity;
						float i_y_velocity = m_entities[i]->y_velocity;
						float i_z_velocity = m_entities[i]->z_velocity;
						m_entities[i]->x_velocity = m_entities[j]->x_velocity;
						m_entities[i]->y_velocity = m_entities[j]->y_velocity;
						m_entities[i]->z_velocity = m_entities[j]->z_velocity;
						m_entities[j]->x_velocity = i_x_velocity;
						m_entities[j]->y_velocity = i_y_velocity;
						m_entities[j]->z_velocity = i_z_velocity;
						//std::cout << "collider" << std::endl;
						}
		
					
				}
			}
}

void PhysicsEngine::PlayerControl()
{
	for (unsigned int i = 0; i < m_entities.size(); i++) {
		if (m_entities[i]->GetIsControl()) {
			if (GetAsyncKeyState(UP_ARROW_KEY)) {
				m_entities[i]->z_velocity = 1.0f;
			}
			else if (GetAsyncKeyState(DOWN_ARROW_KEY)) {
				m_entities[i]->z_velocity = -1.0f;
			}
			else if (GetAsyncKeyState(LEFT_ARROW_KEY)) {
				m_entities[i]->x_velocity = -1.0f;
			}
			else if (GetAsyncKeyState(RIGHT_ARROW_KEY)) {
				m_entities[i]->x_velocity = 1.0f;
			}
			//std::cout << m_entities[i]->x_velocity << " " << m_entities[i]->y_velocity << " " << m_entities[i]->z_velocity << std::endl;
		}
	}
}

//void PhysicsEngine::AddObject(const PhysicsObject & object)
//{
//	m_objects.push_back(object);
//}
//
//void PhysicsEngine::Simulate(float deltaTime)
//{
//	for (unsigned int i = 0; i < m_objects.size(); i++) {
//		m_objects[i].Integrate(deltaTime);
//	}
//}
//
//void PhysicsEngine::HandleCollisions()
//{
//	for (unsigned int i = 0; i < m_objects.size(); i++) {
//		for (unsigned int j = i + 1; j < m_objects.size(); j++) {
//			IntersectData intersectData =
//				m_objects[i].GetBoundingSphere().IntersectBoundingSphere(
//					m_objects[j].GetBoundingSphere());
//
//			if (intersectData.GetDoesIntersect()) {
//				m_objects[i].SetVelocity(m_objects[i].GetVelocity() * -1);
//				m_objects[j].SetVelocity(m_objects[j].GetVelocity() * -1);
//			}
//		}
//	}
//}

PhysicsEngine::~PhysicsEngine()
{
}
