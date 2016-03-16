/*
 * Funnel.cpp
 *
 *  Created on: 07/03/2011
 *      Author: victor
 */

#include "../lang.h"

#include "../iff/exceptions/Exception.h"

#include <QtGlobal>



#include "Vector.h"
#include "Funnel.h"
#include "Triangle.h"
#include "TriangleChannel.h"


Vector3 TriangleChannel::getLeftEndPoint(int triangleID) const {
	Triangle* triangle1 = triangleNodes->get(triangleID);
	Triangle* triangle2 = triangleNodes->get(++triangleID);

	int firstCommon = -1, secondCommon = -1;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (triangle1->getVertex(i) == triangle2->getVertex(j)) {
				if (firstCommon == -1) {
					firstCommon = i;
				} else if (secondCommon == -1) {
					secondCommon = i;
					break;
				}
			}

		}
	}

	Vector3 pointA = triangle1->getVertex(firstCommon);
	Vector3 pointB = triangle1->getVertex(secondCommon);

	int apexPoint = 0;

	for (int i = 0; i < 3; ++i) {
		if (i != firstCommon && i != secondCommon) {
			apexPoint = i;
			break;
		}
	}

	Vector3 apex = triangle1->getVertex(apexPoint);

	if (Funnel::area(apex, pointA, pointB) <= 0)
		return pointB;
	else
		return pointA;

	//throw Exception("no common vertex found");
}

Vector3 TriangleChannel::getRightEndPoint(int triangleID) const {
	/*Triangle* triangle1 = triangleNodes->get(triangleID);

		  if (triangleID >= triangleNodes->size() - 1) {
			  triangleID--;
		  } else
			  triangleID++;

		  Triangle* triangle2 = triangleNodes->get(triangleID);

		  for (int i = 2; i >= 0; --i) {
			  for (int j = 0; j < 3; ++j) {
				  if (triangle1->getVertex(i) == triangle2->getVertex(j))
					  return triangle1->getVertex(i);
			  }
		  }

		  throw Exception("no common vertex found");*/

	Triangle* triangle1 = triangleNodes->get(triangleID);
	Triangle* triangle2 = triangleNodes->get(++triangleID);

	int firstCommon = -1, secondCommon = -1;

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			if (triangle1->getVertex(i) == triangle2->getVertex(j)) {
				if (firstCommon == -1) {
					firstCommon = i;
				} else if (secondCommon == -1) {
					secondCommon = i;
					break;
				}
			}

		}
	}

	Vector3 pointA = triangle1->getVertex(firstCommon);
	Vector3 pointB = triangle1->getVertex(secondCommon);

	int apexPoint = 0;

	for (int i = 0; i < 3; ++i) {
		if (i != firstCommon && i != secondCommon) {
			apexPoint = i;
			break;
		}
	}

	Vector3 apex = triangle1->getVertex(apexPoint);

	if (Funnel::area(apex, pointA, pointB) <= 0)
		return pointA;
	else
		return pointB;
}

float Funnel::area(const Vector3& a, const Vector3& b, const Vector3& c) {
	float ax = b[0] - a[0];
	float ay = b[2] - a[2];

	float bx = c[0] - a[0];
	float by = c[2] - a[2];
	/*
	float ax = vertices[3] - vertices[0];
	float ay = vertices[5] - vertices[2];

	float bx = vertices[6] - vertices[0];
	float by = vertices[8] - vertices[2];*/

	return bx * ay - ax * by;
}

bool Funnel::equal(const Vector3& a, const Vector3& b) {
	return (a.squaredDistanceTo(b) < 0.001 * 0.001);
}

