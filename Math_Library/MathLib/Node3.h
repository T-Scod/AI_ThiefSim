#pragma once
#include "Vector3.h"
#include <vector>

// a position that can be traversed to and from
struct Node3
{
	// a connection between two nodes
	struct Edge3
	{
		// the node that is being connected to
		Node3 * target;
		// the weight of the edge
		float cost;
	};

	// the position of the node
	Vector3 position;
	// the total cost from the start node in a search to the current node
	float gScore;
	// the node that lead to this node
	Node3* parent;
	// a collection of edges to the nodes it connects to
	std::vector<Edge3> connections;
};