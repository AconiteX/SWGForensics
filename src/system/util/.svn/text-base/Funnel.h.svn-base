/*
 * Funnel.h
 *
 *  Created on: 07/03/2011
 *      Author: victor
 */

#ifndef FUNNEL_H_
#define FUNNEL_H_

#include "Vector3.h"
#include "Vector.h"
#include "Triangle.h"
#include "TriangleChannel.h"

namespace engine {
 namespace util {
  namespace u3d {

  class FunnelDeque {
  	Vector<Vector3> left;
  	Vector<Vector3> right;
  	Vector<Vector3> apex;

  public:
  	FunnelDeque(const Vector3& source) {
  		/*left.add(source);
  		right.add(source);*/
  		apex.add(source);
  	}

  	FunnelDeque(const FunnelDeque& d) {
  		left = d.left;
  		right = d.right;
  		apex = d.apex;
  	}

  	inline Vector3& getLeft(int i = 0) {
  		return left.get(i);
  	}

  	inline Vector3& getApex(int i = 0) {
  		return apex.get(i);
  	}

  	inline Vector3& getRight(int i = 0) {
  		return right.get(i);
  	}

  	inline void addLeft(const Vector3& v) {
  		left.insertElementAt(v, 0);
  		//left.add(v);
  	}

  	inline void addRight(const Vector3& r) {
  		right.insertElementAt(r, 0);
  		//right.add(r);
  	}

  	inline void addApex(const Vector3& a) {
  		apex.insertElementAt(a, 0);
  		//apex.add(a);
  	}

  	inline void popLeft() {
  		left.remove(left.size() - 1);
  	}

  	inline void popRight() {
  		right.remove(right.size() - 1);
  	}

  	inline void popApex() {
  		apex.remove(apex.size() - 1);
  	}

  };

  class Funnel {
  public:
  	const static int LEFT = 0;
  	const static int RIGHT = 1;
  	const static int POINT = 2;

  	//static void add(FunnelDeque& funnel, const Vector3& vertex, int type, Vector<Vector3>* path);

  	static float area(const Vector3& a, const Vector3& b, const Vector3& c);
  	static bool equal(const Vector3& a, const Vector3& b);

  	static Vector<Vector3>* funnel(const TriangleChannel& channel);
  };

  }
 }
}

using namespace engine::util::u3d;


#endif /* FUNNEL_H_ */
