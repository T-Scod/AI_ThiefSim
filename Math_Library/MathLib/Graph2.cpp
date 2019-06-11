#include "Graph2.h"
#include <iostream>
#include "Queue.h"
#include <math.h>

Graph2::Graph2()
{
}
// removes all nodes from the graph
Graph2::~Graph2()
{
	// iterates through all elements in the vector
	for (auto node : m_nodes)
	{
		// deletes the node
		delete node;
		node = nullptr;
	}
	// removes all nodes from the graph
	m_nodes.clear();
}

// adds a node to the graph
void Graph2::addNode(Vector2 pos, std::vector<Vector2> links, std::vector<float> weight)
{
	// checks if the value is already in the graph
	if (search(pos) == true)
	{
		// exits the function without adding the node
		return;
	}

	// creates a new node
	Node2* node = new Node2();
	// sets the nodes position to the specified one
	node->position = pos;
	// sets its parent to null pointer
	node->parent = nullptr;
	// sets the scores to 0
	node->gScore = 0.0f;
	node->hScore = 0.0f;
	node->fScore = 0.0f;
	
	// checks if there are edges to add
	if (!links.empty())
	{
		// if the amount of weights is less than the amount of links then fill in the empty spots with 0
		while (weight.size() < links.size())
		{
			weight.push_back(0.0f);
		}

		// iterates through the amount of links
		for (unsigned int i = 0; i < links.size(); i++)
		{
			// iterates through the nodes
			for (auto n : m_nodes)
			{
				// if the link is to an existing node then add the edge and weight
				if (links[i] == n->position)
				{
					// adds an edge
					node->connections.push_back(new Node2::Edge2());
					// sets the target to the matching node
					node->connections.back()->target = n;
					// sets the cost of the edge to the matching weight
					node->connections.back()->cost = weight[i];
					// exits the iteration of the nodes
					break;
				}
			}
		}
	}

	// adds the node to the graph
	m_nodes.push_back(node);
}
// adds an edge to a node
void Graph2::addEdge(Vector2 pos, std::vector<Vector2> links, std::vector<float> weight)
{
	// finds the node
	Node2* node = find(pos);

	// checks if the node is in the graph
	if (node == nullptr)
	{
		// exits the function without adding edges
		return;
	}

	// checks if there are edges to add
	if (!links.empty())
	{
		// if the amount of weights is less than the amount of links then fill in the empty spots with 0
		while (weight.size() < links.size())
		{
			weight.push_back(0.0f);
		}

		// iterates through the amount of links
		for (unsigned int i = 0; i < links.size(); i++)
		{
			// iterates through the nodes
			for (auto n : m_nodes)
			{
				// if the link is to an existing node then add the edge and weight
				if (links[i] == n->position)
				{
					// checks if there are any edges before checking if they are the same
					if (!node->connections.empty())
					{
						// checks if the edge to the node already exists
						for (auto edge : node->connections)
						{
							if (edge->target == n)
							{
								// changes the weight of the edge
								edge->cost = weight[i];
								break;
							}
							// if the edge does not already exist then add it
							else if (edge->target == node->connections.back()->target)
							{
								// adds an edge
								node->connections.push_back(new Node2::Edge2());
								// sets the target to the matching node
								node->connections.back()->target = n;
								// sets the cost of the edge to the matching weight
								node->connections.back()->cost = weight[i];
							}
						}
						// exits the iteration of the nodes
						break;
					}
					else
					{
						// adds an edge
						node->connections.push_back(new Node2::Edge2());
						// sets the target to the matching node
						node->connections.back()->target = n;
						// sets the cost of the edge to the matching weight
						node->connections.back()->cost = weight[i];
						// exits the iteration of the nodes
						break;
					}
				}
			}
		}
	}
}

