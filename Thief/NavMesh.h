#pragma once
#include <Vector2.h>
#include <vector>
#include <list>
#include <Node2.h>
#include "GameObject.h"

// an optimised node for nav meshes
class Node : public Node2
{
public:
	Node() {}
	virtual ~Node() {}

	// edges
	std::vector<Vector2> vertices;

	// finds any vertices that are shared with the other node
	int getAdjacentVertices(Node* other, Vector2* adjacent)
	{
		int count = 0;
		for (auto v : vertices)
		{
			for (auto v2 : other->vertices)
			{
				if (v.x == v2.x && v.y == v2.y)
				{
					adjacent[count++] = v;
					break;
				}
			}
		}
		return count;
	}
};

// forward declaring some Poly2Tri objects
namespace p2t {
	class CDT;
	struct Point;
}

class NavMesh {
public:

	// creates the base walkable area
	NavMesh(float width, float height);
	~NavMesh();

	// a square that has padding space from all the edges
	struct Obstacle {
		float x, y, w, h, padding;
	};

	// returns true if the obstacle was added safely (does not overlap)
	bool addObstacle(float x, float y, float width, float height, float padding);

	// triangulates the walkable area and builds the nav mesh nodes
	void build();

	// given a list of pathfinding nodes from a pathfinding search, this smooths the path using a funneling algorithm
	// funneling algorithm from (http://digestingduck.blogspot.com.au/2010/03/simple-stupid-funnel-algorithm.html)
	static int smoothPath(const std::list<Node*>& path, std::list<Vector2>& smoothPath);

	// returns the amount of nodes in the nav mesh
	unsigned int getNodeCount() const { return (unsigned int)m_nodes.size(); }
	// returns the container of nodes
	const std::vector<Node*>& getNodes() const { return m_nodes; }

	// access random node
	Node* getRandomNode() const;
	// closest node to the coordinate
	Node* findClosest(float x, float y) const;

	// returns the amount of obstacle
	unsigned int getObstacleCount() const { return (unsigned int)m_obstacles.size(); }
	// returns the container of obstacle
	const std::vector<Obstacle>& getObstacles() const { return m_obstacles; }

	// custom A* function for nav mesh
	std::list<Node*> aStar(Node* start, Node* end);

protected:

	// funneling algorithm from (http://digestingduck.blogspot.com.au/2010/03/simple-stupid-funnel-algorithm.html)
	inline static float triarea2(const Vector2& a, const Vector2& b, const Vector2& c)
	{
		const float ax = b.x - a.x;
		const float ay = b.y - a.y;
		const float bx = c.x - a.x;
		const float by = c.y - a.y;
		return bx*ay - ax*by;
	}
	inline static float vdistsqr(const Vector2& a, const Vector2& b)
	{
		float dx = a.x - b.x;
		float dy = a.y - b.y;
		return (dx*dx) + (dy*dy);
	}
	inline static bool vequal(const Vector2& a, const Vector2& b)
	{
		static const float eq = 0.001f*0.001f;
		return vdistsqr(a, b) < eq;
	}
	static int stringPull(const Vector2* portals, int portalCount, Vector2* points, const int maxPoints);

	// stores obstacles
	std::vector<Obstacle> m_obstacles;
	// stores nav mesh nodes
	std::vector<Node*> m_nodes;

	// this is used for building the mesh
	// uses Poly2Tri (https://github.com/greenm01/poly2tri)
	p2t::CDT* m_cdt;
	std::vector<std::vector<p2t::Point*>> m_polygons;
};