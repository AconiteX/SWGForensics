/*
 * AABBTree.h
 *
 *  Created on: 05/12/2010
 *      Author: victor
 */

#ifndef AABBTREE_H_
#define AABBTREE_H_

#include "src/system/util/Vector3.h"

#include "src/system/util/Triangle.h"
#include <QVector>


class AABB {
	Vector3 mBounds[2]; // box bounds - min followed by max
public:

	AABB() {

	}

	AABB(const Vector3& boxmin, const Vector3& boxmax) {
		mBounds[0] = boxmin;
		mBounds[1] = boxmax;
	}

	inline void setMinBound(const Vector3& r) {
		mBounds[0] = r;
	}

	inline void setMaxBound(const Vector3& r) {
		mBounds[1] = r;
	}

	inline Vector3* getMinBound() {
		return &mBounds[0];
	}

	inline float getXMin() {
		return mBounds[0].getX();
	}

	inline float getYMin() {
		return mBounds[0].getY();
	}

	inline float getZMin() {
		return mBounds[0].getZ();
	}

	inline float getXMax() {
		return mBounds[1].getX();
	}

	inline float getYMax() {
		return mBounds[1].getY();
	}

	inline float getZMax() {
		return mBounds[1].getZ();
	}

	inline Vector3* getMaxBound() {
		return &mBounds[1];
	}

	// calc aabb from trilist
	AABB(const QVector<Triangle>& triangles);

	AABB(const AABB& aab) {
		mBounds[0] = aab.mBounds[0];
		mBounds[1] = aab.mBounds[1];
	}

	// returns a sub box of the octant specified, with the partition as the new corner.
	float distSqrd(const Vector3& point) const;

	// calculate the floating point error metric
	float errorMetric() const {
		return (Vector3(1.0f) + (mBounds[1] - mBounds[0])).length();
	}

	// intersection scalar (used for weighting in building aabb)
	uint32 longestAxis() const;
	// mid-point
	Vector3 midPoint() const {
		return (mBounds[0] + mBounds[1]) * .5f;
	}
	// copy
	void copy(const AABB& box) {
		mBounds[0] = box.mBounds[0];
		mBounds[1] = box.mBounds[1];
	}

	// make this box encompass the current box as well as this one - returns * this
	void encompass(const AABB& encbox);
	// render this box
	//void Render() const;



};

class AABBNode {
	AABB mBox; // node's bounding box
	AABBNode* mChildren[2]; // child nodes of this node
	QVector<Triangle> mTriangles; // triangles in this node

public:
	// heuristic struct, passed down the tree
	struct Heuristic {
		uint8 maxdepth; // maximum depth
		uint32 mintricnt; // minimum triangle count
		uint32 tartricnt; // target triangle count
		float minerror; // minimum error required
	};

	AABBNode() {
		mChildren[0] = NULL;
		mChildren[1] = NULL;
	}

	// constructs this aabb tree node from a triangle list and creates its children recursively
	AABBNode(QVector<Triangle>& trilist, int depth, const Heuristic& heurdata);


	// destructs this node
	~AABBNode();

	inline AABB* getMbox() {
		return &mBox;
	}

	inline AABBNode* getLeftChild() {
		return mChildren[0];
	}

	inline AABBNode* getRightChild() {
		return mChildren[1];
	}

	inline void setLeftChild(AABBNode* node) {
		mChildren[0] = node;
	}

	inline void setRightChild(AABBNode* node) {
		mChildren[1] = node;
	}

	// renders tris that collide with the sphere

	//bool testCollide(const Sphere& testsphere) const;

};
#endif /* AABTREE_H_ */
