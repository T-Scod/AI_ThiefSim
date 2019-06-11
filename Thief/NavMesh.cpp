#include "NavMesh.h"
#include <Queue.h>
#include "poly2tri/poly2tri.h"

// creates the base walkable area
NavMesh::NavMesh(float width, float height)
{
	m_polygons.push_back({});
	m_polygons[0].push_back(new p2t::Point(0, 0));
	m_polygons[0].push_back(new p2t::Point(0, height));
	m_polygons[0].push_back(new p2t::Point(width, height));
	m_polygons[0].push_back(new p2t::Point(width, 0));

	m_cdt = new p2t::CDT(m_polygons[0]);
}
NavMesh::~NavMesh()
{
	for (auto node : m_nodes)
	{
		delete node;
		node = nullptr;
	}
	m_cdt = nullptr;
	delete m_cdt;
}

// returns true if the obstacle was added safely (does not overlap)
bool NavMesh::addObstacle(float x, float y, float width, float height, float padding)
{
	// checks if there is an existing obstacle that would overlap with the requested obstacle
	for (auto& ob : m_obstacles)
	{
		if (((ob.x + ob.w + ob.padding) < x - padding ||
			(ob.y + ob.h + ob.padding) < y - padding ||
			(x + width + padding) < ob.x - ob.padding ||
			(y + height + padding) < ob.y - ob.padding) == false)
		{
			return false;
		}
	}

	// creates the obstacle and adds it to the container
	Obstacle o = { x, y, width, height, padding };
	m_obstacles.push_back(o);

	// adds the corners of the square to the container
	m_polygons.push_back({});
	m_polygons.back().push_back(new p2t::Point(o.x - padding, o.y - padding));
	m_polygons.back().push_back(new p2t::Point(o.x - padding, o.y + o.h + padding));
	m_polygons.back().push_back(new p2t::Point(o.x + o.w + padding, o.y + o.h + padding));
	m_polygons.back().push_back(new p2t::Point(o.x + o.w + padding, o.y - padding));
	m_cdt->AddHole(m_polygons.back());

	return true;
}

// triangulates the walkable area and builds the nav mesh nodes
void NavMesh::build()
{
	m_cdt->Triangulate();

	// first convert triangles to NavMesh::Node's
	std::vector<p2t::Triangle*> triangles = m_cdt->GetTriangles();
	for (auto tri : triangles)
	{
		Node* n = new Node();

		n->vertices.push_back({ (float)tri->GetPoint(0)->x, (float)tri->GetPoint(0)->y });
		n->vertices.push_back({ (float)tri->GetPoint(1)->x, (float)tri->GetPoint(1)->y });
		n->vertices.push_back({ (float)tri->GetPoint(2)->x, (float)tri->GetPoint(2)->y });

		n->position.x = (n->vertices[0].x + n->vertices[1].x + n->vertices[2].x) / 3;
		n->position.y = (n->vertices[0].y + n->vertices[1].y + n->vertices[2].y) / 3;

		m_nodes.push_back(n);
	}

	// then link nodes that share triangle edges
	for (auto nodeA : m_nodes)
	{
		for (auto nodeB : m_nodes)
		{
			// ignore same node
			if (nodeA == nodeB)
			{
				continue;
			}

			// share verts?
			int sharedVerts = 0;
			for (auto& vA : nodeA->vertices)
			{
				for (auto& vB : nodeB->vertices)
				{
					if (vA.x == vB.x && vA.y == vB.y)
					{
						sharedVerts++;
					}
				}
			}

			// link if two verts shared (should only ever be 0, 1, 2)
			if (sharedVerts == 2)
			{
				float mag = Vector2(nodeB->position - nodeA->position).magnitudeSqr();
				// add links to both nodes
				nodeA->connections.push_back(new Node2::Edge2(nodeB, mag));
				nodeB->connections.push_back(new Node2::Edge2(nodeA, mag));
			}
		}
	}

	// cleanup polygons
	for (auto& p : m_polygons)
	{
		for (auto ptr : p)
		{
			delete ptr;
		}
	}
	m_polygons.clear();

	// close up Poly2Tri
	delete m_cdt;
	m_cdt = nullptr;
}

