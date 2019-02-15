// ------------------------------------------------ graphl.cpp -------------------------------------------------------
// Sean O'Dell, CSS 502A
// Creation Date: 02/04/2019
// Date of Last Modification: 2/17/2019
// --------------------------------------------------------------------------------------------------------------------
// Purpose - Data structure implementation of a graph to do depth first search using an adjacency list implementation
// --------------------------------------------------------------------------------------------------------------------
// Allows for the creation of graph given a formatted text file.  Functionality includes depth first search, and
// displaying
// --------------------------------------------------------------------------------------------------------------------

#include "graphl.h"

// ------------------------------------GraphL-----------------------------------------------
// Description: constructor for GraphL
// ---------------------------------------------------------------------------------------------------
GraphL::GraphL()
{
	for (int nodeNumber = 0; nodeNumber < arraySizeInitialization; nodeNumber++)
	{
		this->C[nodeNumber].visited = false;
		this->C[nodeNumber].data = nullptr;
		this->C[nodeNumber].edgeHead = nullptr;
	}
	this->size = 0;
}

// ------------------------------------~GraphL-----------------------------------------------
// Description: destructor for GraphL
// ---------------------------------------------------------------------------------------------------
GraphL::~GraphL()
{
	delete C[0].data;
	C[0].data = nullptr;
	for (int nodeNumber = 1; nodeNumber <= this->size; nodeNumber++)
	{

		EdgeNode* currentEdge = C[nodeNumber].edgeHead;
		while (currentEdge != nullptr)
		{
			EdgeNode* next = currentEdge->nextEdge;
			delete currentEdge;
			currentEdge = next;

		}
		currentEdge = nullptr;
		C[nodeNumber].edgeHead = nullptr;

		if (C[nodeNumber].data != nullptr)
		{
			delete C[nodeNumber].data;
			C[nodeNumber].data = nullptr;
		}
	}
}

// ------------------------------------buildGraph-----------------------------------------------
// Description: builds graph given a formatted input text file.  Creates graph using adjacency
// list implementation
// ---------------------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream& fileStream)
{
	std::string line;
	std::getline(fileStream, line);
	std::istringstream iss(line);
	int declaredSize = 0;
	iss >> declaredSize;
	if (declaredSize <= 0)
	{
		return;
	} else
	{
		this->size = declaredSize;
	}
	for (int i = 1; i <= this->size; i++)
	{
		this->C[i].data = new NodeData();
		std::getline(fileStream, line);
		std::istringstream issNames(line);
		this->C[i].data->setData(issNames);
	}
	while (true)
	{
		std::getline(fileStream, line);
		std::istringstream issEdges(line);
		int from;
		int to;
		issEdges >> from;
		if (from == 0)
		{
			break;
		}
		issEdges >> to;
		this->insertEdge(from, to);
	}
}

// ------------------------------------displayGraph-----------------------------------------------
// Description: displays the graph
// ---------------------------------------------------------------------------------------------------
void GraphL::displayGraph()
{
	std::cout << "Graph:" << std::endl;
	for (int nodeNumber = 1; nodeNumber <= this->size; nodeNumber++)
	{
		std::cout << "Node" << std::setw(10) << std::left << nodeNumber << *C[nodeNumber].data << std::endl;
		if (C[nodeNumber].edgeHead != nullptr)
		{
			EdgeNode* currentEdgeNode = C[nodeNumber].edgeHead;
			while (currentEdgeNode != nullptr)
			{
				std::cout << "  " << "edge  " << nodeNumber << " " << currentEdgeNode->adjGraphNode << std::endl;
				currentEdgeNode = currentEdgeNode->nextEdge;
			}
		}
	}
	std::cout << std::endl;
}

// ------------------------------------depthFirstSearch-----------------------------------------------
// Description: finds and displays depth first ordering
// ---------------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
	resetVisited();
	std::cout << "Depth-first ordering:";
	for (int i = 1; i <= this->size; i++)
	{
		if (!C[i].visited)
		{
			dfs(i);
		}
	}
	std::cout << std::endl << std::endl;
}

// ------------------------------------breadthFirstSearch-----------------------------------------------
// Description: finds and displays breadth first ordering (NOT REQUIRED FOR CLASS PROJECT)
// ---------------------------------------------------------------------------------------------------
//void GraphL::breadthFirstSearch()
//{
//	queue<GraphNode> traversalQueue;
//	traversalQueue.push(C[1]);
//	C[1].visited = true;
//	std::cout << "Breadth-first ordering: " << 1;
//	while (!traversalQueue.empty())
//	{
//		GraphNode currentGNode = traversalQueue.front();
//		traversalQueue.pop();
//		EdgeNode* nextAdjacent = currentGNode.edgeHead;
//		while (nextAdjacent != nullptr)
//		{
//			if (!C[nextAdjacent->adjGraphNode].visited)
//			{
//				C[nextAdjacent->adjGraphNode].visited = true;
//				traversalQueue.push(C[nextAdjacent->adjGraphNode]);
//				std::cout << " " << nextAdjacent->adjGraphNode;
//			}
//			nextAdjacent = nextAdjacent->nextEdge;
//		}
//
//	}
//	std::cout << endl;
//}

// ------------------------------------insertEdge-----------------------------------------------
// Description: inserts edge into the graph
// ---------------------------------------------------------------------------------------------------
void GraphL::insertEdge(int from, int to)
{
	EdgeNode* newEdge = new EdgeNode();
	newEdge->adjGraphNode = to;
	if (C[from].edgeHead != nullptr)
	{
		newEdge->nextEdge = C[from].edgeHead;
		C[from].edgeHead = newEdge;
	} else
	{
		newEdge->nextEdge = nullptr;
		C[from].edgeHead = newEdge;

	}
}

// ------------------------------------dfs-----------------------------------------------
// Description: recursive call to allow for depth first searching
// ---------------------------------------------------------------------------------------------------
void GraphL::dfs(int nodeNumber)
{
	C[nodeNumber].visited = true;
	std::cout << " " << nodeNumber;
	if (C[nodeNumber].edgeHead != nullptr)
	{
		EdgeNode* currentEdge = C[nodeNumber].edgeHead;
		while (currentEdge != nullptr)
		{
			if (!C[currentEdge->adjGraphNode].visited)
			{
				dfs(currentEdge->adjGraphNode);
			}
			if (currentEdge != nullptr)
			{
				currentEdge = currentEdge->nextEdge;
			}
		}
	}
}

// ------------------------------------resetVisited-----------------------------------------------
// Description: resets all visited booleans to false
// ---------------------------------------------------------------------------------------------------
void GraphL::resetVisited()
{
	for (int nodeNumber = 1; nodeNumber <= this->size; nodeNumber++)
	{
		this->C[nodeNumber].visited = false;
	}
}