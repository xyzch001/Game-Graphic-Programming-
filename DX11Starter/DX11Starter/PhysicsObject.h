#pragma once
#include "math3d.h"
#include "BoundingSphere.h"

class PhysicsObject
{
public:
	PhysicsObject(const Vector3f& position, const Vector3f velocity, float radius) :
		m_position(position),
		m_velocity(velocity),
	    m_radius(radius) {}

	void Integrate(float deltaTime);

	inline const Vector3f& GetPosition() const { return m_position; }
	inline const Vector3f& GetVelocity() const { return m_velocity; }
	inline float GetRadius() const { return m_radius; }
	inline BoundingSphere GetBoundingSphere() const {
		return BoundingSphere(m_position, m_radius);
	}

	inline void SetVelocity(const Vector3f& velocity) { m_velocity = velocity; }

	~PhysicsObject();

private:
	Vector3f m_position;
	Vector3f m_velocity;
	float m_radius;
};

