#include "plane.h"





plane plane::Normalized() const
{
	float magnitude = m_normal.Length();

	return plane(m_normal / magnitude, m_distance / magnitude);
}

IntersectData plane::IntersectSphere(const BoundingSphere & other) const
{
	float distanceFromSphereCenter = fabs(m_normal.Dot(other.GetCenter()) - m_distance);
	float distanceFromSphere = distanceFromSphereCenter - other.GetRadius();
	return IntersectData(distanceFromSphere < 0, distanceFromSphere);
}

plane::~plane()
{
}
