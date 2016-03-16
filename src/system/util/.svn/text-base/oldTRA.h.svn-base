/*
 * oldTRA.h
 *
 *  Created on: 11/03/2011
 *      Author: TheAnswer
 */

#ifndef OLDTRA_H_
#define OLDTRA_H_

/*
 * TriangulationAStarAlgorithm.h
 *
 *  Created on: 11/03/2011
 *      Author: TheAnswer
 */

#ifndef TRIANGULATIONASTARALGORITHM_H_
#define TRIANGULATIONASTARALGORITHM_H_


#include "PriorityQueue.h"
#include "../lang.h"

#include "VectorMap.h"
#include "Funnel.h"

#include "AStarAlgorithm.h"

template<class Graph, class Node>
class TriangulationAStarAlgorithm {
public:
	template <class IDType>
	static Vector<Node*>* search(Graph* graph, Node* source, Node* target) {
		VectorMap<IDType, AStarNode<Node, IDType>*  > openSet;
		openSet.setAllowDuplicateInsertPlan();
		openSet.setNullValue(NULL);

		PriorityQueue priorityQueue;
		VectorMap<IDType, AStarNode<Node, IDType>* >  closeSet;
		closeSet.setAllowDuplicateInsertPlan();
		closeSet.setNullValue(NULL);

		AStarNode<Node, IDType>*  start = new AStarNode<Node, IDType>(source, 0, graph->calculateManhattanDistance(source, target));
		openSet.put(source->getID(), start);
		priorityQueue.add(start);

		AStarNode<Node, IDType>*  goal = NULL;

		while (openSet.size() > 0) {
			AStarNode<Node, IDType>*  x = (AStarNode<Node, IDType>*)const_cast<PriorityQueueEntry*>(priorityQueue.poll());
			openSet.drop(x->getID());

			if (TypeInfo<IDType>::compare(x->getID(), target->getID()) == 0) {
				//if (x->getID() == target->getID()) {
				goal = x;

				break;
			} else {
				closeSet.put(x->getID(), x);

				Vector<Node*>* neighbors = x->getNode()->getNeighbors();

				for (int i = 0; i < neighbors->size(); ++i) {
					Node* neighbor = neighbors->get(i);

					AStarNode<Node, IDType>* visited = closeSet.get(neighbor->getID());

					/*float h = graph->calculateManhattanDistance(x->getNode(), neighbor);
					float g = x->getGeodisc() + h;*/

					Triangle* triangle1 = x->getNode();
					Triangle* triangle2 = neighbor;

					int firstCommon = -1, secondCommon = -1;

					for (int i = 0; i < 3; ++i) {
						for (int j = 0; j < 3; ++j) {
							if (triangle1->getVertex(i) == neighbor->getVertex(j)) {
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

					//distance to both points

					float distA = pointA.squaredDistanceTo(target->getBarycenter());
					float distB = pointA.squaredDistanceTo(target->getBarycenter());

					Vector3 closestPoint;

					float ourEstDist;
					if (distA < distB) {
						closestPoint = pointA;
						ourEstDist = distA;
					} else {
						closestPoint = pointB;
						ourEstDist = distB;
					}

					float h = ourEstDist;

					distA = pointA.squaredDistanceTo(source->getBarycenter());
					distB = pointA.squaredDistanceTo(source->getBarycenter());

					float distEA;

					if (distA < distB) {
						closestPoint = pointA;
						distEA = distA;
					} else {
						closestPoint = pointB;
						distEA = distB;
					}

					Vector<Triangle*> trianglesToFunnel;

					trianglesToFunnel.add(neighbor);

					AStarNode<Node, IDType>* parent = x;

					while (parent != NULL) {
						trianglesToFunnel.insertElementAt(parent->getNode(), 0);
						parent = parent->getCameFrom();
					}


					TriangleChannel triangleChannel(source->getBarycenter(), &trianglesToFunnel, neighbor->getBarycenter());
					Vector<Vector3>* funnelPath = Funnel::funnel(triangleChannel);

					float funnelDist = 0;

					for (int i = 1; i < funnelPath->size(); ++i) {
						funnelDist += funnelPath->get(i).squaredDistanceTo(funnelPath->get(i - 1));
					}

					delete funnelPath;

					float g = MAX(MAX(x->getGeodisc(), distEA), funnelDist);



					if (visited == NULL) {
						AStarNode<Node, IDType>*  n = openSet.get(neighbor->getID());

						if (n == NULL) {



							n = new AStarNode<Node, IDType>(neighbor, g, h);
							n->setCameFrom(x);
							openSet.put(neighbor->getID(), n);

							priorityQueue.add(n);
						} else if (g < n->getGeodisc()) {
							n->setCameFrom(x);
							n->setGeodisc(g);
							n->setHeuristic(h);
						}
					}
				}
			}
		}

		if (goal == NULL)
			return NULL;

		Vector<Node*>* path = new Vector<Node*>();
		path->add(goal->getNode());

		AStarNode<Node, IDType>* parent = goal->getCameFrom();

		while (parent != NULL) {
			path->insertElementAt(parent->getNode(), 0);
			parent = parent->getCameFrom();
		}

		return path;
	}
};


#endif /* TRIANGULATIONASTARALGORITHM_H_ */


#endif /* OLDTRA_H_ */
