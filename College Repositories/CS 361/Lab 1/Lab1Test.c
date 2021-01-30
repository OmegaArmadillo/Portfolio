void merge(int currentArray[], int start, int end, int start2, int end2)
{
    int firstSize = end - start + 1;
    int secondSize =  end2 - start2 + 1;

    int firstHalf[firstSize];
    int secondHalf[secondSize];

    for (int i = 0; i < firstSize; i++)
    {
        firstHalf[i] = currentArray[start + i];
    }

    for (int j = 0; j < secondSize; j++)
    {
         secondHalf[j] = currentArray[start2 + j];
    }


    int i = start;
    int j = 0;
    int k = 0;


    while (j < firstSize && k < secondSize)
    {
        if (firstHalf[j] <= secondHalf[k])
        {
            currentArray[i] = firstHalf[j];
            j++;
        }
        else
        {
            currentArray[i] = secondHalf[k];
            k++;
        }
        i++;
    }


    while (j < firstSize)
    {
        currentArray[i] = firstHalf[j];
        j++;
        i++;
    }


    while (k < secondSize)
    {
        currentArray[i] = secondHalf[k];
        k++;
        i++;
    }
}


void mergeSort(int currentArray[], int start, int end)
{
    if (start < end)
    {

        int end1 = (end + start)/2;
        int start2 = end1 +1;
        int end2 = end;

        mergeSort(currentArray, start, end1);
        mergeSort(currentArray, start2, end2);

        merge(currentArray, start, end1, start2, end2);
    }
}



/* UTILITY FUNCTIONS */
/* Function to print an array */
void printArray(int A[], int size)
{
    int i;
    for (i=0; i < size; i++)
        printf("%d ", A[i]);
    printf("\n");
}

/* Driver program to test above functions */
int main()
{
    int arr[] = {12, 11, 13, 5, 6, 7};
    int arr_size = sizeof(arr)/sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    mergeSort(arr, 0, arr_size - 1);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}
