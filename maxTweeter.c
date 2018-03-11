#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct tweeter {
    char* name;
    int tweetCount;
};

/*
input the first line of csv here
return's location of the first "name" found
return -1 if cannot find name
*/
int getTweeterLocation(char* parse){
	int find = -1;
	char* token;
	int count = 0;
	token = strtok(parse,",");
	while (token != NULL) {
		if (!strcmp(token,"\"name\"")){
			find = count;
			break;
		}
		count++;
		token = strtok(NULL,",");
	}
	return find;
}

/*
given a line and the location counter, return the tweeter name value
*/
char* getName(char* parse, int location){
	char* token;
	token = strtok(parse,",");
	for (int i = 0; i < location; i++){
		token = strtok(NULL,",");
	}
	//printf("n: %s\n",token);
	return token;
}


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
	if (argc != 2){
		return -1;
	}
	FILE *fp=fopen(argv[1], "r");
	if (fp == NULL){
		return -1;
	}

	char parse[512];
	if( fgets (parse, sizeof(parse), fp)==NULL ){
		return -1;
	}

	int location = getTweeterLocation(parse);
    
    int size = 0;
    size++;
    struct tweeter* array = malloc(size * sizeof(struct tweeter)); 

	printf("location of name is @ %d\n",location);
	while (fgets(parse,sizeof(parse),fp)!= NULL){
		char* currName = getName(parse,location);
        printf("%s\n", currName);
        /*
        // If currName exists in array, increment its count by 1, cont.
        int index = existsInArray(array, currName, size);
        if (index != -1)
        {
            array[index].tweetCount += 1;
            continue;
        }
        // Else, make a tweeter struct instance and add it to the array 
        // and initialize its count to 1; 
        else if (index == -1) 
        {
            size++;
            array = increaseArray(array, size);
            array[size - 1].name = currName;
            array[size - 1].tweetCount = 1;            
        }
        */
	}
	fclose(fp);
    return(0);

}
