#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <string>


using namespace std;


// getting char in a string
//http://www.cplusplus.com/reference/string/string/at/

//a function that takes dfa parameters and an input string to see if the input is valid
void dfaCheck (vector<string> states, string start, vector<string> acceptStates, vector<char> alphabet, vector<string> equation[], string input)
{
    //keeps track of whether the input is valid or not
    int validInput = 1;

    //keeps track of the current character being checked and position in the input being checked
    char currentInput;
    int inputPosition = 0;

    //keeps track of what state the dfa is in and its value in the state array
    string currentState = start;
    int statePosition = 0;


    //used in for loops
    int temp = 0;


    //used to check for an empty string
    if(input.length() == 0)
    {
        validInput = 0;
    }


    //done if the input string is not empty
    if(validInput == 1)
    {
        //goes through each char in the input
        for(int i = 0; i < input.size(); i++)
        {
            //gets the input value to be checked
            currentInput = input.at(i);

            //gets the input's position in the alphabet array
            for(temp = 0; temp < alphabet.size(); temp++)
            {
                if(alphabet[temp] == currentInput)
                {
                    inputPosition = temp;
                }
            }


            //gets the state's position in the states array
             for(temp = 0; temp < states.size(); temp++)
            {
                if(states[temp] == currentState)
                {
                    statePosition = temp;
                }
            }


            //calculates what the next state is by using the current state and the current input
            currentState = equation[statePosition][inputPosition];



        }
    }

    //assumes the input is incorrect to be checked later
    validInput = 0;

            //checks if the final state is an accept state and sets the string to be valid if it is
            for(temp = 0; temp < acceptStates.size(); temp++)
            {
                if(acceptStates[temp] == currentState)
                {
                    validInput = 1;
                }
            }


            //tells the user if the input is valid
            if(validInput == 1)
            {
                printf("input %s is valid\n", input.c_str());
            }
            else
            {
                printf("input %s is invalid\n", input.c_str());
            }


}






//function to use the bellman ford algorithm on a graph
void bellmanFord(vector<int> graph[], int vertexAmount, int edgeAmount, int startNode)
{
    //sets a value to be infinity in the function
    int infinity = 1000;

    //keeps track of the distance to each node
    int distance[vertexAmount];

    //keeps track of the predecessor of each node
    int predecessor[vertexAmount];

    //sets the distance to each node to be infinity and the predecessors to be null
    for(int i = 0; i < vertexAmount; i++)
    {
        distance[i] = infinity;

        predecessor[i] = -1;
    }

    //sets the distance to the start node to be 0
    distance[startNode] = 0;


    //checks each edge an amount of times equal to the amount of vertices - 1
    for( int checks = 0; checks < vertexAmount - 1; checks++)
    {
        //checks each edge in the graph
        for(int currentEdge = 0; currentEdge < edgeAmount; currentEdge++)
        {
            //checks of the current distance to the vertex is less than the adjacent vertex + edge distance
            //also checks if the distance at the start node so the graph is no unnecessarily updated
            if((distance[graph[currentEdge][1]] > distance[graph[currentEdge][0]] + graph[currentEdge][2]) && distance[graph[currentEdge][0]] != infinity)
            {
         //       printf("%d begin    %d end\n", graph[currentEdge][0], graph[currentEdge][1]);

          //      printf("end %d   start %d   weight %d\n", distance[graph[currentEdge][1]], distance[graph[currentEdge][0]], graph[currentEdge][2]);

                //update the distance to the vertex
                distance[graph[currentEdge][1]] = distance[graph[currentEdge][0]] + graph[currentEdge][2];

           //     printf("distance %d\n",  distance[graph[currentEdge][1]]);

                //update the predecessor
                predecessor[graph[currentEdge][1]] = graph[currentEdge][0];

            //    printf("predecessor %d\n",  predecessor[graph[currentEdge][1]]);

                printf("\n");

            }
        }
    }


    //keeps track of if a negative cycle exists
    int negativeCycleExists = 0;


        //does the edge check one more time to check if the distances update again
        for(int currentEdge = 0; currentEdge < edgeAmount; currentEdge++)
        {
            //if the distance changes a negative weight cycle exists
            if((distance[graph[currentEdge][1]] > distance[graph[currentEdge][0]] + graph[currentEdge][2]) && distance[graph[currentEdge][0]] != infinity)
            {
                    negativeCycleExists = 1;

            }
        }




        //tells the user that a negative weight cycle exists or prints the data of the graph if its does not exist
        if(negativeCycleExists == 1)
        {
            printf("negative weight cycle exists");
        }

        else
        {
            char alphabet = 'a';

            printf("distance to\n");

            for(int i = 0; i < vertexAmount; i++)
            {
                printf("%c: %d, ", alphabet, distance[i]);

                alphabet++;
            }

            alphabet = 'a';

            printf("\n\n predecessor\n");

            for(int i = 0; i < vertexAmount; i++)
            {
                printf("%c: %d, ", alphabet, predecessor[i]);

                alphabet++;
            }
        }



}