// given a list of pathfinding nodes from a pathfinding search, this smooths the path using a funneling algorithm
// funneling algorithm from (http://digestingduck.blogspot.com.au/2010/03/simple-stupid-funnel-algorithm.html)
int NavMesh::smoothPath(const std::list<Node*>& path, std::list<Vector2>& smoothPath)
{
	if (path.size() == 0)
	{
		return 0;
	}

	smoothPath.clear();

	// build portal list
	int index = 0;
	Vector2* portals = new Vector2[(path.size() + 1) * 2];

	// add start node as first portal
	portals[index++] = ((Node*)path.front())->position;
	portals[index++] = ((Node*)path.front())->position;

	Node* prev = nullptr;

	for (auto it = path.begin(); it != path.end(); ++it)
	{
		if (it != path.begin())
		{
			Node* node = (Node*)*it;

			// find vertices they share to make a portal from
			Vector2 adjacent[2];
			prev->getAdjacentVertices(node, adjacent);

			// get a vector going from previous node to this one
			float mag = Vector2(node->position - prev->position).magnitudeSqr();

			Vector2 fromPrev = {};
			if (mag > 0)
			{
				fromPrev = node->position - prev->position;
				fromPrev.normalise();
			}

			// now get a vector going to the first adjacent vertex on the edge
			mag = Vector2(adjacent[0] - prev->position).magnitudeSqr();

			Vector2 toAdj0 = {};
			if (mag > 0)
			{
				toAdj0 = adjacent[0] - prev->position;
				toAdj0.normalise();
			}

			if (fromPrev.cross(toAdj0) > 0)
			{
				portals[index++] = adjacent[0];
				portals[index++] = adjacent[1];
			}
			else
			{
				portals[index++] = adjacent[1];
				portals[index++] = adjacent[0];
			}
		}

		prev = (Node*)*it;
	}

	// add last node as end portal
	portals[index++] = ((Node*)path.back())->position;
	portals[index++] = ((Node*)path.back())->position;

	// run funnelling algorithm
	Vector2 out[100];
	int count = stringPull(portals, index / 2, out, 100);

	// gather up shortest path
	for (int i = 0; i < count; i++)
	{
		smoothPath.push_back(out[i]);
	}

	// cleanup and return length of path
	delete[] portals;
	return (int)smoothPath.size();
}

// access random node
Node* NavMesh::getRandomNode() const {
	if (m_nodes.empty())
	{
		return nullptr;
	}

	return m_nodes[rand() % m_nodes.size()];
}
// closest node to the coordinate
Node* NavMesh::findClosest(float x, float y) const {

	Node* closest = nullptr;
	float closestDist = 2000 * 2000;

	// iterates through each node and compares the distance between the node and the coordinate
	for (auto node : m_nodes)
	{
		// determines the distance between the coordinate and the node
		float dist = (node->position.x - x) * (node->position.x - x) + (node->position.y - y) * (node->position.y - y);

		// compares the distances
		if (dist < closestDist)
		{
			// sets the node to the current closest node
			closest = node;
			// replaces the variable with the newfound closest distance
			closestDist = dist;
		}
	}

	return closest;
}

