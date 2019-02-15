// ------------------------------------------------ graphm.h -------------------------------------------------------
// Sean O'Dell, CSS 502A
// Creation Date: 02/04/2019
// Date of Last Modification: 2/17/2019
// --------------------------------------------------------------------------------------------------------------------
// Purpose - Data structure implementation of a graph to find shortest path using adjacency matrix
// --------------------------------------------------------------------------------------------------------------------
// Allows for the creation of graph given a formatted text file.  Functionality includes finding shortest path and
// displaying.
// --------------------------------------------------------------------------------------------------------------------

#ifndef GRAPHM_H
#define GRAPHM_H
#include "nodedata.h"
#include <climits>
#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
#include <stack>
#include <vector>
#include <iterator>

class GraphM
{

public:

	// ------------------------------------GraphM-----------------------------------------------
	// Description: constructor for GraphM
	// ---------------------------------------------------------------------------------------------------
	GraphM();

	// ------------------------------------buildGraph-----------------------------------------------
	// Description: builds graph given a formatted input text file.  Creates graph using adjacency
	// matrix implementation
	// ---------------------------------------------------------------------------------------------------
	void buildGraph(ifstream&);

	// ------------------------------------insertEdge-----------------------------------------------
	// Description: inserts edge into graph between two given nodes
	// ---------------------------------------------------------------------------------------------------
	void insertEdge(int, int, int);

	// ------------------------------------removeEdge-----------------------------------------------
	// Description: removes edge from graph between two given nodes
	// ---------------------------------------------------------------------------------------------------
	void removeEdge(int, int);

	// ------------------------------------findShortestPath-----------------------------------------------
	// Description: finds the shortest path between every node to every other node in the graph
	// ---------------------------------------------------------------------------------------------------
	void findShortestPath();

	// ------------------------------------displayAll-----------------------------------------------
	// Description: shows that the findShortestPath algorithm worked correctly by printing results to the
	// console
	// ---------------------------------------------------------------------------------------------------
	void displayAll();

	// ------------------------------------display-----------------------------------------------
	// Description: displays shortest distance with path info from one node to another
	// ---------------------------------------------------------------------------------------------------
	void display(int, int);

private:

	static constexpr int MAXNODES = 100;
	static constexpr int arraySizeInitialization = MAXNODES + 1;

	struct TableType
	{
		bool visited;          // whether node has been visited
		int dist;              // shortest distance from source known so far
		int path;              // previous node in path of min dist
	};

	NodeData data[arraySizeInitialization];								// data for graph nodes 
	int C[arraySizeInitialization][arraySizeInitialization];            // Cost array, the adjacency matrix
	int size;															// number of nodes in the graph
	TableType T[arraySizeInitialization][arraySizeInitialization];      // stores visited, distance, path

	// utility functions

	// ------------------------------------getMinV-----------------------------------------------
	// Description: gets vertex with the minimum distance from the origin node
	// ---------------------------------------------------------------------------------------------------
	int getMinV(int);

	// ------------------------------------getPath-----------------------------------------------
	// Description: gets the shortest path from one node to another
	// ---------------------------------------------------------------------------------------------------
	vector<int> getPath(int, int);

	// ------------------------------------displayShortestPathDistance-----------------------------------------------
	// Description: displays the shortest path distance from one node to another
	// ---------------------------------------------------------------------------------------------------
	void displayShortestPathDistance(int, int);

};
#endif