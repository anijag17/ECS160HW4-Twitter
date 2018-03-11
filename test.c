#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct tweeter {
    char* name;
    int tweetCount;
};

// Either returns array index of targetName in array or -1 if not present
int existsInArray(struct tweeter* arr, char* targetName, int size) 
{
    // works
    int index = -1;
    int i = 0;
    while(i < size) 
    {
        if (strcmp(arr[i].name, targetName) == 0) 
        {
            index = i;
            break;
        }
        i++;
    }
    return index;
}

// Dynamically increases the size of the array with the space for 
// one more struct object
struct tweeter* increaseArray (struct tweeter* oldArr, int newSize)
{
    // works
    struct tweeter* newArr = oldArr;
    newArr = realloc(newArr, newSize * sizeof(struct tweeter));
    return newArr;
}

int main(int argc, char** argv){
    int size = 0;
    // works
    size++;
    struct tweeter* array = malloc(size * sizeof(struct tweeter));    
    array[0].name = "uno";
    array[0].tweetCount = 1234;

    size++;
    array = increaseArray(array, size); // works
    array[1].name = "dos";
    array[1].tweetCount = 321;

    size++;
    array = increaseArray(array, size); // works
    array[2].name = "tres";
    array[2].tweetCount = 321;

    // works
    int x = existsInArray(array, "tres", size); // prints 2
    printf("\n%d\n", x);    // prints 2
    // works
    for (int i = 0; i < size; i++) 
    {
        printf("%s\t\t", array[i].name);
        printf("%d\n", array[i].tweetCount);
    }

    return 0;
}
