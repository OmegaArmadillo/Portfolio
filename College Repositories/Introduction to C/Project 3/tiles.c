#include <stdio.h>

    struct tile
    {
        int canLeft;
        int canRight;
        int canUp;
        int canDown;
        int value;
        
    };


void printBoard (struct tile gameBoard[])
{
    
        	printf("%d %d %d %d\n", gameBoard[0].value, gameBoard[1].value, gameBoard[2].value, gameBoard[3].value);
            printf("%d %d %d %d\n", gameBoard[4].value, gameBoard[5].value, gameBoard[6].value, gameBoard[7].value);
            printf("%d %d %d %d\n", gameBoard[8].value, gameBoard[9].value, gameBoard[10].value, gameBoard[11].value);
            printf("%d %d %d %d\n", gameBoard[12].value, gameBoard[13].value, gameBoard[14].value, gameBoard[15].value);    
}


int selectionCheck()
{



        int currentTile;    
        int checkSelection = 0;

    
        while(checkSelection == 0 )
        {	
        	printf("To select the tile you want to move enter the value 1-16\n ");
            scanf("%d", &currentTile);
            
            //currentTile = currentTile - 1;
            
            
            if(currentTile < 1)
            {
          	printf("Invalid Tile\n ");              
            }
            
            else if (currentTile > 15)
            {
          	printf("Invalid Tile\n ");                 
            }
            
             else
            {
                checkSelection = 1;
            } 
  
  
        }	
        	
               checkSelection = 0; 
               
               
               return currentTile;
    
}



int intToArray(int tileSelect, struct tile gameBoard[])
{
    int currentTile;
    
 
       for(int i = 0; i < 16; i++)
       {
           if(tileSelect == gameBoard[i].value)
           {
               currentTile = i;
           }
       } 
 
 
    return currentTile;
}


int directionCheck()
{
  
    int direction;
    int checkDirection = 0;

  
       while (checkDirection == 0)
       {
        	
        	printf("Select the direction you want to move the tile\n");
        	printf("1: Left\n");
        	printf("2: Right\n");
        	printf("3: Up\n");
        	printf("4: Down\n");
            scanf("%d", &direction); 
            
            
            if(direction < 1)
            {
          	    printf("Invalid Direction\n ");              
            }
            
            else if (direction > 4)
            {
          	    printf("Invalid Direction\n ");                 
            }
            
            else
            {
              checkDirection = 1; 
            }
            
       }   
            
            checkDirection = 0;  
  
  return direction;
    
}








int winChecker(struct tile gameBoard[])
{
  int hasWon = 1;
 
         for(int i = 0; i < 15; i++)
        {
            
            if(gameBoard[i].value != i+1)
            {
                
                hasWon = 0;
            }

        
    
        }
  
    return hasWon;
}






