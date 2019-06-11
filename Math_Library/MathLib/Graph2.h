#pragma once
#include "Node2.h"

// a collection of coordinates
typedef std::vector<Node2*> Path;

class Graph2
{
public:
	Graph2();
	// removes all nodes from the graph
	~Graph2();

	// adds a node to the graph
	void addNode(Vector2 pos, std::vector<Vector2> links = { NULL }, std::vector<float> weight = { NULL });
	// adds an edge to a node
	void addEdge(Vector2 pos, std::vector<Vector2> links = { NULL }, std::vector<float> weight = { NULL });

	// removes a node from the graph
	void removeNode(Vector2 pos);
	// removes an edge from a node
	void removeEdge(Vector2 pos, std::vector<Vector2> links = { NULL });

	// checks if a node is in the graph
	bool search(Vector2 pos);
	// returns the node requested
	Node2* find(Vector2 pos);
	// uses Dijkstra's algorithm to find the shortest path between two nodes
	Path dijkstrasSearch(Vector2 start, Vector2 end);
	// uses the A*  method to find the shortest path between two node
	Path aStarSearch(Vector2 start, Vector2 end);

	// allows access to nodes by index in the vector
	Vector2& operator [] (const int& index);
	// prints the properties of all nodes in the graph
	void print();

	// checks if the graph is empty
	bool empty();
	// removes all nodes from the graph
	void clear();

private:
	// a collection of nodes
	std::vector<Node2*> m_nodes;
};