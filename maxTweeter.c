#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

static int SIZE = 20000;  //size will not exceed 20k
static int numCols = 0;
struct tweeter {  //data of pair
    char name[56];
    int tweetCount;
};

struct pair { //hash table entries
  char key[56];
  struct tweeter data;
};

//https://stackoverflow.com/questions/2624192/good-hash-function-for-strings
int hashf(char* name){  //used to hash string for table
  int size = strlen(name);
  int hash = 7;
  for (int i = 0; i < size; i++) {
    hash = hash*31 + (int)name[i];
  }
  return abs(hash%SIZE);
}

//function to increment count if name is in hashtable
int put(struct pair* table,char* name){
  int hash = hashf(name);
  if (!strcmp(table[hash].key,name)){  //result of hash has same name
    table[hash].data.tweetCount++;     //increase the count
    return 0;
  }
  else if (!strcmp(table[hash].key,"\0")){ //bucket has not been initialized
    strcpy(table[hash].key,name);
    strcpy(table[hash].data.name,name);
    table[hash].data.tweetCount++;
    return 0;
  }
  else {  //collision, loop until found or empty bucket is found
    int inc = hash++;
    while (strcmp(table[inc].key,name)){ //while they do not equal each other, check gthe next one
      if (table[inc].data.tweetCount == 0){ //if it is empty,place in this bucket
        strcpy(table[inc].key,name);
        strcpy(table[inc].data.name,name);
        table[inc].data.tweetCount++;
        return 0;
      }
      else inc++;
    }
    //found here
    strcpy(table[inc].key,name);
    strcpy(table[inc].data.name,name);
    table[inc].data.tweetCount++;
    return 0;
  }
}

//function finds the location of where "name" is in the header line
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

//with the variable location, grab the string at a specific location in a line
char* getName(char* parse, int location){
	char* token;
	token = strtok(parse,",");
	for (int i = 0; i < location; i++){
		token = strtok(NULL,",");
    if (token == NULL){
      return NULL;
    }
	}
	//printf("n: %s\n",token);
	return token;
}

//bubble sort, but only the first 10 for O(n) solution for top ten tweets
int bubbleSort(struct pair* table){
  for (int i = 0; i< 10; i++){
    for (int j = i+1; j < SIZE; j++){
      if (table[i].data.tweetCount < table[j].data.tweetCount){
        struct pair temp = table[i];
        table[i] = table[j];
        table[j] = temp;
      }
    }
  }
  return 0;
}

int main(int argc, char** argv){
  //checks
  if (argc != 2){ //makes sure there is only one csv argument
    printf("Invalid Input Format\n");
		return -1;
	}
	FILE *fp=fopen(argv[1], "r");
	if (fp == NULL){ //cannot find specific csv
    printf("Invalid Input Format\n");
		return -1;
	}

	char parse[512];
	if( fgets (parse, sizeof(parse), fp)==NULL ){  //if empty file
    printf("Invalid Input Format\n");
		return -1;
	}
  while (!strcmp(parse,"\n")){  //skip empty lines before
    if( fgets (parse, sizeof(parse), fp)==NULL ){  //if empty file
      printf("Invalid Input Format\n");
  		return -1;
    }
  }
  int location = getTweeterLocation(parse);
  if (location == -1){  //could not find "name" in first row
    printf("Invalid Input Format\n");
    return -1;
  }
  //end of checks
  struct pair table[SIZE];
  struct pair init; //initialize all buckets to be at 0
  strcpy(init.key,"\0");
  strcpy(init.data.name,"\0");
  init.data.tweetCount = 0;
  for (int i = 0; i < SIZE; i++){
    table[i] = init;
  }
  //table initialized
  char* curr;
  while (fgets(parse,sizeof(parse),fp)!= NULL){
    if (!strcmp(parse,"\n"))  //skip empty lines
    {
      continue;
    }
    curr = getName(parse,location);
    if (curr != NULL)
      put(table,curr);
  }

  bubbleSort(table);
  for (int i = 0; i < 10; i++){
    if (table[i].data.tweetCount == 0)
      break;
    printf("%s: %d\n",table[i].key,table[i].data.tweetCount);
  }

  return 0;
}