// custom A* function for nav mesh
std::list<Node*> NavMesh::aStar(Node * start, Node * end)
{
	// contains the untraversed nodes
	Queue<Node*> priorityQueue;
	// contains the traversed nodes
	Queue<Node*> traversedQueue;

	// sets all the nodes g scores to infinity
	// allows for checking for occurance of processes
	for (auto node : m_nodes)
	{
		node->gScore = INFINITY;
	}

	// sets the start node's parent to itself
	start->parent = nullptr;
	// sets the start node's g score to 0
	start->gScore = 0.0f;
	// adds the start node to the priority queue
	priorityQueue.push(start);

	// a pointer to the node being inspected
	Node* currentNode = new Node();

	//iterates while there are still untraversed nodes
	while (!priorityQueue.empty())
	{
		// sorts the priority nodes by lowest to highest f score using bubble sort
		for (unsigned int i = 0; i < priorityQueue.size(); i++)
		{
			for (unsigned int j = 0; j < priorityQueue.size() - 1; j++)
			{
				// if the earlier node's f score is greater than the next node's f score then swap
				if (priorityQueue[j]->fScore > priorityQueue[j + 1]->fScore)
				{
					Node* temp = priorityQueue[j];
					priorityQueue[j] = priorityQueue[j + 1];
					priorityQueue[j + 1] = temp;
					// deletes the temp
					temp = nullptr;
					delete temp;
				}
			}
		}

		// sets the first node in the priority queue to the current node
		currentNode = priorityQueue.front();

		// breaks the loop if the end node is reached because it has the lowest possible g score
		if (currentNode == end)
		{
			break;
		}

		// moves the current node into the transversed queue
		priorityQueue.pop();
		traversedQueue.push(currentNode);

		// iterates through all of the edges of the current node
		for (auto edge : currentNode->connections)
		{
			// adds the connection to the priority queue if it has not already been traversed
			if (!traversedQueue.search((Node*)edge->target))
			{
				// checks if the target already has a smaller g score, implying that there is a faster way to the target
				if (edge->target->gScore > currentNode->gScore + edge->cost)
				{
					// adds the next node into the priority queue
					priorityQueue.push((Node*)edge->target);

					// sets the target's g score to the total g score plus the cost required to reach the target
					edge->target->gScore = currentNode->gScore + edge->cost;
					// sets the heuristic to the distance between the next node and the end node
					edge->target->hScore = edge->target->position.distanceSqr(end->position);
					// the final score is the sum of the scores
					edge->target->fScore = edge->target->gScore + edge->target->hScore;

					// sets the target's parent to the node that it came from
					edge->target->parent = currentNode;
				}
			}
		}
	}

	// contains the path
	std::list<Node*> path;
	// sets the current node to the end node
	currentNode = end;
	// runs as long as the current node is not null
	while (currentNode != nullptr)
	{
		// adds the position of the node to the path
		path.push_front(currentNode);
		// sets the current node to its own parent
		currentNode = (Node*)currentNode->parent;
	}

	// cleans up the assets
	priorityQueue.clear();
	traversedQueue.clear();
	currentNode = nullptr;
	delete currentNode;

	// returns the container of positions
	return path;
}

// funneling algorithm taken from
// http://digestingduck.blogspot.com.au/2010/03/simple-stupid-funnel-algorithm.html
int NavMesh::stringPull(const Vector2* portals, int portalCount,
	Vector2* points, const int maxPoints) {

	// Find straight path
	int npts = 0;

	// Init scan state
	Vector2 portalApex, portalLeft, portalRight;
	int apexIndex = 0, leftIndex = 0, rightIndex = 0;
	portalApex = portals[0];
	portalLeft = portals[0];
	portalRight = portals[1];

	// Add start point
	points[npts] = portalApex;
	npts++;

	for (int i = 1; i < portalCount && npts < maxPoints; ++i)
	{
		Vector2 left = portals[i * 2 + 0];
		Vector2 right = portals[i * 2 + 1];

		// Update right vertex
		if (triarea2(portalApex, portalRight, right) <= 0.0f)
		{
			if (vequal(portalApex, portalRight) || triarea2(portalApex, portalLeft, right) > 0.0f)
			{
				// Tighten the funnel
				portalRight = right;
				rightIndex = i;
			}
			else
			{
				// Right over left, insert left to path and restart scan from portal left point
				points[npts] = portalLeft;
				npts++;

				// Make current left the new apex
				portalApex = portalLeft;
				apexIndex = leftIndex;

				// Reset portal
				portalLeft = portalApex;
				portalRight = portalApex;
				leftIndex = apexIndex;
				rightIndex = apexIndex;

				// Restart scan
				i = apexIndex;
				continue;
			}
		}

		// Update left vertex
		if (triarea2(portalApex, portalLeft, left) >= 0.0f)
		{
			if (vequal(portalApex, portalLeft) || triarea2(portalApex, portalRight, left) < 0.0f)
			{
				// Tighten the funnel
				portalLeft = left;
				leftIndex = i;
			}
			else
			{
				// Left over right, insert right to path and restart scan from portal right point
				points[npts] = portalRight;
				npts++;

				// Make current right the new apex
				portalApex = portalRight;
				apexIndex = rightIndex;

				// Reset portal
				portalLeft = portalApex;
				portalRight = portalApex;
				leftIndex = apexIndex;
				rightIndex = apexIndex;

				// Restart scan
				i = apexIndex;
				continue;
			}
		}
	}

	// Append last point to path
	if (npts < maxPoints)
	{
		points[npts] = portals[(portalCount - 1) * 2 + 0];
		npts++;
	}

	return npts;
}