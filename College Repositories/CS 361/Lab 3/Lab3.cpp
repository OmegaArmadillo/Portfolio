#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>

using namespace std;


//function to print parentheses taken from
//https://www.geeksforgeeks.org/matrix-chain-multiplication-dp-8/

//finds the optimal parentheses for the matrix chain multiplication
void parenthesize(int i, int j, int n, int *kMatrix, int &startMatrix)
{
    //used if only one matrix is left to check
    if (i == j)
    {
        printf("%d", startMatrix++);
        return;
    }

    printf("(");

    //repeats the checks
    parenthesize(i, *((kMatrix+i*n)+j), n, kMatrix, startMatrix);
    parenthesize(*((kMatrix+i*n)+j) + 1, j, n, kMatrix, startMatrix);

    printf(")");
}









//Function that does mcm using dynamic programming
void mcmDP(int pArray[],int arraySize)
{
    //matrices that keep track of the most efficient multiplication and the most efficient k values
    int matrixValue[arraySize][arraySize];
    int optimalPlace[arraySize][arraySize];

    //the actual bound the loops should count to
    int maxActual = arraySize - 1;


    //fills the matrix with -1 to make the output easier to read
    for(int i = 1; i <= maxActual; i++)
    {
        for(int j = 1; j <= maxActual; j++)
        {
            matrixValue[i][j] = -1;
        }

    }



    //sets the values with the same i and j to zero
    for(int i = 1; i <= maxActual; i++)
    {
        matrixValue[i][i] = 0;
    }

    //used in the loops
    int j = 1;
    int k = 1;

    //keeps track of the current calculation made by the loop
    int currentCalculation;

    //used to keep track of the bound the loops should go to
    int bound = maxActual - 1;

    //keeps track of the distance between i and j in the calculations
    int gap = 1;



//calculates the values for each diagonal in the matrix
for(int m = 0; m < maxActual; m++ )
 {

    //calculates the mcm from i to j
    for(int i = 1; i <= bound; i++)
    {
        //sets the i and and values for the loops
        j = i + gap;
        k = i;

        //calculates the value for the first k.
        printf("calculating %d %d: %d + %d %d: %d + (p%d %d * p%d %d * p%d %d) \n", i, k, matrixValue[i][k], k+1, j, matrixValue[k+1][j], i-1, pArray[i-1], k, pArray[k], j, pArray[j]);
        matrixValue[i][j] = matrixValue[i][k] + matrixValue[k+1][j] + (pArray[i-1] * pArray[k] * pArray[j]);
        printf("the total is %d \n", matrixValue[i][j]);

        //puts the k value into the k matrix and increases k
        optimalPlace[i][j] = k;
        k++;

        //calculates the value for the other ks
        for(k; k < j; k++)
        {
            //calculates the mcm value
            printf("calculating new %d %d: %d + %d %d: %d + (p%d %d * p%d %d * p%d %d) \n", i, k, matrixValue[i][k], k+1, j, matrixValue[k+1][j], i-1, pArray[i-1], k, pArray[k], j, pArray[j]);
            currentCalculation = matrixValue[i][k] + matrixValue[k+1][j] + (pArray[i-1] * pArray[k] * pArray[j]);
            printf("old %d  new %d \n", matrixValue[i][j], currentCalculation);

            //checks if the current calculated value is lower than the current lowest
            if(currentCalculation < matrixValue[i][j])
            {
                //if it is the new low is added and the new lowest k is added
                matrixValue[i][j] = currentCalculation;
                optimalPlace[i][j] = k;
            }

            printf("current %d \n", matrixValue[i][j]);
        }

        printf("\n");

    }

    //lowers the bound and raises the gap
    bound--;
    gap++;


printf("\n\n\n");

}


//prints the matrix
    for(int i = 1; i <= maxActual; i++)
    {
        for(int j = 1; j <= maxActual; j++)
        {
            printf("%d, ",matrixValue[i][j]);
        }
        printf("\n");

    }


 //prints the parentheses and the optimal cost


    int startMatrix = 1;
    cout << "Optimal Parenthesization is : ";
    parenthesize(1, 7-1, 7, (int *)optimalPlace, startMatrix);
    cout << "\nOptimal Cost is : " << matrixValue[1][7-1];

}