//used as a simpler way to add edges to a graph
void createEdge(vector<int> graph[], int location, int start, int end, int weight)
{
    graph[location].push_back(start);
    graph[location].push_back(end);
    graph[location].push_back(weight);

}


int main()
{
    vector<string> states = {"s","q1","q2","r1","r2"};

    string start = "s";

    vector<string> acceptStates = {"q1","r1"};

    vector<char> alphabet = {'a','b'};

    vector<string> *equation = new vector<string>[5];

    equation[0].push_back("q1");
    equation[0].push_back("r1");

    equation[1].push_back("q1");
    equation[1].push_back("q2");

    equation[2].push_back("q1");
    equation[2].push_back("q2");

    equation[3].push_back("r2");
    equation[3].push_back("r1");

    equation[4].push_back("r2");
    equation[4].push_back("r1");



  //a,b,c,d,e,f,g,h,i,j,k, l, m, n
  //0,1,2,3,4,5,6,7,8,9,10,11,12,13

  //begin, end, weight

    vector<int> *edges = new vector<int>[21];

    edges[0].push_back(0);
    edges[0].push_back(3);
    edges[0].push_back(3);

    edges[1].push_back(1);
    edges[1].push_back(0);
    edges[1].push_back(-2);

    edges[2].push_back(2);
    edges[2].push_back(1);
    edges[2].push_back(1);

    edges[3].push_back(2);
    edges[3].push_back(13);
    edges[3].push_back(-3);

    edges[4].push_back(2);
    edges[4].push_back(12);
    edges[4].push_back(3);

    edges[5].push_back(3);
    edges[5].push_back(4);
    edges[5].push_back(2);


    createEdge(edges,6,3,5,6);

    createEdge(edges,7,3,6,-1);

    createEdge(edges,8,3,13,-1);

    createEdge(edges,9,4,5,3);

    createEdge(edges,10,5,7,-2);

    createEdge(edges,11,6,7,1);

    createEdge(edges,12,7,9,3);

    createEdge(edges,13,7,10,-1);

    createEdge(edges,14,8,7,-4);

    createEdge(edges,15,9,8,2);

    createEdge(edges,16,9,10,3);

    createEdge(edges,17,11,10,2);

    createEdge(edges,18,12,11,-4);

    createEdge(edges,19,13,12,8);

    createEdge(edges,20,13,9,5);


    bellmanFord(edges, 14, 21, 10);


    vector<int> *testGraph = new vector<int>[3];

    createEdge(testGraph,0,0,1,1);

    createEdge(testGraph,1,1,2,-1);

    createEdge(testGraph,2,2,0,-1);

  //  bellmanFord(testGraph, 3, 3, 0);


//printf("%d", edges[0].size());


  //  vector<string> accept = {"f","d","f"};


  //  string test = "hfsidhgsiojg";

   // test = equation[0][0];

   // printf("%d", test.length());

    //printf("%s", test.c_str());

   // printf("%c", test.at(0));

 //  printf("%d", accept.size());

//   test(accept);

//dfaCheck(states, start, acceptStates, alphabet, equation, "a");
//dfaCheck(states, start, acceptStates, alphabet, equation, "b");

//dfaCheck(states, start, acceptStates, alphabet, equation, "aba");
//dfaCheck(states, start, acceptStates, alphabet, equation, "baa");

/*
dfaCheck(states, start, acceptStates, alphabet, equation, "ababa");
dfaCheck(states, start, acceptStates, alphabet, equation, "baba");
dfaCheck(states, start, acceptStates, alphabet, equation, "aababaab");
dfaCheck(states, start, acceptStates, alphabet, equation, "babaabaaabb");
dfaCheck(states, start, acceptStates, alphabet, equation, "");
*/
}
