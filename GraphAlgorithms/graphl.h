// ------------------------------------------------ graphl.h -------------------------------------------------------
// Sean O'Dell, CSS 502A
// Creation Date: 02/04/2019
// Date of Last Modification: 2/17/2019
// --------------------------------------------------------------------------------------------------------------------
// Purpose - Data structure implementation of a graph to do depth first search using an adjacency list implementation
// --------------------------------------------------------------------------------------------------------------------
// Allows for the creation of graph given a formatted text file.  Functionality includes depth first search, and
// displaying
// --------------------------------------------------------------------------------------------------------------------

#ifndef GRAPHl_H
#define GRAPHl_H
#include "nodedata.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <string>
#include <vector>
#include <sstream>

class GraphL
{

public:

	// ------------------------------------GraphL-----------------------------------------------
	// Description: constructor for GraphL
	// ---------------------------------------------------------------------------------------------------
	GraphL();

	// ------------------------------------~GraphL-----------------------------------------------
	// Description: destructor for GraphL
	// ---------------------------------------------------------------------------------------------------
	~GraphL();

	// ------------------------------------buildGraph-----------------------------------------------
	// Description: builds graph given a formatted input text file.  Creates graph using adjacency
	// list implementation
	// ---------------------------------------------------------------------------------------------------
	void buildGraph(ifstream& fileStream);

	// ------------------------------------displayGraph-----------------------------------------------
	// Description: displays the graph
	// ---------------------------------------------------------------------------------------------------
	void displayGraph();

	// ------------------------------------depthFirstSearch-----------------------------------------------
	// Description: finds and displays depth first ordering
	// ---------------------------------------------------------------------------------------------------
	void depthFirstSearch();

	// ------------------------------------breadthFirstSearch-----------------------------------------------
	// Description: finds and displays breadth first ordering (NOT REQUIRED FOR CLASS PROJECT)
	// ---------------------------------------------------------------------------------------------------
	//void breadthFirstSearch();
	
private:

	struct EdgeNode;      // forward reference for the compiler
	struct GraphNode
	{    // structs used for simplicity, use classes if desired
		EdgeNode* edgeHead; // head of the list of edges
		NodeData* data;     // data information about each node
		bool visited;
	};

	struct EdgeNode
	{
		int adjGraphNode;  // subscript of the adjacent graph node
		EdgeNode* nextEdge;
	};

	static constexpr int MAXNODES = 100;
	static constexpr int arraySizeInitialization = MAXNODES + 1;
	GraphNode C[arraySizeInitialization];
	int size;

	// ------------------------------------insertEdge-----------------------------------------------
	// Description: inserts edge into the graph
	// ---------------------------------------------------------------------------------------------------
	void insertEdge(int, int);

	// ------------------------------------dfs-----------------------------------------------
	// Description: recursive call to allow for depth first searching
	// ---------------------------------------------------------------------------------------------------
	void dfs(int);

	// ------------------------------------resetVisited-----------------------------------------------
	// Description: resets all visited booleans to false
	// ---------------------------------------------------------------------------------------------------
	void resetVisited();
};
#endif