//helper for the mcmMemo function
int memoCalculate(int *matrixValue, int pArray[], int i, int j, int *optimalPlace, int arraySize)
{
    //the value that represents infinity in the other for loop
    int infinity = 1000000;

    //keeps track of the calculated value
    int currentValue;

    //if the value is already calculated it returns that value
    if(*((matrixValue+i*arraySize)+j) > 0)
    {
        return *((matrixValue+i*arraySize)+j);
    }

    //if the i and j is the same it should be zero and returns that value
    if(i == j)
    {
        *((matrixValue+i*arraySize)+j) = 0;
    }
    //otherwise the value is calculated
    else
    {
        //sets the value there to be the new infinity
        *((matrixValue+i*arraySize)+j) = infinity;


        for(int k = i; k <= (j-1); k++)
        {
                //calculates the value by calling the function again
                currentValue = memoCalculate(matrixValue, pArray, i, k, optimalPlace, arraySize) +
                             memoCalculate(matrixValue, pArray, k+1, j, optimalPlace, arraySize) +
                             (pArray[i-1] * pArray[k] * pArray[j]);

                //checks if the calculated value is lower than the current lowest value
                if (currentValue < *((matrixValue+i*arraySize)+j) )
                {
                    //if it is the values is replaced and the k value is replaced
                    *((matrixValue+i*arraySize)+j) = currentValue;
                    *((optimalPlace+i*arraySize)+j) = k;
                }
        }

    }


//returns the calculated value
return *((matrixValue+i*arraySize)+j);




}



//calculates the mcm using memoization
void mcmMemo(int pArray[], int arraySize)
{

    //matrices used form the optimal calculation and the optimal ks
    int matrixValue[7][7];
    int optimalPlace[7][7];


    //fills the value matrix with -1 to represent infinity
    int i;
    int j;
    for(i = 1; i <= 6; i++)
    {
        for(j = 1; j <= 6; j++)
        {
            matrixValue[i][j] = -1;
        }

    }

    //calls the helper function, the int here is not important for the calculations
    int nothing = memoCalculate((int *)matrixValue, pArray, 1, 6, (int *)optimalPlace, 7);

    //prints the matrix
    for(i = 1; i <= 6; i++)
    {
        for(j = 1; j <= 6; j++)
        {
            printf("%d, ",matrixValue[i][j]);
        }
        printf("\n");

    }


    //finds the optimal parentheses

    int startMatrix = 1;
    cout << "Optimal Parenthesization is : ";
    parenthesize(1, 7-1, 7, (int *)optimalPlace, startMatrix);
    cout << "\nOptimal Cost is : " << matrixValue[1][7-1];

}






//preforms a breadth first search on an adjacency matrix
void bfsMatrix(int *graph, int start, int matrixSize)
{
    //graph nodes start at 0 so -1 is used as blank in the queue
    //in the color array 0 is white, 1 is gray, 2 is black


    //keeps track of the color of the nodes
    int color[matrixSize] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    //keeps track of the minimum distance to the nodes
    int distance[matrixSize] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    //keeps track of the predecessor to the nodes
    int predecessor[matrixSize] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    //used to keep track of what node should be processed next
    int queue[matrixSize] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    //keeps track of the current position in the queue
    int queuePos = 0;

    //keeps track of the current node being processed
    int currentNode;

    //sets the color of the start node to be gray
    color[start] = 1;

    //puts the start node in the queue
    queue[0] = start;



    //checks if the queue is empty
    while(queue[0] != -1)
    {
        //gets the first node in the queue and decreases the queue counter
        currentNode = queue[0];
        queuePos--;

        //moves the queue down
        for(int i = 0; i < matrixSize; i++)
        {
            queue[i] = queue[i+1];
        }

            //sets the last value in the queue to be -1 so the queue will be correct
            queue[matrixSize - 1] = -1;

            //goes through the row in the matrix that represents that node
            for(int n = 0; n < matrixSize; n++)
            {
                //goes through every value in the array to check if the current node is adjacent to the node being checked
                if(*((graph+currentNode*matrixSize)+n) != 0)
                {
                    //checks if the node is already been visited
                    if(color[n] == 0)
                    {
                        //if it is not visited updates the information for the node
                        color[n] = 1;
                        distance[n] = distance[currentNode] + 1;
                        predecessor[n] = currentNode;

                        //adds the node into the queue and updates the queue position
                        queuePos++;
                        queue[queuePos] = n;



                    }

                }

            }

                //changes the checked node to black after all calculations are made
                color[currentNode] = 2;
    }



char letters[14] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n'};

printf("Distance to\n");
for(int i = 0; i < matrixSize; i++)
{
    printf("%c: %d,  ", letters[i], distance[i]);
}
printf("\n");

printf("Predecessor to\n");
for(int i = 0; i < matrixSize; i++)
{
    printf("%c: %d, ", letters[i], predecessor[i]);
}
printf("\n");

printf("Color of\n");
for(int i = 0; i < matrixSize; i++)
{
    printf("%c: %d, ", letters[i], color[i]);
}
printf("\n");


}







