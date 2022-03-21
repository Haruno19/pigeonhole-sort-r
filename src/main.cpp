/*
    Pigeonhole Sortig Algorithm revision with plain arrays

    21.03.2022 | g++ -std=c++11 | https://github.com/Haruno19
*/

#include <iostream>
#include <chrono>
#include <time.h>

const int arrayLength = 1000000;
const int maxValue = 1000000;

int array[arrayLength];
int min = maxValue;
int max = 0;
double ExecutionTime;

void PrintArray();
int** GenerateArray();
void FindMinMax();
void PigeonholeSort(int** bufferArray);


int main()
{
    srand(time(NULL));

    PigeonholeSort(GenerateArray());
    PrintArray();

    return 0;
}

void PrintArray()
{
    std::cout << "\nPigeonhole Sort with " << arrayLength << " elements \n";

    /*for(int i=0;i<arrayLength;i++)
    {
        if(array[i]<10) std::cout << " ";
        std::cout << array[i] << char(10);
    }*/
       
    std::cout << "\nExecution time: " << ExecutionTime << " sec \n\n"; 
}

int** GenerateArray()
{
    for(int i=0;i<arrayLength;i++)
        array[i]=rand()%maxValue + 1;

    FindMinMax();

    /*
        the auxiliary array has two columns:
            the first one contains the indexed values from the primary array (following the algorithm's logic)
            the second one contains the number of iterations of that value
    */

    int** a = new int*[max-min+1];  
    for(int i=0;i<max-min+1;i++)
        a[i] = new int[2];

    return a;
}

void FindMinMax()
{
    for(int i=0;i<arrayLength;i++)
        if(array[i]>=max)
            max=array[i];
        else if(array[i]<=min)
            min=array[i];
}

void PigeonholeSort(int** bufferArray)
{
    auto start = std::chrono::steady_clock::now();

    for(int i=0;i<arrayLength;i++)  
    {   //index every number in the primary array at the position [value - min]
        bufferArray[array[i]-min][0]=array[i];
        bufferArray[array[i]-min][1]++;
    }   //counts the times this value appears in the primary array

    int i=0, j=0;
    for(int k=0;k<max-min+1;k++)    //iterates through all the auxiliary
        if(bufferArray[k][1]>0)     //if there are values indexed in this position (meaning the counter is > 0)
        {
            j=0;
            while(j<bufferArray[k][1])  //it reinserts it in the primary array as many times as counted
            {
                array[i]=bufferArray[k][0];
                i++;
                j++;
            }
        }

    auto end = std::chrono::steady_clock::now();
    auto diff = end - start;
    ExecutionTime = (std::chrono::duration <double, std::milli> (diff).count())/1000;
}
