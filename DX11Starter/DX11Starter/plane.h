#pragma once
#include "math3d.h"
#include "BoundingSphere.h"

class plane
{
public:
	plane(const Vector3f& normal, float distance) :
		m_normal(normal),
		m_distance(distance) {}

	plane Normalized() const;
	IntersectData IntersectSphere(const BoundingSphere& other) const;

	inline const Vector3f& GetNormal() const { return m_normal; }
	inline float GetDistance()         const { return m_distance; }

	~plane();

private:
	const Vector3f m_normal;
	const float    m_distance;
};

