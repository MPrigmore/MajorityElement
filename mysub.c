int findMax(int countA, int countB, int indexA, int indexB)
{
    if (countA == countB)
        return 0;
    else if (countA > countB)
        return indexA;
    else
        return indexB;
}

int mysub(int n)
{
    int result;
    int myArray[4];
    int queryIndex = 1;
    int iterByOne = 1;
    int firstRun = 1;
    int previousRun = -1;
    
    //Same value in both (1) or (0) ==> Need both so we can iterate by two eventually.
    int booleanIndexA1 = -1;
    int booleanIndexA2 = -1;
    int indexCountA = 0; //Used to keep count of boolean value A
    
    int booleanIndexB = -1; //Remaining boolean value (1) or (0)
    int indexCountB = 0; //Used to keep count of boolean value B
    
    while (iterByOne && queryIndex < n - 2) //Haven't found two different boolean values and their index yet.
    {
        myArray[0] = queryIndex;
        myArray[1] = queryIndex + 1;
        myArray[2] = queryIndex + 2;
        myArray[3] = queryIndex + 3;
        queryIndex++;
        
        result = QCOUNT(1, myArray);
        
        if (firstRun)
        {
            if (result == 4)
            {
                booleanIndexA1 = myArray[0];
                booleanIndexA2 = myArray[1];
                indexCountA = 4;
            }
            else if (result == 2)
            {
                //DO NOTHING because we know nothing about the indexes yet.
            }
            else if (result == 0)
            {
                //DO NOTHING because we know nothing about the indexes yet.
            }
            else
            {
                printf("********ERROR: On first run, result is a value other than 4, 2, or 0 ********\n");
                return -1;
            }
            firstRun = 0;
            previousRun = result;
        }
        else //Second run.
        {
            if (result == 4 && previousRun == 4) //4 ==> 4
            {
                indexCountA++;
				if (indexCountA > n/2) //We have reached a majority.
				{	
					return indexCountA;
				}
            }
            else if (result == 4 && previousRun == 2) //2 ==> 4
            {
                booleanIndexA1 = 2;
                booleanIndexA2 = 3;
                booleanIndexB = 1;
                indexCountA = 4;
                indexCountB = 1;
                queryIndex = 6; //Update query index for iterating by 2
                iterByOne = 0;
            }
            else if (result == 2 && previousRun == 4) //4 ==> 2
            {
                queryIndex += 3;
                booleanIndexB = queryIndex - 1;
                indexCountB = 1;
                iterByOne = 0;
            }
            else if (result == 2 && previousRun == 2) //2 ==> 2
            {
                //Store the two index with the same boolean values
                booleanIndexA1 = 1;
                booleanIndexA2 = 5;
                queryIndex = 6; //Update query index for iterating by 2
                
                //Check Right 2 elements of the middle 3:
                myArray[0] = booleanIndexA1;
                myArray[1] = booleanIndexA2;
                myArray[2] = 3;
                myArray[3] = 4;
                
                result = QCOUNT(1, myArray);
                
                if (result ==2)
                {
                    //Need another iteration to find opposite boolean value (check left 2 elements of the middle 3).
                    myArray[0] = booleanIndexA1;
                    myArray[1] = booleanIndexA2;
                    myArray[2] = 2;
                    myArray[3] = 3;
                    
                    result = QCOUNT(1, myArray);
                    
                    if (result == 2)
                    {
                        //we know the opposite boolean value (Middle is different at index 3).
                        booleanIndexB = 3;
                        indexCountA = 4;
                        indexCountB = 1;
                        iterByOne = 0;
                    }
                    else if (result == 4)
                    {
                        //we know the opposite boolean value (Far right is different at index 4).
                        booleanIndexB = 4;
                        indexCountA = 4;
                        indexCountB = 1;
                        iterByOne = 0;
                    }
                    else
                    {
                        printf("********ERROR: On first run, result is a value other than 4, 2, or 0 ********\n");
                        return -1;
                    }
                }
                else if (result == 4)
                {
                    //we know the opposite boolean value (Far left at index 2).
                    booleanIndexB = 2;
                    indexCountA = 4;
                    indexCountB = 1;
                    iterByOne = 0;
                    
                }
                else if (result == 0)
                {
                    //We know the opposite boolean value (all three are different (we will use index 2).
                    booleanIndexB = 2;
                    indexCountA = 2;
                    indexCountB = 3;
                    iterByOne = 0;
                }
                else
                {
                    printf("********ERROR: On first run, result is a value other than 4, 2, or 0 ********\n");
                    return -1;
                }
            }
            else if (result == 2 && previousRun == 0) //0 ==> 2
            {
                //We know that index 1 and 5 are opposite boolean values
                //Store the two indexes with the opposite boolean values
                booleanIndexA1 = 1;
                booleanIndexB = 5;
                queryIndex = 6; //Update query index for iterating by 2
                
                //Check Right 2 elements of the middle 3:
                myArray[0] = booleanIndexA1;
                myArray[1] = booleanIndexB;
                myArray[2] = 3;
                myArray[3] = 4;
                
                result = QCOUNT(1, myArray);
                
                if (result == 2)
                {
                    //We know that index 3 and 4 are the same boolean values and index 2 is opposite boolean value.
                    booleanIndexA1 = 3;
                    booleanIndexA2 = 4;
                    booleanIndexB = 2;
                    indexCountA = 3;
                    indexCountB = 2;
                    iterByOne = 0;
                }
                else if (result == 0)
                {
                    //Need another iteration to find the indexes we need (check left 2 elements of the middle 3).
                    myArray[0] = booleanIndexA1;
                    myArray[1] = booleanIndexB;
                    myArray[2] = 2;
                    myArray[3] = 3;
                    
                    result = QCOUNT(1, myArray);
                    
                    if (result == 0)
                    {
                        booleanIndexA1 = 2;
                        booleanIndexA2 = 4;
                        booleanIndexB = 3;
                        indexCountA = 3;
                        indexCountB = 2;
                        iterByOne = 0;
                    }
                    if (result ==2)
                    {
                        booleanIndexA1 = 2;
                        booleanIndexA2 = 3;
                        booleanIndexB = 4;
                        indexCountA = 3;
                        indexCountB = 2;
                        iterByOne = 0;
                    }
                }
            }
            else if (result == 0 && previousRun == 2) //2 ==> 0
            {
                //We know that index 1 and 5 are opposite boolean values
                //Store the two indexes with the opposite boolean values
                booleanIndexA1 = 1;
                booleanIndexB = 5;
                queryIndex = 6; //Update query index for iterating by 2
                
                //Check Right 2 elements of the middle 3:
                myArray[0] = booleanIndexA1;
                myArray[1] = booleanIndexB;
                myArray[2] = 3;
                myArray[3] = 4;
                
                result = QCOUNT(1, myArray);
                
                if (result == 2)
                {
                    //We know that index 3 and 4 are the same boolean values and index 2 is opposite boolean value.
                    booleanIndexA1 = 3;
                    booleanIndexA2 = 4;
                    booleanIndexB = 2;
                    indexCountA = 3;
                    indexCountB = 2;
                    iterByOne = 0;
                }
                else if (result == 0)
                {
                    //Need another iteration to find the indexes we need (check left 2 elements of the middle 3).
                    myArray[0] = booleanIndexA1;
                    myArray[1] = booleanIndexB;
                    myArray[2] = 2;
                    myArray[3] = 3;
                    
                    result = QCOUNT(1, myArray);
                    
                    if (result == 0)
                    {
                        booleanIndexA1 = 2;
                        booleanIndexA2 = 4;
                        booleanIndexB = 3;
                        indexCountA = 3;
                        indexCountB = 2;
                        iterByOne = 0;
                    }
                    if (result ==2)
                    {
                        booleanIndexA1 = 2;
                        booleanIndexA2 = 3;
                        booleanIndexB = 4;
                        indexCountA = 3;
                        indexCountB = 2;
                        iterByOne = 0;
                    }
                }
            }
            else if (result == 0 && previousRun == 0) //0 ==> 0
            {
                //Store the two index with the same boolean values
                booleanIndexA1 = 1;
                booleanIndexA2 = 5;
                queryIndex = 6; //Update query index for iterating by 2
                
                //Check Right 2 elements of the middle 3:
                myArray[0] = booleanIndexA1;
                myArray[1] = booleanIndexA2;
                myArray[2] = 3;
                myArray[3] = 4;
                
                result = QCOUNT(1, myArray);

                if (result == 0)
                {
                    booleanIndexA1 = 3;
                    booleanIndexA2 = 4;
                    booleanIndexB = 2;
                    indexCountA = 2;
                    indexCountB = 3;
                    iterByOne = 0;
                }
                else if (result == 2)
                {
                    //Need another iteration to find the indexes we need (check left 2 elements of the middle 3).
                    myArray[0] = booleanIndexA1;
                    myArray[1] = booleanIndexA2;
                    myArray[2] = 2;
                    myArray[3] = 3;
                    
                    result = QCOUNT(1, myArray);
                    
                    if (result == 0)
                    {
                        booleanIndexA1 = 2;
                        booleanIndexA2 = 3;
                        booleanIndexB = 4;
                        indexCountA = 2;
                        indexCountB = 3;
                        iterByOne = 0;
                    }
                    if (result ==2)
                    {
                        booleanIndexA1 = 2;
                        booleanIndexA2 = 4;
                        booleanIndexB = 3;
                        indexCountA = 2;
                        indexCountB = 3;
                        iterByOne = 0;
                    }
                }
            }
            else
            {
                printf("********ERROR: Result is a value other than 4, 2, or 0 ********\n");
                return -1;
            }
            previousRun = result;
        }
    }
    
    //Iterating by 2 now
    while (queryIndex < n)
    {
        if (indexCountA > n/2) //We have a majority.
        {
            return booleanIndexA1;
        }
        else if (indexCountB > n/2) //We have a majority.
        {
            return booleanIndexB;
        }
        else
        {
            myArray[0] = booleanIndexA1;
            myArray[1] = booleanIndexA2;
            myArray[2] = queryIndex;
            myArray[3] = queryIndex + 1;
            queryIndex += 2;
            
            result = QCOUNT(1, myArray);
            
            if (result == 4) //two of the same values seen.
            {
                indexCountA += 2;
            }
            else if (result == 2) //One of each seen.
            {
                indexCountA += 1;
                indexCountB += 1;
            }
            else if (result == 0) //two new values seen.
            {
                indexCountB += 2;
            }
            else
            {
                printf("********ERROR: Result is a value other than 4, 2, or 0 ********\n");
                return -1;
            }
        }
    }
    if (queryIndex == n) //No Majority yet with one last element to check: marble[n].
    {
        myArray[0] = booleanIndexA1;
        myArray[1] = booleanIndexA2;
        myArray[2] = booleanIndexB;
        myArray[3] = queryIndex;
        
        result = QCOUNT(1, myArray);
        
        if (result == 0)
        {
            indexCountB += 1;
        }
        else if (result == 2)
        {
            indexCountA += 1;
        }
    }
    return findMax(indexCountA, indexCountB, booleanIndexA1, booleanIndexB);
}
