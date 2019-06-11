#pragma once
#include "Node3.h"

class Graph3
{
public:
	Graph3();
	// removes all nodes from the graph
	~Graph3();

	// adds a node to the graph
	void addNode(Vector3 pos, std::vector<Vector3> links = { NULL }, std::vector<float> weight = { NULL });
	// adds an edge to a node
	void addEdge(Vector3 pos, std::vector<Vector3> links = { NULL }, std::vector<float> weight = { NULL });

	// removes a node from the graph
	void removeNode(Vector3 pos);
	// removes an edge from a node
	void removeEdge(Vector3 pos, std::vector<Vector3> links = { NULL });

	// checks if a node is in the graph
	bool search(Vector3 pos);
	// returns the node requested
	Node3* find(Vector3 pos);
	// checks if the graph is empty
	bool empty();
	// removes all nodes from the graph
	void clear();

private:
	// a collection of nodes
	std::vector<Node3*> m_nodes;
};