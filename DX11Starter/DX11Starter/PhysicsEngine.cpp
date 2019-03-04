#include "PhysicsEngine.h"


#include <iostream>



PhysicsEngine::PhysicsEngine()
{
}

void PhysicsEngine::AddEntities(GameEntity* entity)
{
	
	m_entities.push_back(entity);
	
}

void PhysicsEngine::Simulate(float time)
{
	for (unsigned int i = 0; i < m_entities.size(); i++) {
		m_entities[i]->SetTranslation(time * m_entities[i]->GetDirection() + m_entities[i]->GetCollider()->Center.x, time * m_entities[i]->GetDirection() + m_entities[i]->GetCollider()->Center.y, time * m_entities[i]->GetDirection() + m_entities[i]->GetCollider()->Center.z);
		m_entities[i]->SetWorldMatrix();
		DirectX::BoundingSphere newSphere;
		m_entities[i]->GetCollider()->Transform(newSphere, m_entities[i]->getWordCollider());
		(*m_entities[i]->GetCollider()) = newSphere;
	}
}

void PhysicsEngine::HandleCollisions()
{
	for (unsigned int i = 0; i < m_entities.size(); i++) {
				for (unsigned int j = i + 1; j < m_entities.size(); j++) {
					if (m_entities[i]->GetCollider()->BoundingSphere::Intersects(*m_entities[j]->GetCollider())) {
						m_entities[i]->ChangeDirection();
						m_entities[j]->ChangeDirection();
						//std::cout << "collider" << std::endl;
						}
		
					
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
