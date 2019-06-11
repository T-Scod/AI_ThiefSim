#pragma once
#include "Vector2.h"
#include <vector>

// a position that can be traversed to and from
class Node2
{
public:
	Node2() {}
	Node2(Vector2 pos) : position(pos) {}
	~Node2()
	{
		for (auto edge : connections)
		{
			delete edge;
		}
		parent = nullptr;
	}

	// a connection between two nodes
	struct Edge2
	{
		Edge2() {}
		Edge2(Node2* t, float c) : target(t), cost(c) {}
		~Edge2()
		{
			target = nullptr;
		}

		// the node that is being connected to
		Node2 * target;
		// the weight of the edge
		float cost;
	};

	// the position of the node
	Vector2 position;
	// the total cost from the start node in a search to the current node
	float gScore;
	// the heuristic score is an estimate used to determine the shortest route faster
	float hScore;
	// the final score is the sum of the g score and the heuristic
	float fScore;
	// the node that lead to this node
	Node2* parent;
	// a collection of edges to the nodes it connects to
	std::vector<Edge2*> connections;
};