// removes a node from the graph
void Graph2::removeNode(Vector2 pos)
{
	// finds the node
	Node2* node = find(pos);

	// checks if the node is in the graph
	if (node == nullptr)
	{
		// exits the function without removing anything
		return;
	}

	// iterates through the graph to remove all connections to the node
	for (auto n : m_nodes)
	{
		// checks if the current node has any edges
		if (n->connections.empty())
		{
			// continues onto the next node if there are no edges
			continue;
		}
		// iterates through all of the edges
		for (auto edge : n->connections)
		{
			// checks if the edge is connected to the node
			if (edge->target == n)
			{
				// overlaps the edge with the last edge in the collection
				edge = n->connections.back();
				// removes the last edge from the collection as it is either a double up or the edge to be removed
				n->connections.pop_back();
				break;
			}
		}
	}

	// deletes the node
	node = nullptr;
	delete node;

	// overlaps the empty space with the back node
	node = m_nodes.back();
	// removes the last node from the collection as it is either a double up or the node to be removed
	m_nodes.pop_back();
}
// removes an edge from a node
void Graph2::removeEdge(Vector2 pos, std::vector<Vector2> links)
{
	// finds the node
	Node2* node = find(pos);

	// checks if the node is in the graph
	if (node == nullptr)
	{
		// exits the function without removing anything
		return;
	}

	// iterates through the graph to remove all connections to the node
	for (auto n : m_nodes)
	{
		// checks if the current node has any edges
		if (n->connections.empty())
		{
			// continues onto the next node if there are no edges
			continue;
		}
		// iterates through all of the edges
		for (auto edge : n->connections)
		{
			// checks if the edge is connected to the node
			if (edge->target == n)
			{
				// overlaps the edge with the last edge in the collection
				edge = n->connections.back();
				// removes the last edge from the collection as it is either a double up or the edge to be removed
				n->connections.pop_back();
				break;
			}
		}
	}
}

// checks if a node is in the graph
bool Graph2::search(Vector2 pos)
{
	// iterates through the graph to find the node
	for (auto node : m_nodes)
	{
		// if the position is found then return true
		if (pos == node->position)
		{
			return true;
		}
	}
	// if the node is not found then return false
	return false;
}
// returns the node requested
Node2* Graph2::find(Vector2 pos)
{
	// iterates through the graph to find the node
	for (auto node : m_nodes)
	{
		// if the position is found then return the node
		if (pos == node->position)
		{
			return node;
		}
	}
	// if the node is not found then return a null pointer
	return nullptr;
}
// uses Dijkstra's algorithm to find the shortest path between two nodes
Path Graph2::dijkstrasSearch(Vector2 start, Vector2 end)
{
	// contains the untraversed nodes
	Queue<Node2*> priorityQueue;
	// contains the traversed nodes
	Queue<Node2*> traversedQueue;

	// sets all the nodes g scores to infinity
	// allows for checking for occurance of processes
	for (auto node : m_nodes)
	{
		node->gScore = INFINITY;
	}

	// sets the end node to the corresponding node
	Node2* endNode = find(end);
	// sets the start node to the corresponding node
	Node2* startNode = find(start);
	// sets the start node's parent to itself
	startNode->parent = nullptr;
	// sets the start node's g score to 0
	startNode->gScore = 0.0f;
	// adds the start node to the priority queue
	priorityQueue.push(startNode);

	// a pointer to the node being inspected
	Node2* currentNode = new Node2();

	//iterates while there are still untraversed nodes
	while (!priorityQueue.empty())
	{
		// sorts the priority nodes by lowest to highest g score using bubble sort
		for (unsigned int i = 0; i < priorityQueue.size(); i++)
		{
			for (unsigned int j = 0; j < priorityQueue.size() - 1; j++)
			{
				// if the earlier node's g score is greater than the next node's g score then swap
				if (priorityQueue[j]->gScore > priorityQueue[j + 1]->gScore)
				{
					Node2* temp = priorityQueue[j];
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
		if (currentNode == endNode)
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
			if (!traversedQueue.search(edge->target))
			{
				// checks if the target already has a smaller g score, implying that there is a faster way to the target
				if (edge->target->gScore > currentNode->gScore + edge->cost)
				{
					// adds the next node into the priority queue
					priorityQueue.push(edge->target);
					// sets the target's g score to the total g score plus the cost required to reach the target
					edge->target->gScore = currentNode->gScore + edge->cost;
					// sets the target's parent to the node that it came from
					edge->target->parent = currentNode;
				}
			}
		}
	}

	// contains the path
	Path path;
	// sets the current node to the end node
	currentNode = endNode;
	// runs as long as the current node is not null
	while (currentNode != nullptr)
	{
		// adds the position of the node to the path
		path.push_back(currentNode);
		// sets the current node to its own parent
		currentNode = currentNode->parent;
	}

	// cleans up the assets
	priorityQueue.clear();
	traversedQueue.clear();
	currentNode = nullptr;
	delete currentNode;

	// returns the container of positions
	return path;
}
// uses the A*  method to find the shortest path between two node
Path Graph2::aStarSearch(Vector2 start, Vector2 end)
{
	// contains the untraversed nodes
	Queue<Node2*> priorityQueue;
	// contains the traversed nodes
	Queue<Node2*> traversedQueue;

	// sets all the nodes g scores to infinity
	// allows for checking for occurance of processes
	for (auto node : m_nodes)
	{
		node->gScore = INFINITY;
	}

	// sets the end node to the corresponding node
	Node2* endNode = find(end);
	// sets the start node to the corresponding node
	Node2* startNode = find(start);
	// sets the start node's parent to itself
	startNode->parent = nullptr;
	// sets the start node's g score to 0
	startNode->gScore = 0.0f;
	// adds the start node to the priority queue
	priorityQueue.push(startNode);

	// a pointer to the node being inspected
	Node2* currentNode = new Node2();

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
					Node2* temp = priorityQueue[j];
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
		if (currentNode == endNode)
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
			if (!traversedQueue.search(edge->target))
			{
				// checks if the target already has a smaller g score, implying that there is a faster way to the target
				if (edge->target->gScore > currentNode->gScore + edge->cost)
				{
					// adds the next node into the priority queue
					priorityQueue.push(edge->target);

					// sets the target's g score to the total g score plus the cost required to reach the target
					edge->target->gScore = currentNode->gScore + edge->cost;
					// sets the heuristic to the distance between the next node and the end node
					edge->target->hScore = edge->target->position.distanceSqr(endNode->position);
					// the final score is the sum of the scores
					edge->target->fScore = edge->target->gScore + edge->target->hScore;

					// sets the target's parent to the node that it came from
					edge->target->parent = currentNode;
				}
			}
		}
	}

	// contains the path
	Path path;
	// sets the current node to the end node
	currentNode = endNode;
	// runs as long as the current node is not null
	while (currentNode != nullptr)
	{
		// adds the position of the node to the path
		path.push_back(currentNode);
		// sets the current node to its own parent
		currentNode = currentNode->parent;
	}

	// cleans up the assets
	priorityQueue.clear();
	traversedQueue.clear();
	currentNode = nullptr;
	delete currentNode;

	// returns the container of positions
	return path;
}

