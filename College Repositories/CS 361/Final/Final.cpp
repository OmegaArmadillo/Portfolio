#include <iostream>
#include <vector>


using namespace std;


//Does a preorder search of the minimum spanning tree using the parent array
//Takes the starting node, the parent array for the start of each edge, and the total amount of vertices
void preorder(int startNode, vector<int> parent, int vertexAmount)
{
    //uses the pattern
    //node, left, right

    //prints the value of the current node
    printf("%d, ", startNode);

    //goes through the parent array from the end to the beginning
    for (int i = vertexAmount - 1; i > 0 ; i--)
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


int main()
{

int vertexAmount = 5;

vector<int> parent{6,0,1,0,1};

hamiltonianCycle(0,parent,vertexAmount);


}
