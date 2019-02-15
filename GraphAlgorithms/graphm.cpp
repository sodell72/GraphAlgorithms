// ------------------------------------------------ graphm.cpp -------------------------------------------------------
// Sean O'Dell, CSS 502A
// Creation Date: 02/04/2019
// Date of Last Modification: 2/17/2019
// --------------------------------------------------------------------------------------------------------------------
// Purpose - Data structure implementation of a graph to find shortest path using adjacency matrix
// --------------------------------------------------------------------------------------------------------------------
// Allows for the creation of graph given a formatted text file.  Functionality includes finding shortest path and
// displaying.
// --------------------------------------------------------------------------------------------------------------------

#include "graphm.h"


// ------------------------------------GraphM-----------------------------------------------
// Description: constructor for GraphM
// ---------------------------------------------------------------------------------------------------
GraphM::GraphM()
{
	for (int source = 0; source < arraySizeInitialization; source++)
	{
		for (int destination = 0; destination < arraySizeInitialization; destination++)
		{
			this->C[source][destination] = -1;
			this->T[source][destination].visited = false;
			this->T[source][destination].dist = INT_MAX;
			this->T[source][destination].path = 0;
		}
	}
	this->size = 0;
}

// ------------------------------------buildGraph-----------------------------------------------
// Description: builds graph given a formatted input text file.  Creates graph using adjacency
// matrix implementation
// ---------------------------------------------------------------------------------------------------
void GraphM::buildGraph(ifstream& infile)
{         
	int declaredSize;
	infile >> declaredSize;
	if (declaredSize <= 0)
	{
		return;
	} else
	{
		this->size = declaredSize;
	}
	for (int i = 0; i <= this->size; i++)
	{
		this->data[i].setData(infile);
	}
	while (true)
	{
		int from, to, weight;
		infile >> from;
		infile >> to;
		infile >> weight;
		if (from == 0) break;
		this->insertEdge(from, to, weight);
	}

}

// ------------------------------------insertEdge-----------------------------------------------
// Description: inserts edge into graph between two given nodes
// ---------------------------------------------------------------------------------------------------
void GraphM::insertEdge(int from, int to, int weight)
{
	this->C[from][to] = weight;
}

// ------------------------------------removeEdge-----------------------------------------------
// Description: removes edge from graph between two given nodes
// ---------------------------------------------------------------------------------------------------
void GraphM::removeEdge(int from, int to)
{
	this->C[from][to] = -1;
}

// ------------------------------------findShortestPath-----------------------------------------------
// Description: finds the shortest path between every node to every other node in the graph
// ---------------------------------------------------------------------------------------------------
void GraphM::findShortestPath()
{
	// loop for each node as source
	for (int source = 1; source <= size; source++)
	{
		this->T[source][source].dist = 0;
		// finds shortest distance from source node to all other nodes
		for (int i = 1; i <= size; i++)
		{
			int minV = this->getMinV(source);
			T[source][minV].visited = true;
			for (int adjacent = 1; adjacent <= this->size; adjacent++)
			{
				int edgeValue = C[minV][adjacent];
				if (edgeValue != -1 && T[source][adjacent].visited != true)
				{
					if (T[source][adjacent].dist > T[source][minV].dist + edgeValue)
					{
						T[source][adjacent].path = minV;
					}
					T[source][adjacent].dist = min(T[source][adjacent].dist, T[source][minV].dist + edgeValue);
				}
			}

		}
	}

}

// ------------------------------------displayAll-----------------------------------------------
// Description: shows that the findShortestPath algorithm worked correctly by printing results to the
// console
// ---------------------------------------------------------------------------------------------------
void GraphM::displayAll()
{
	std::cout<< std::setw(25) << std::left << "Description";
	std::cout << std::setw(11) << "From node" << std::setw(11) << "To node" << std::setw(13) << "Dijkstra's" << std::setw(11) << "Path" << std::endl;
	for (int i = 1; i <= this->size; i++)
	{
		std::cout << std::setw(25) << std::left << this->data[i] << std::endl;
		for (int j = 1; j <= this->size; j++)
		{
			if (j == i) continue;
			std::cout << std::setw(25) << " " << std::setw(11) << std::left << i;
			std::cout << std::setw(11) << std::left << j;
			displayShortestPathDistance(i, j);
			vector<int> path = getPath(i, j);
			vector<int>::iterator it;
			for (it = path.begin(); it < path.end(); it++)
			{
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		}
	}
}

// ------------------------------------display-----------------------------------------------
// Description: displays shortest distance with path info from one node to another
// ---------------------------------------------------------------------------------------------------
void GraphM::display(int from, int to)
{
	std::cout << std::setw(11) << std::left << from << std::setw(11) << std::left << to;
	displayShortestPathDistance(from, to);
	vector<int> path = getPath(from, to);
	vector<int>::iterator it;
	for (it = path.begin(); it < path.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << endl;
	for (it = path.begin(); it < path.end(); it++)
	{
		std::cout << this->data[*it] << std::endl;
	}
	std::cout << endl;
}

// ------------------------------------getMinV-----------------------------------------------
// Description: gets vertex with the minimum distance from the origin node
// ---------------------------------------------------------------------------------------------------
int GraphM::getMinV(int source)
{
	int minV = 0;
	int minValue = INT_MAX;
	for (int i = 1; i <= this->size; i++)
	{
		TableType current = T[source][i];
		if (!current.visited)
		{
			if (T[source][i].dist < minValue)
			{
				minV = i;
				minValue = T[source][i].dist;
			}
		}
	}
	return minV;
}

// ------------------------------------getPath-----------------------------------------------
// Description: gets the shortest path from one node to another
// ---------------------------------------------------------------------------------------------------
vector<int> GraphM::getPath(int from, int to)
{
	vector<int> pathVector;
	if (T[from][to].dist == INT_MAX) return pathVector;
	int parent = to;
	stack<int> path;
	path.push(parent);
	while (parent != from)
	{
		parent = T[from][parent].path;
		path.push(parent);
	}
	while (!path.empty())
	{
		pathVector.push_back(path.top());
		path.pop();
	}
	return pathVector;
}

// ------------------------------------displayShortestPathDistance-----------------------------------------------
// Description: displays the shortest path distance from one node to another
// ---------------------------------------------------------------------------------------------------
void GraphM::displayShortestPathDistance(int from, int to)
{
	if (T[from][to].dist == INT_MAX)
	{
		std::cout << std::setw(13) << std::left << "----";
	} else
	{
		std::cout << std::setw(13) << std::left << T[from][to].dist;
	}
}