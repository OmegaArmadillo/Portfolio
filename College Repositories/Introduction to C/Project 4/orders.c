
#include <stdio.h>
#include <stdlib.h>

#define companyAmount 5
#define productAmount 10

struct company
{

  int ID;
  char Name[20];
  char State[15];
  char phoneNumber[15];
  char Website[40];

};

struct product
{

  int ID;
  char Name[30];
  int supplyId;
  float Price;
  int Amount;

};




void printProductList(struct company companyList[], struct product productList[])
{


	 

		for (int i = 0; i < productAmount; i++)
			{

				printf ("%d. ", i + 1);

				printf ("Product Name: %s   ", productList[i].Name);



				for (int j = 0; j < companyAmount; j++)
					{

						if (productList[i].supplyId == companyList[j].ID)
							{

								printf ("Company: %s   ", companyList[j].Name);

							}

					}

					printf ("Price: %.2f   ", productList[i].Price);
					printf ("Amount left: %d\n", productList[i].Amount);



			}


	
	
	
		printf ("11: Complete Order\n");


    
    
}











int askArrayNumber()
{
 
 
 int arrayNumber;
 
 		printf ("Enter the number next to the product you want to order or 11 to complete the order:");
 
		scanf("%d", &arrayNumber);




	       while (arrayNumber < 1 || arrayNumber > 12)
	        {
	            printf ("\nInvalid Product Number or Command Number");
                printf ("\nEnter the number next to the product you want to order or 11 to complete the order:");
                scanf("%d", &arrayNumber);
	        }
 
    return arrayNumber;
 
    
}





int askForAmount()
{

    int amountOrdered;

	printf ("\nhow much do you want to order: ");
      
	scanf ("%d", &amountOrdered);

    return amountOrdered;    
}





int main ()
{



  FILE *companyPointer;
  FILE *productPointer;
  FILE *orderPointer;

  struct company companyList[5];
  struct product productList[10];


  char customerName[30];
  char dateOrdered[20];
  int amountOrdered;
  float totalPrice;


  int selectedProduct;
  int arrayNumber;
  int productSupplier;
  
  int orderComplete = 0;





//setting the pointers
  companyPointer = fopen ("companies.txt", "r");
  productPointer = fopen ("products.txt", "r");
  orderPointer = fopen ("order.txt", "a");


  //if statements to see id the files opened correctly
  if (companyPointer == NULL)
    {
      fprintf (stderr, "Can't open file %s!\n", "companies.txt");

    }

  if (productPointer == NULL)
    {
      fprintf (stderr, "Can't open file %s!\n", "products.txt");

    }

  if (orderPointer == NULL)
    {
      fprintf (stderr, "Can't open file %s!\n", "order.txt");

    }


	
	
  while (orderComplete == 0)
   {	
	
	
	
		//loop to read the file of companies
		for (int i = 0; i < companyAmount; i++)
			{
				fscanf (companyPointer, "%d", &companyList[i].ID);

				fscanf (companyPointer, "%s", &companyList[i].Name);

				fscanf (companyPointer, "%s", &companyList[i].State);

				fscanf (companyPointer, "%s", &companyList[i].phoneNumber);

				fscanf (companyPointer, "%s", &companyList[i].Website);
			}



		//loop to read the file of products
		for (int i = 0; i < productAmount; i++)
			{
				fscanf (productPointer, "%d", &productList[i].ID);

				fscanf (productPointer, "%s", &productList[i].Name);

				fscanf (productPointer, "%d", &productList[i].supplyId);

				fscanf (productPointer, "%f", &productList[i].Price);

				fscanf (productPointer, "%d", &productList[i].Amount);
			}



	
	

            printProductList(companyList, productList);
	 
	 

            arrayNumber = askArrayNumber();

	    
			//will complete the order if 11 is selected
			if(arrayNumber == 11)
			{
				orderComplete = 1;
			}
		
	
	
		else
			
		{

			//used to get the correct array value from the input
			selectedProduct = arrayNumber - 1;

						
			//gets the correct supplier name for the chosen product
			for (int i = 0; i < companyAmount; i++)
				{
					if (productList[selectedProduct].supplyId == companyList[i].ID)
						{

						productSupplier = i;

						}
				}	 
    



			printf ("\nwho is ordering this product: ");

			scanf("%s",customerName);


			printf ("\nwhat is today's date: ");

			scanf("%s",dateOrdered);



        amountOrdered = askForAmount();




			while (amountOrdered > productList[selectedProduct].Amount)
			{
					printf ("\nThere is not enough inventory to fill that order");
                    amountOrdered = askForAmount();
			}

			productList[selectedProduct].Amount = productList[selectedProduct].Amount - amountOrdered;

			totalPrice = productList[selectedProduct].Price * amountOrdered;


			fprintf (orderPointer,
			"Product: %s   Supplier: %s   Customer Name: %s   Date Ordered: %s   Amount Ordered: %d   Product Price: %.2f   Total Price: %f\n",
			productList[selectedProduct].Name, companyList[productSupplier].Name, customerName, dateOrdered, amountOrdered, productList[selectedProduct].Price, totalPrice);


	}

    
	
	
	
   }



printf("Your order has been completed");	
	
	

//closing the pointers 
  fclose (companyPointer);
  fclose (productPointer);
  fclose (orderPointer);

  return 0;
}