int main()
{

    
    
    int currentTile;
    int direction;
    int hasWon = 0;
    
    
    
    

    
    struct tile tile1 = { .canLeft = 0, .canRight = 1, .canUp = 0, .canDown = 1, .value = 1};    
    struct tile tile2 = { .canLeft = 1, .canRight = 1, .canUp = 0, .canDown = 1, .value = 2};    
    struct tile tile3 = { .canLeft = 1, .canRight = 1, .canUp = 0, .canDown = 1, .value = 3};
    struct tile tile4 = { .canLeft = 1, .canRight = 0, .canUp = 0, .canDown = 1, .value = 4};
    
    struct tile tile5 = { .canLeft = 0, .canRight = 1, .canUp = 1, .canDown = 1, .value = 5};
    struct tile tile6 = { .canLeft = 1, .canRight = 1, .canUp = 1, .canDown = 1, .value = 6};
    struct tile tile7 = { .canLeft = 1, .canRight = 1, .canUp = 1, .canDown = 1, .value = 7};
    struct tile tile8 = { .canLeft = 1, .canRight = 0, .canUp = 1, .canDown = 1, .value = 8};
    
    struct tile tile9 = { .canLeft = 0, .canRight = 1, .canUp = 1, .canDown = 1, .value = 9};
    struct tile tile10 = { .canLeft = 1, .canRight = 1, .canUp = 1, .canDown = 1, .value = 10};
    struct tile tile11 = { .canLeft = 1, .canRight = 1, .canUp = 1, .canDown = 1, .value = 11};
    struct tile tile12 = { .canLeft = 1, .canRight = 0, .canUp = 1, .canDown = 1, .value = 0};
    
    struct tile tile13 = { .canLeft = 0, .canRight = 1, .canUp = 1, .canDown = 0, .value = 13};
    struct tile tile14 = { .canLeft = 1, .canRight = 1, .canUp = 1, .canDown = 0, .value = 14};
    struct tile tile15 = { .canLeft = 1, .canRight = 1, .canUp = 1, .canDown = 0, .value = 15};
    struct tile tile16 = { .canLeft = 1, .canRight = 0, .canUp = 1, .canDown = 0, .value = 12};
    
    
    
    struct tile gameBoard[16] = {tile1, tile2, tile3, tile4, 
                                 tile5, tile6, tile7, tile8,
                                 tile9, tile10, tile11, tile12, 
                                 tile13, tile14, tile15, tile16};
    
    while(hasWon<1)
    {
        
        hasWon = 1;
        
    printBoard(gameBoard);

    currentTile = selectionCheck();    

    currentTile = intToArray(currentTile, gameBoard);
       
    direction = directionCheck();  
       
       


        
            switch(direction)
            {
                case 1:
                
                
                
                if(gameBoard[currentTile].canLeft == 1)
                {

               
               
                    if(gameBoard[currentTile-1].value == 0)
                    {
                        gameBoard[currentTile-1].value = gameBoard[currentTile].value;
                        gameBoard[currentTile].value = 0;
                    }
                
                
                    else    
                    {
                        printf("Your selected tile can not be moved to that location because it is blocked\n");
                    }               
               
            
                }
                
                
                
                else
                {
                    
                    printf("Your selected tile can not be moved to the left\n");
                }
                
                
                
                break;
                
                
                case 2:
                
                if(gameBoard[currentTile].canRight == 1)
                {

               
               
                    if(gameBoard[currentTile+1].value == 0)
                    {
                        gameBoard[currentTile+1].value = gameBoard[currentTile].value;
                        gameBoard[currentTile].value = 0;
                    }
                
                
                    else    
                    {
                        printf("Your selected tile can not be moved to that location because it is blocked\n");
                    }               
               
            
                }
                
                
                
                else
                {
                    
                    printf("Your selected tile can not be moved to the right\n");
                }
                      
                
                
                break;
                
                
                case 3:
                
                
                if(gameBoard[currentTile].canUp == 1)
                {

               
               
                    if(gameBoard[currentTile-4].value == 0)
                    {
                        gameBoard[currentTile-4].value = gameBoard[currentTile].value;
                        gameBoard[currentTile].value = 0;
                    }
                
                
                    else    
                    {
                        printf("Your selected tile can not be moved to that location because it is blocked\n");
                    }               
               
            
                }
                
                
                
                else
                {
                    
                    printf("Your selected tile can not be moved up\n");
                }
                           
                
                
                
                break;
                
                
                case 4:
                
                if(gameBoard[currentTile].canDown == 1)
                {

               
               
                    if(gameBoard[currentTile+4].value == 0)
                    {
                        gameBoard[currentTile+4].value = gameBoard[currentTile].value;
                        gameBoard[currentTile].value = 0;
                    }
                
                
                    else    
                    {
                        printf("Your selected tile can not be moved to that location because it is blocked\n");
                    }               
               
            
                }
                
                
                
                else
                {
                    
                    printf("Your selected tile can not be moved down\n");
                }
                            
                
                
                break;
                
                default:
                
                    printf("Your selected tile can not be moved to that location\n");
                
            }
    
        
        
        
        

      hasWon = winChecker(gameBoard);  
        

        
   
        
        
        
    }
    


    printBoard(gameBoard);
        	


    
    printf("You won");
    
    
    return 0;
}


