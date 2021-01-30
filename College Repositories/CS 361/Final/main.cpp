#include <iostream>
#include <list>
#include <queue>
using namespace std;


//Does a preorder search of the minimum spanning tree using the parent array
//Takes the starting node, the parent array for the start of each edge, and the total amount of vertices
//Assumes that the rows in the tree go with the lowest node values on the left to the greatest on the right
void preorder(int startNode, vector<int> parent, int vertexAmount)
{
    //uses the pattern
    //node, left, right

    //prints the value of the current node
    printf("%d, ", startNode);
    //goes through the parent array from the beginning to end
    for (int i = 0; i < vertexAmount; i++)
    {

        //checks if the current vertex is the start of an edge in the parent array
        if(parent[i] == startNode)
        {
            //if the current node is a start node for and edge it will run the preorder search on the end of the edge
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


typedef pair<int, int> iPair;

// This class represents a directed graph using
// adjacency list representation
class Graph
{
    int V; //# of verticies

    // In a weighted graph, we need to store vertex
    // and weight pair for every edge
    list<pair<int, int> > *adj;

public:
    Graph(int V);  // Constructor

    // function to add an edge to graph; u is starting node; v is other node; w is weight
    void addEdge(int u, int v, int w);

    // Print MST using Prim's algorithm
    Graph primMST();
};

// Allocates memory for adjacency list
Graph::Graph(int V)
{
    this->V = V;
    adj = new list<iPair> [V];
}

void Graph::addEdge(int u, int v, int w)
{
    adj[u].push_back(make_pair(v, w)); //creates a pair with weight coming second
    adj[v].push_back(make_pair(u, w));
}

// Prints shortest paths from src to all other vertices
Graph Graph::primMST()
{
    // Create a priority queue to store vertices that
    // are being preinMST
    priority_queue<iPair> pq;

    int src = 0; // Taking vertex 0 as source

    // Create a vector for keys and initialize all
    // keys as infinite (INF)
    vector<int> key(V, INT_MAX);

    // To store parent array which in turn store MST
    vector<int> parent(V, -1);

    // To keep track of vertices included in MST. Begins as all false
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
    for (int i = 1; i < V; ++i){
        printf("%d - %d\n", parent[i], i);
    }

    //finds the Hamiltonian cycle of the minimum spanning tree
    hamiltonianCycle(src, parent, V);
//    return final;
}


int main()
{
    int V = 4;
        vector<iPair > adj[4];
        Graph test(V);
        test.addEdge(0, 1, 10);
        test.addEdge(0, 2, 15);
        test.addEdge(0, 3, 20);
        test.addEdge(1, 2, 35);
        test.addEdge(1, 3, 25);
        test.addEdge(2, 3, 30);

         test.primMST();

       // Graph final(V);
        // making above shown graph
//        test.addEdge(0, 1, 4);
//        test.addEdge(0, 2, 6);
//        test.addEdge(0, 3, 3);
//        test.addEdge(0, 4, 5);
//        test.addEdge(1, 2, 12);
//        test.addEdge(1, 3, 10);
//        test.addEdge(1, 4, 8);
//        test.addEdge(2, 3, 9);
//        test.addEdge(2, 4, 2);
//        test.addEdge(3, 4, 8);



        //final =


        return 0;
}
