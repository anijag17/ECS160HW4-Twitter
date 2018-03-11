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
	printf("n: %s\n",token);
	return token;
}

// returns an index where the target exists, or -1
int existsInArray(struct tweeter* arr, char* targetName, int size) 
{
    int index = -1;
 

    return index;
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
    
    int arrSize = 1;
    struct tweeter* array = malloc(sizeof(struct tweeter) * arrSize);

	printf("location of name is @ %d\n",location);
	while (fgets(parse,sizeof(parse),fp)!= NULL){
		char* currName = getName(parse,location);
        // If currName exists in array, increment its count by 1, cont.
        // Else, make a tweeter struct instance and add it to the array 
        // and initialize its count to 1; 
	}
	fclose(fp);
    return(0);

}