// allows access to nodes by index in the vector
Vector2 & Graph2::operator[](const int & index)
{
	return m_nodes[index]->position;
}
// prints the properties of all nodes in the graph
void Graph2::print()
{
	// iterates through each node
	for (auto node : m_nodes)
	{
		// prints the position
		std::cout << "Position: " << node->position.x << ", " << node->position.y << ". ";
		// prints the connections
		std::cout << "Connections to: ";
		// checks if there are connections
		if (!node->connections.empty())
		{
			// iterates through all of the node's edges
			for (auto edge : node->connections)
			{
				// if it is the last edge then use a .
				if (edge->target == node->connections.back()->target)
				{
					// prints the edge position and weight
					std::cout << edge->target->position.x << ", " << edge->target->position.y << " with weight " << edge->cost << "." << std::endl;
				}
				// otherwise use a ,
				else
				{
					std::cout << edge->target->position.x << ", " << edge->target->position.y << " with weight " << edge->cost << ", ";
				}
			}
		}
		// if not then print no connections
		else
		{
			std::cout << "no connections." << std::endl;
		}
	}
}

// checks if the graph is empty
bool Graph2::empty()
{
	// if there are nodes in the graph then return true
	if (m_nodes.empty() == true)
	{
		return true;
	}
	// otherwise return false
	return false;
}
// removes all nodes from the graph
void Graph2::clear()
{
	// iterates through all elements in the vector
	for (auto node : m_nodes)
	{
		// deletes the node
		node = nullptr;
		delete node;
	}
	// removes all nodes from the graph
	m_nodes.clear();
}