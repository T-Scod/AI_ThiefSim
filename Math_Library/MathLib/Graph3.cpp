#include "Graph3.h"

Graph3::Graph3()
{
}
// removes all nodes from the graph
Graph3::~Graph3()
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

// adds a node to the graph
void Graph3::addNode(Vector3 pos, std::vector<Vector3> links, std::vector<float> weight)
{
	// checks if the value is already in the graph
	if (search(pos) == true)
	{
		// exits the function without adding the node
		return;
	}

	// creates a new node
	Node3* node = new Node3();
	// sets the nodes position to the specified one
	node->position = pos;
	// sets its parent to null pointer
	node->parent = nullptr;
	// sets the g score to 0
	node->gScore = 0.0f;

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
					node->connections.push_back(Node3::Edge3());
					// sets the target to the matching node
					node->connections.back().target = n;
					// sets the cost of the edge to the matching weight
					node->connections.back().cost = weight[i];
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
void Graph3::addEdge(Vector3 pos, std::vector<Vector3> links, std::vector<float> weight)
{
	// finds the node
	Node3* node = find(pos);

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
					// checks if the edge to the node already exists
					for (auto edge : node->connections)
					{
						if (edge.target == n)
						{
							// changes the weight of the edge
							edge.cost = weight[i];
							break;
						}
						// if the edge does not already exist then add it
						else if (edge.target == node->connections.back().target)
						{
							// adds an edge
							node->connections.push_back(Node3::Edge3());
							// sets the target to the matching node
							node->connections.back().target = n;
							// sets the cost of the edge to the matching weight
							node->connections.back().cost = weight[i];
						}
					}
					// exits the iteration of the nodes
					break;
				}
			}
		}
	}
}

// removes a node from the graph
void Graph3::removeNode(Vector3 pos)
{
	// finds the node
	Node3* node = find(pos);

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
			if (edge.target == n)
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
void Graph3::removeEdge(Vector3 pos, std::vector<Vector3> links)
{
	// finds the node
	Node3* node = find(pos);

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
			if (edge.target == n)
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
bool Graph3::search(Vector3 pos)
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
Node3* Graph3::find(Vector3 pos)
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
// checks if the graph is empty
bool Graph3::empty()
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
void Graph3::clear()
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