Vector<Vector3>* Funnel::funnel(const TriangleChannel& channel) {
	Vector<Vector3>* path = new Vector<Vector3>();

	path->add(channel.getStart());

	if (channel.size() < 2) {
		path->add(channel.getGoal());

		return path;
	}

	int apexIndex = 0, leftIndex = 0, rightIndex = 0, npts = 0;

	Vector3 portalApex = channel.getStart();
	Vector3 portalLeft = channel.getStart();//channel.getLeftEndPoint(0);
	Vector3 portalRight = channel.getStart();//channel.getRightEndPoint(0);

	for (int i = 1; i < channel.size(); ++i) {
		Vector3 left;
		Vector3 right;

		if (i == channel.size() - 1) {
			left = channel.getGoal();
			right = channel.getGoal();
		} else {
			left = channel.getLeftEndPoint(i); //getRightEndPoint
			right = channel.getRightEndPoint(i); //getLeftEndPoint
		}

		if (area(portalApex, portalRight, right) <= 0.0f) {
			if ((portalApex == portalRight) || area(portalApex, portalLeft, right) > 0.0f) {
				// Tighten the funnel.
				portalRight = right;
				//vcpy(portalRight, right);
				rightIndex = i;
			} else {
				// Right over left, insert left to path and restart scan from portal left point.
				/*vcpy(&pts[npts*2], portalLeft);
             npts++;*/

				path->add(portalLeft);
				// Make current left the new apex.
				//vcpy(portalApex, portalLeft);
				portalApex = portalLeft;

				apexIndex = leftIndex;
				// Reset portal
				//vcpy(portalLeft, portalApex);
				portalLeft = portalApex;
				//vcpy(portalRight, portalApex);
				portalRight = portalApex;

				leftIndex = apexIndex;
				rightIndex = apexIndex;
				// Restart scan
				i = apexIndex;
				continue;
			}
		}

		// Update left vertex.
		if (area(portalApex, portalLeft, left) >= 0.0f) {
			if ((portalApex == portalLeft) || area(portalApex, portalRight, left) < 0.0f) {
				// Tighten the funnel.
				//vcpy(portalLeft, left);
				portalLeft = left;
				leftIndex = i;
			} else {
				// Left over right, insert right to path and restart scan from portal right point.
				/*vcpy(&pts[npts*2], portalRight);
				 npts++;*/
				path->add(portalRight);
				// Make current right the new apex.
				//vcpy(portalApex, portalRight);
				portalApex = portalRight;

				apexIndex = rightIndex;
				// Reset portal
				//vcpy(portalLeft, portalApex);
				portalLeft = portalApex;
				//vcpy(portalRight, portalApex);
				portalRight = portalApex;
				leftIndex = apexIndex;
				rightIndex = apexIndex;
				// Restart scan
				i = apexIndex;
				continue;
			}
		}
	}

	path->add(channel.getGoal());

	return path;
}




/*Vector<Vector3>* Funnel::funnel(const TriangleChannel& channel) {
	Vector<Vector3>* path = new Vector<Vector3>();

	path->add(channel.getStart());

	if (channel.size() < 2) {
		path->add(channel.getGoal());

		return path;
	}

	FunnelDeque funnelDeque(channel.getStart());

	funnelDeque.addLeft(channel.getStart());
	funnelDeque.addRight(channel.getStart());

	Vector3 vertexLeft = channel.getLeftEndPoint(1);
	System::out << "channel.getLeftEndPoint(0) = " << vertexLeft.getX() << " " << vertexLeft.getY() << " " << vertexLeft.getZ() << endl;
	//add(funnelDeque, vertexLeft, LEFT, path);
	funnelDeque.addLeft(vertexLeft);

	Vector3 vertexRight = channel.getRightEndPoint(1);
	System::out << "channel.getRightEndPoint(0) = " << vertexRight.getX() << " " << vertexRight.getY() << " " << vertexRight.getZ() << endl;
	//add(funnelDeque, vertexRight, RIGHT, path);
	funnelDeque.addRight(vertexRight);



	System::out << "triangle:" << channel.getTriangle(0) << endl;

	Vector3 vertexLeftNew, vertexRightNew;

	for (int i = 2; i < channel.size() - 1; ++i) {
		System::out << "i:" << i << endl;
		System::out << "triangle:" << channel.getTriangle(i) << endl;

		vertexLeftNew = channel.getLeftEndPoint(i);
		System::out << "vertexLeftNew(" << i << ") = " << vertexLeftNew.getX() << " " << vertexLeftNew.getY() << " " << vertexLeftNew.getZ() << endl;
		vertexRightNew = channel.getRightEndPoint(i);
		System::out << "vertexRightNew(" << i << ") = " << vertexRightNew.getX() << " " << vertexRightNew.getY() << " " << vertexRightNew.getZ() << endl;

		if (vertexLeftNew == vertexLeft) {
			System::out << "vertexLeftNew == vertexLeft" << endl;

			vertexRight = vertexRightNew;

			add(funnelDeque, vertexRight, RIGHT, path);
		} else {
			System::out << "else" << endl;
			vertexLeft = vertexLeftNew;

			add(funnelDeque, vertexLeft, LEFT, path);
		}
	}

	add(funnelDeque, channel.getGoal(), POINT, path);

	return path;
}*/
/*
Algorithm 4 Funnel(Channel c, Point s, Point g) : Path
1: p.Clear()
2: if NumEdges(c) < 1 then
3: p.Add(s); p.Add(g)
4: return p
5: end if
6: AddVertex(s, p)
7: f = FunnelDeque(s)
8: vl = LeftEndpoint(c0); Add(f, vl, Left, p)
9: vr = RightEndpoint(c0); Add(f, vr, Right, p)
10: for i = 1 to NumEdges(c) do
11: v
0
l = LeftEndpoint(ci); v
0
r = RightEndpoint(ci)
12: if v
0
l = vl then
13: vr = v
0
r
; Add(f, vr, Right, p)
14: else
15: vl = v
0
l
; Add(f, vl
, Left, p)
16: end if
17: end for
18: Add(f, g, Point, p)
19: return p
 */
