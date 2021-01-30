#include <iostream>
#include <list>
#include <queue>
using namespace std;

typedef pair<int, int> iPair;



//Does a preorder search of the minimum spanning tree using the parent array
//Takes the starting node, the parent array for the start of each edge, and the total amount of vertices
//assumes that the rows in the tree go with the lowest node values on the left to the greatest on the right
void preorder(int startNode, vector<int> parent, int vertexAmount)
{
    //uses the pattern
    //node, left, right

    //prints the value of the current node
    printf("%d, ", startNode);

    //goes through the parent array from the beginning to end
    for (int i = 0; i < vertexAmount ; i++)
    {

        //checks if the current vertex is the start of an edge in the parent array
        if(parent[i] == startNode)
        {
            //if the current node is a start node for and edge it will run the pre-order search on the end of the edge
           preorder(i,parent,vertexAmount);
        }

    }



}


//creates a hamiltonian cycle for a minimum spanning tree
void hamiltonianCycle(int startNode, vector<int> parent, int vertexAmount)
{
    //does the preorder search to get everything except the end value
    preorder(startNode, parent, vertexAmount);

    //prints the start value which is the end of the cycle
    printf("%d", startNode);
}


// This class represents a directed graph using
// adjacency list representation
class Graph
{
    int V;    // No. of vertices

    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list<pair<int, int> > *adj;

public:
    Graph(int V);  // Constructor

    // function to add an edge to graph
    void addEdge(int u, int v, int w);

    // Print MST using Prim's algorithm
    void primMST();
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair> [V];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w));
    adj[v].push_back(make_pair(u, w));
}

// Prints shortest paths from src to all other vertices
void Graph::primMST()
{
    // Create a priority queue to store vertices that
    // are being preinMST. This is weird syntax in C++.
    // Refer below link for details of this syntax
    // http://geeksquiz.com/implement-min-heap-using-stl/
    priority_queue<iPair, vector <iPair> , greater<iPair> > pq;

    int src = 0; // Taking vertex 0 as source

    // Create a vector for keys and initialize all
    // keys as infinite (INF)
    vector<int> key(V, INT_MAX);

    // To store parent array which in turn store MST
    vector<int> parent(V, -1);

    // To keep track of vertices included in MST
    vector<bool> inMST(V, false);

    // Insert source itself in priority queue and initialize
    // its key as 0.
    pq.push(make_pair(0, src));
    key[src] = 0;

    /* Looping till priority queue becomes empty */
    while (!pq.empty())
    {
        // The first vertex in pair is the minimum key
        // vertex, extract it from priority queue.
        // vertex label is stored in second of pair (it
        // has to be done this way to keep the vertices
        // sorted key (key must be first item
        // in pair)
        int u = pq.top().second;
        pq.pop();

        inMST[u] = true;  // Include vertex in MST

        // 'i' is used to get all adjacent vertices of a vertex
        list< pair<int, int> >::iterator i;
        for (i = adj[u].begin(); i != adj[u].end(); ++i)
        {
            // Get vertex label and weight of current adjacent
            // of u.
            int v = (*i).first;
            int weight = (*i).second;

            //  If v is not in MST and weight of (u,v) is smaller
            // than current key of v
            if (inMST[v] == false && key[v] > weight)
            {
                // Updating key of v
                key[v] = weight;
                pq.push(make_pair(key[v], v));
                parent[v] = u;
            }
        }
    }

    // Print edges of MST using parent array
    for (int i = 1; i < V; ++i)
        printf("%d - %d\n", parent[i], i);


    //creates a Hamiltonian cycle for the minimum spanning tree
    hamiltonianCycle(src,parent,V);


}

int main()
{
/*
    int V = 9;
        vector<iPair > adj[9];
        Graph test(V);
        // making above shown graph
        test.addEdge(0, 1, 4);
        test.addEdge(0, 7, 8);
        test.addEdge(1, 2, 8);
        test.addEdge(1, 7, 11);
        test.addEdge(2, 3, 7);
        test.addEdge(2, 8, 2);
        test.addEdge(2, 5, 4);
        test.addEdge(3, 4, 9);
        test.addEdge(3, 5, 14);
        test.addEdge(4, 5, 10);
        test.addEdge(5, 6, 2);
        test.addEdge(6, 7, 1);
        test.addEdge(6, 8, 6);
        test.addEdge(7, 8, 7);

        test.primMST();
*/

    int V = 4;
        vector<iPair > adj[V];
        Graph test(V);
        // making above shown graph
        test.addEdge(0, 1, 10);
        test.addEdge(1, 2, 35);
        test.addEdge(1, 3, 25);
        test.addEdge(0, 3, 20);
        test.addEdge(0, 2, 15);
        test.addEdge(2, 3, 30);

        test.primMST();

/*
     int V = 5;
        vector<iPair > adj[5];
        Graph test(V);

        test.addEdge(0,1,)
*/


        return 0;
}
