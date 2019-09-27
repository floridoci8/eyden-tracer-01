// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "Prim.h"

/**
 * @brief Sphere Geaometrical Primitive class
 */
class CPrimSphere : public CPrim
{
public:
	/**
	 * @brief Constructor
	 * @param center Position of the center of the sphere
	 * @param radius Radius of the sphere
	 * @param color Color of the shape
	 */
	CPrimSphere(Vec3f color, Vec3f center, float radius)
		: CPrim(color)
		, m_center(center)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool Intersect(Ray &ray) override
	{
		// --- PUT YOUR CODE HERE ---
		// Reference for implentation of the intersection: https://www.scratchapixel.com/lessons/3d-basic-rendering/minimal-ray-tracer-rendering-simple-shapes/ray-sphere-intersection
		float x1, x2; // solutions for x if the ray intersects 
 
        float a = ray.dir.dot(ray.dir); 
        float b = 2 * ray.dir.dot(ray.org - m_center); 
        float c = (ray.org - m_center).dot(ray.org - m_center) - m_radius*m_radius; 
        float discriminant = b*b - 4*a*c;
		if(discriminant < 0)
			return false;
		else if( discriminant == 0){
			x1 = -b / (2*a);
			x2 = x1;
		} 
		else{
			x1 = (-b - sqrt(discriminant)) / (2*a);
			x2 = (-b + sqrt(discriminant)) / (2*a);
		}
        if (x1 > x2){
			float temp = x1;
			x1 = x2; 
			x2 = temp;
		} 
 
        if (x1 < Epsilon || x1 > ray.t){  
            x1 = x2; // if x1 is negative, let's use x2 instead 
            if (x1 < Epsilon || x1 > ray.t) return false; // both x1 and x2 are negative 
        } 
 
        ray.t = x1; 
 
		return true;
	}
	
	
private:
	Vec3f m_center;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