//preforms a breadth first search on an adjacency list
void bfsList(vector<int> adjList[], int start, int vertexAmount)
{
    //graph nodes start at 0 so -1 is used as blank in the queue
    //in the color array 0 is white, 1 is gray, 2 is black

    //keeps track of the color of the nodes
    int color[vertexAmount] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    //keeps track of the minimum distance to the nodes
    int distance[vertexAmount] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0};

    //keeps track of the predecessor to the nodes
    int predecessor[vertexAmount] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    //used to keep track of what node should be processed next
    int queue[vertexAmount] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};

    //keeps track of the current position in the queue
    int queuePos = 0;

    //keeps track of the current node being processed
    int currentNode;

    //sets the color of the start node to be gray
    color[start] = 1;

    //puts the start node in the queue
    queue[0] = start;



    //checks if the queue is empty
    while(queue[0] != -1)
    {
        //gets the first node in the queue and decreases the queue counter
        currentNode = queue[0];
        queuePos--;

        //moves the queue down
        for(int i = 0; i < vertexAmount; i++)
        {
            queue[i] = queue[i+1];
        }
            //sets the last value in the queue to be -1 so the queue will be correct
            queue[vertexAmount - 1] = -1;

            //goes through the current node's list of adjacent vertices
            for(int n = 0; n < adjList[currentNode].size(); n++)
            {

                    //checks if the node in the list has already been visited
                    if(color[adjList[currentNode][n]] == 0)
                    {
                        //if it is not visited updates the information for the node
                        color[adjList[currentNode][n]] = 1;
                        distance[adjList[currentNode][n]] = distance[currentNode] + 1;
                        predecessor[adjList[currentNode][n]] = currentNode;

                        //adds the node into the queue and updates the queue position
                        queuePos++;
                        queue[queuePos] = adjList[currentNode][n];


                    }


            }

                //changes the checked node to black after all calculations are made
                color[currentNode] = 2;
    }





char letters[14] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n'};

printf("Distance to\n");
for(int i = 0; i < vertexAmount; i++)
{
    printf("%c: %d,  ", letters[i], distance[i]);
}
printf("\n");

printf("Predecessor to\n");
for(int i = 0; i < vertexAmount; i++)
{
    printf("%c: %d, ", letters[i], predecessor[i]);
}
printf("\n");

printf("Color of\n");
for(int i = 0; i < vertexAmount; i++)
{
    printf("%c: %d, ", letters[i], color[i]);
}
printf("\n");


}







int main()
{
int pArray[7] = {30, 4, 8, 5, 10, 25, 15};
                //   a,b,c,d,e,f,g,h,i,j,k,l,m,n
int graph[14][14] = {0,1,0,1,0,0,0,0,0,0,0,0,0,0,
                     1,0,1,0,0,0,0,0,0,0,0,0,0,0,
                     0,1,0,0,0,0,0,0,0,0,0,0,1,1,
                     1,0,0,0,1,1,1,0,0,0,0,0,0,1,
                     0,0,0,1,0,1,0,0,0,0,0,0,0,0,
                     0,0,0,1,1,0,0,1,0,0,0,0,0,0,
                     0,0,0,1,0,0,0,1,0,1,0,0,0,0,
                     0,0,0,0,0,1,1,0,1,0,1,0,0,0,
                     0,0,0,0,0,0,0,1,0,1,0,0,0,0,
                     0,0,0,0,0,0,1,0,1,0,1,0,0,1,
                     0,0,0,0,0,0,0,1,0,1,0,1,0,0,
                     0,0,0,0,0,0,0,0,0,0,1,0,1,0,
                     0,0,1,0,0,0,0,0,0,0,0,1,0,1,
                     0,0,1,1,0,0,0,0,0,1,0,0,1,0,
                     };


vector<int> *adjList = new vector<int>[14];
//a
adjList[0].push_back(1);
adjList[0].push_back(3);

//b
adjList[1].push_back(0);
adjList[1].push_back(2);

//c
adjList[2].push_back(1);
adjList[2].push_back(12);
adjList[2].push_back(13);

//d
adjList[3].push_back(0);
adjList[3].push_back(4);
adjList[3].push_back(5);
adjList[3].push_back(6);
adjList[3].push_back(13);

//e
adjList[4].push_back(3);
adjList[4].push_back(5);

//f
adjList[5].push_back(3);
adjList[5].push_back(4);
adjList[5].push_back(7);

//g
adjList[6].push_back(3);
adjList[6].push_back(7);
adjList[6].push_back(9);

//h
adjList[7].push_back(5);
adjList[7].push_back(6);
adjList[7].push_back(8);
adjList[7].push_back(10);

//i
adjList[8].push_back(7);
adjList[8].push_back(9);

//j
adjList[9].push_back(6);
adjList[9].push_back(8);
adjList[9].push_back(10);
adjList[9].push_back(13);

//k
adjList[10].push_back(7);
adjList[10].push_back(9);
adjList[10].push_back(11);

//l
adjList[11].push_back(10);
adjList[11].push_back(12);

//m
adjList[12].push_back(2);
adjList[12].push_back(11);
adjList[12].push_back(13);

//n
adjList[13].push_back(2);
adjList[13].push_back(3);
adjList[13].push_back(9);
adjList[13].push_back(12);


//printf("%d", adjList[13][3]);

//mcmDP(pArray,7);
mcmMemo(pArray,7);
//bfsMatrix((int *)graph,0,14);

//printf("\n");

//bfsList(adjList,0,14);
}
