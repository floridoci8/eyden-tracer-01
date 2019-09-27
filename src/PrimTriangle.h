// Triangle Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Triangle Geaometrical Primitive class
 */
class CPrimTriangle : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param a Position of the first vertex
	 * @param b Position of the second vertex
	 * @param c Position of the third vertex
	 * @param color Color of the shape
	 */
	CPrimTriangle(Vec3f color, Vec3f a, Vec3f b, Vec3f c)
		: CPrim(color)
		, m_a(a)
		, m_b(b)
		, m_c(c)
  	{}
	virtual ~CPrimTriangle(void) = default;
	
	virtual bool Intersect(Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---
		Vec3f normab = (m_b - ray.org).cross(m_a - ray.org);
		Vec3f normbc = (m_c - ray.org).cross(m_b - ray.org);
		Vec3f normac = (m_a - ray.org).cross(m_c - ray.org);

		float sum = normab.dot(ray.dir) + normbc.dot(ray.dir) + normac.dot(ray.dir);
		float lambda1 = normab.dot(ray.dir) / sum;
		float lambda2 = normbc.dot(ray.dir) / sum;
		float lambda3 = normac.dot(ray.dir) / sum;

		if(lambda1 < 0 || lambda2 < 0 || lambda3 < 0)
			return false;

		Vec3f normal = (m_b - m_a).cross(m_c - m_a);

		float n1 = -normal.dot(ray.org - m_a);
		float n2 = normal.dot(ray.dir);
		float t;

		if(n2 == 0)
			return false;
		else 
			t = n1 / n2;

		if(t < Epsilon || t > ray.t)
			return false;
		
		ray.t = t;
		return true;
	}

	
private:
	Vec3f m_a;	///< Position of the first vertex
	Vec3f m_b;	///< Position of the second vertex
	Vec3f m_c;	///< Position of the third vertex
};
