/*
 * Triangle.h
 *
 *  Created on: 05/12/2010
 *      Author: victor
 */

#ifndef TRIANGLE_H_
#define TRIANGLE_H_

#include "Vector3.h"


class AABB;

class Triangle {
protected:
	Vector3 vertices[3];

public:
	Triangle() {

	}

	Triangle(const Triangle& tri) {
		vertices[0] = tri.vertices[0];
		vertices[1] = tri.vertices[1];
		vertices[2] = tri.vertices[2];
	}

	Triangle(const Vector3 vert[]) {
		this->vertices[0] = vert[0];
		this->vertices[1] = vert[1];
		this->vertices[2] = vert[2];
	}

	Triangle& operator=(const Triangle& tri) {
		vertices[0] = tri.vertices[0];
		vertices[1] = tri.vertices[1];
		vertices[2] = tri.vertices[2];

		return *this;
	}

	void set(const Vector3 vert[]) {
		this->vertices[0] = vert[0];
		this->vertices[1] = vert[1];
		this->vertices[2] = vert[2];
	}

	// distance squared to a point from the tri
	//float distSqrd(const Vector3& point) const;

	// calculate the midpoint
	Vector3 midPoint() const {
		return (vertices[0] + vertices[1] + vertices[2]) * (1.0f / 3.0f);
	}

	AABB triAABB() const;

	Vector3 getNormal() const {
		Vector3 normal;

		Vector3 v1 = vertices[1] - vertices[0];
		Vector3 v2 = vertices[2] - vertices[0];

		normal = v1.crossProduct(v2);

		normal.normalize();

		return normal;
	}

	inline Vector3 getVertex(int i) const {
		if (i > 2)
			ArrayIndexOutOfBoundsException(i);

		return vertices[i];
	}
};


#endif /* TRIANGLE_H_ */
