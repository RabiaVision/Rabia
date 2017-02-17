// Graph.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include<vector>
#include<list>

class Graph
{
private:
	int NbVertexes;
	std::vector<std::list<int>> AdjList;

public: 
	Graph(int V) :NbVertexes(V) { AdjList.resize(NbVertexes); }

	void AddVertex(int Node);
	void AddEdge(int Src, int Dst);

	void DetectCycles();
	void RemoveEdge(int node1, int node2);

};

void Graph::AddVertex(int Node)
{
	AdjList[Node].push_back(Node);
}

void Graph::AddEdge(int Src, int Dst)
{
	AdjList[Src].push_back(Dst);

	//Undirected graph.
	AdjList[Dst].push_back(Src);
}

void Graph::RemoveEdge(int node1, int node2)
{
	AdjList[node1].remove(node2);
}

void Graph::DetectCycles()
{
	int root = 0;
	int NbVisited = 0;
	int index = 0;
	std::vector<bool> visited(NbVertexes, false);
	std::vector<int> Source(NbVertexes, -1);
	std::list<int>   Queue;


	while (NbVisited < NbVertexes) // ==> this to be sure that we visited 
								   // all our graph (case of disconnected gpragh)
	{
		//Get the first element not visited.
		root = (std::find(visited.begin(), visited.end(), false) - visited.begin());
		std::vector<std::pair<int, int>> EdgesToRemove;

		// initialize the Queue by putting the value of root.
		// update the visited value of the root and increment Nbvisited
		Queue.push_back(root);
		Source[root]  = -1;
		visited[root] = 1;
		NbVisited++;

		while (!Queue.empty())
		{
			
			// Get the front of the Queue.
			int node = Queue.front();
			Queue.pop_front();

			//Go through the adjacent list of node, Add them to the Queue.
			// tag them as visited, and tag their source.
			for (auto Elem : AdjList[node])
			{
				// if the source node is Elem, we ignore
				if (Source[node] == Elem)
					continue;

				// If Elem is visited, and has already a source, that means that
				// he has more than one source, which results in a cycle.
				if (visited[Elem])
				{
					//Here we have a cycle!!!
					EdgesToRemove.emplace_back(Elem, node);
				}
				else
				{
					visited[Elem] = true;
					Source[Elem] = node;
					Queue.push_back(Elem);
					++NbVisited;
				}
			}
		}

		// Call the function of removing edges.
		for (auto Edge : EdgesToRemove)
		{
			RemoveEdge(Edge.first, Edge.second);
		}
	}
	

	
}

int main()
{
	Graph myGraph(13);

    // Since our labels are ordered integers,
	// we dont need to add the vertices. 
	// they can be represented by the indices of the vector of 
	// adjacency list.

	// Here we define the different edges.
	myGraph.AddEdge(1, 2);
	myGraph.AddEdge(1, 3);

	myGraph.AddEdge(2, 4);
	myGraph.AddEdge(2, 5);
	myGraph.AddEdge(2, 6);

	myGraph.AddEdge(3, 6);

	myGraph.AddEdge(5, 6);
	myGraph.AddEdge(5, 7);

	myGraph.AddEdge(7, 8);

	myGraph.AddEdge(9, 10);
	myGraph.AddEdge(9, 12);
	myGraph.AddEdge(10, 11);
	myGraph.AddEdge(11, 12);


	// Detect and remove Cycles.
	myGraph.DetectCycles();

    return 0;
}

