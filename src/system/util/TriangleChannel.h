/*
 * TriangleChannel.h
 *
 *  Created on: 08/03/2011
 *      Author: victor
 */

#ifndef TRIANGLECHANNEL_H_
#define TRIANGLECHANNEL_H_

#include "Triangle.h"
#include "Vector3.h"
#include "Vector.h"


namespace engine {
 namespace util {
  namespace u3d {

  class TriangleChannel {
	  Vector3 start;

	  Vector<Triangle*>* triangleNodes;

	  Vector3 goal;

  public:
	  TriangleChannel(const Vector3& startPoint, Vector<Triangle*>* nodes, const Vector3& goalPoint) {
		  start = startPoint;

		  triangleNodes = nodes;

		  goal = goalPoint;
	  }

	  TriangleChannel(const TriangleChannel& ch) {
		  start = ch.start;

		  triangleNodes = ch.triangleNodes;

		  goal = ch.goal;
	  }

	  Vector3 getLeftEndPoint(int triangleID) const;

	  Vector3 getRightEndPoint(int triangleID) const;

	  TriangleChannel& operator=(const TriangleChannel& ch) {
		  if (this == &ch)
			  return *this;

		  start = ch.start;

		  triangleNodes = ch.triangleNodes;

		  goal = ch.goal;

		  return *this;
	  }

	  inline Vector3 getStart() const {
		  return start;
	  }

	  inline Triangle* getTriangle(int i) const {
		  return triangleNodes->get(i);
	  }

	  inline int size() const {
		  return triangleNodes->size();
	  }

	  inline Vector3 getGoal() const {
		  return goal;
	  }
  };


  }
 }
}

using namespace engine::util::u3d;


#endif /* TRIANGLECHANNEL_H_ */
