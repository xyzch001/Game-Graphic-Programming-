#pragma once

#include "GameEntity.h"
#include <vector>

class PhysicsEngine
{
public:
	PhysicsEngine();
	void AddEntities(GameEntity* entity);
	void Simulate(float time);
	void HandleCollisions();
	inline GameEntity* GetEntity(unsigned int index) {
		return m_entities[index];
	}
	inline unsigned int GetNumEntities() {
		return (unsigned int)m_entities.size();
	}

	/*void AddObject(const PhysicsObject& object);
	void Simulate(float deltaTime);
	void HandleCollisions();*/

	////TODO temporary getters
	//inline const PhysicsObject& GetObject(unsigned int index) const {
	//	return m_objects[index];
	//}
	//inline unsigned int GetNumObjects() const {
	//	return (unsigned int)m_objects.size();
	//}


	~PhysicsEngine();

private:
	//std::vector<PhysicsObject> m_objects;
	std::vector<GameEntity*> m_entities;
};

